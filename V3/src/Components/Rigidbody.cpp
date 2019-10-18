#include "pch.h"
#include "Rigidbody.h"



Rigidbody::Rigidbody() : Component("Rigidbody")
{
	velocity = glm::vec3(0, 0, 0);
	angVelocity = glm::vec3(0, 0, 0);
	useGravity = true;
	awake = 1;
	timer = 0;
	damping = 1.5;
	ignoreRotation = 0;

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
	ignoreRotation = 0;


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

	angVelocity = glm::lerp(angVelocity, glm::vec3(), Timer::GetDeltaS() * damping * 6 );

	if (fabs(angVelocity.x) < 0.05)
		angVelocity.x = 0;

	if (fabs(angVelocity.z) < 0.05)
		angVelocity.z = 0;

	if (fabs(angVelocity.y) < 0.05)
		angVelocity.y = 0;

	if(useGravity && awake)
		velocity += PhysicsWorld::Instance().gravity * _parent->GetTotalMass() * Timer::GetDeltaS(); //If enabled, add gravity to the velocity vector

	velocity.x = glm::lerp(velocity.x, 0.0f, Timer::GetDeltaS() * damping);
	velocity.z = glm::lerp(velocity.z, 0.0f, Timer::GetDeltaS() * damping);

	if (fabs(velocity.x) < 0.05)
		velocity.x = 0;

	if (fabs(velocity.z) < 0.05)
		velocity.z = 0;

	_parent->transform.Translate(velocity * Timer::GetDeltaS()); //Update the transform's postion in world space
	_parent->transform.RotateBy(angVelocity.x * Timer::GetDeltaS(), 1, 0, 0); //Update the transform's x rotation
	_parent->transform.RotateBy(angVelocity.y * Timer::GetDeltaS(), 0, 1, 0); //Update the transform's y rotation
	_parent->transform.RotateBy(angVelocity.z * Timer::GetDeltaS(), 0, 0, 1); //Update the transform's z rotation		





}

bool Rigidbody::GetUseDynamicPhysics()
{
	return useDynamicPhysics;
}

void Rigidbody::SetUseDynamicPhysics(bool useDynamicPhysics)
{
	this->useDynamicPhysics = useDynamicPhysics;
}
