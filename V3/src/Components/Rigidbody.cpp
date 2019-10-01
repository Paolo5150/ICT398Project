#include "pch.h"
#include "Rigidbody.h"


Rigidbody::Rigidbody() : Component("Rigidbody")
{
	velocity = glm::vec3(0, 0, 0);
	angVelocity = glm::vec3(0, 0, 0);
	useGravity = true;
	awake = 1;
	timer = 0;
	damping = 0.5;

}

Rigidbody::Rigidbody(float x, float y, float z, bool relative) : Component("Rigidbody")
{
	if (relative == false) //Add velocity to the global refence frame
		AddVelocity(x, y, z);
	else //Add velocity to the local refence frame
		AddRelativeVelocity(x, y, z);

	angVelocity = glm::vec3(0, 0, 0);
	useGravity = true;
	awake = 1;
	timer = 0;

}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::SetVelocity(float x, float y, float z)
{
	velocity = glm::vec3(x, y, z);
	awake = 1;

}

void Rigidbody::AddVelocity(float x, float y, float z)
{
	velocity += glm::vec3(x, y, z);
	awake = 1;

}

void Rigidbody::AddVelocity(glm::vec3 velocityVector)
{
	velocity += velocityVector;
	awake = 1;

}

void Rigidbody::AddRelativeVelocity(float x, float y, float z)
{
	velocity += x * _parent->transform.GetLocalFront();
	velocity += y * _parent->transform.GetLocalUp();
	velocity += z * _parent->transform.GetLocalRight();
	awake = 1;
}

void Rigidbody::AddRelativeVelocity(glm::vec3 velocityVector)
{
	velocity += velocityVector.x * _parent->transform.GetLocalFront();
	velocity += velocityVector.y * _parent->transform.GetLocalUp();
	velocity += velocityVector.z * _parent->transform.GetLocalRight();
	awake = 1;
}

void Rigidbody::SetVelocity(glm::vec3 velocityVector)
{
	velocity = velocityVector;
	awake = 1;
}

glm::vec3 Rigidbody::GetVelocity() const
{
	return velocity;
}

void Rigidbody::UseGravity(bool gravityEnabled)
{
	useGravity = gravityEnabled;
}

bool Rigidbody::GetUseGravity()
{
	return useGravity;
}

void Rigidbody::SetAngularVelocity(float x, float y, float z)
{
	angVelocity = glm::vec3(x, y, z);
	awake = 1;

}

void Rigidbody::SetAngularVelocity(glm::vec3 angularVelocityVector)
{
	angVelocity = angularVelocityVector;
	awake = 1;

}

void Rigidbody::AddAngularVelocity(float x, float y, float z)
{
	angVelocity += glm::vec3(x, y, z);
	awake = 1;

}

void Rigidbody::AddRelativeAngularVelocity(float x, float y, float z)
{
	angVelocity += x * _parent->transform.GetLocalFront();
	angVelocity += y * _parent->transform.GetLocalUp();
	angVelocity += z * _parent->transform.GetLocalRight();
	awake = 1;

}

void Rigidbody::AddRelativeAngularVelocity(glm::vec3 angularVelocityVector)
{
	angVelocity += angularVelocityVector.x * _parent->transform.GetLocalFront();
	angVelocity += angularVelocityVector.y * _parent->transform.GetLocalUp();
	angVelocity += angularVelocityVector.z * _parent->transform.GetLocalRight();
	awake = 1;

}

void Rigidbody::AddAngularVelocity(glm::vec3 angularVelocityVector)
{
	angVelocity += angularVelocityVector;
	awake = 1;
}

glm::vec3 Rigidbody::GetAngularVelocity() const
{
	return angVelocity;
}

void Rigidbody::Update()
{
	timer += Timer::GetDeltaS();

	if (glm::length(velocity) < 0.2  && glm::length(angVelocity) < 0.2 && timer > 0.5)
	{
		velocity = glm::vec3(0);
		angVelocity = glm::vec3();
		awake = false;

	}

	if (awake)
	{
		velocity = glm::lerp(velocity, glm::vec3(), Timer::GetDeltaS() * damping);
		angVelocity = glm::lerp(angVelocity, glm::vec3(), Timer::GetDeltaS() * damping * 2);

		//angVelocity += glm::vec3(1, 1, 1) * -damping;

		if(useGravity)
			velocity += PhysicsWorld::Instance().gravity * _parent->GetTotalMass() * Timer::GetDeltaS(); //If enabled, add gravity to the velocity vector

		_parent->transform.Translate(velocity * Timer::GetDeltaS()); //Update the transform's postion in world space
		_parent->transform.RotateBy(angVelocity.x * Timer::GetDeltaS(), 1, 0, 0); //Update the transform's x rotation
		_parent->transform.RotateBy(angVelocity.y * Timer::GetDeltaS(), 0, 1, 0); //Update the transform's y rotation
		_parent->transform.RotateBy(angVelocity.z * Timer::GetDeltaS(), 0, 0, 1); //Update the transform's z rotation
	}
}

bool Rigidbody::GetUseDynamicPhysics()
{
	return useDynamicPhysics;
}

void Rigidbody::SetUseDynamicPhysics(bool useDynamicPhysics)
{
	this->useDynamicPhysics = useDynamicPhysics;
}
