#include "pch.h"
#include "Rigidbody.h"
#include "..\Core\Timer.h"


Rigidbody::Rigidbody() : Component("Rigidbody")
{
	velocity = glm::vec3(0, 0, 0);
	angVelocity = glm::vec3(0, 0, 0);
}

Rigidbody::Rigidbody(float x, float y, float z, bool relative) : Component("Rigidbody")
{
	if (relative == false) //Add velocity to the global refence frame
		AddVelocity(x, y, z);
	else //Add velocity to the local refence frame
		AddRelativeVelocity(x, y, z);

	angVelocity = glm::vec3(0, 0, 0);
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::SetVelocity(float x, float y, float z)
{
	velocity = glm::vec3(x, y, z);
}

void Rigidbody::AddVelocity(float x, float y, float z)
{
	velocity += glm::vec3(x, y, z);
}

void Rigidbody::AddVelocity(glm::vec3 velocityVector)
{
	velocity += velocityVector;
}

void Rigidbody::AddRelativeVelocity(float x, float y, float z)
{
	velocity += x * _parent->transform.GetLocalFront();
	velocity += y * _parent->transform.GetLocalUp();
	velocity += z * _parent->transform.GetLocalRight();
}

void Rigidbody::AddRelativeVelocity(glm::vec3 velocityVector)
{
	velocity += velocityVector.x * _parent->transform.GetLocalFront();
	velocity += velocityVector.y * _parent->transform.GetLocalUp();
	velocity += velocityVector.z * _parent->transform.GetLocalRight();
}

void Rigidbody::SetVelocity(glm::vec3 velocityVector)
{
	velocity = velocityVector;
}

glm::vec3 Rigidbody::GetVelocity() const
{
	return velocity;
}

void Rigidbody::SetAngularVelocity(float x, float y, float z)
{
	angVelocity = glm::vec3(x, y, z);
}

void Rigidbody::SetAngularVelocity(glm::vec3 angularVelocityVector)
{
	angVelocity = angularVelocityVector;
}

void Rigidbody::AddAngularVelocity(float x, float y, float z)
{
	angVelocity += glm::vec3(x, y, z);
}

void Rigidbody::AddAngularVelocity(glm::vec3 angularVelocityVector)
{
	angVelocity += angularVelocityVector;
}

glm::vec3 Rigidbody::GetAngularVelocity() const
{
	return angVelocity;
}

void Rigidbody::Update()
{
	_parent->transform.Translate(velocity * Timer::GetDeltaS()); //Update the transform's postion in world space
	_parent->transform.RotateBy(angVelocity.x * Timer::GetDeltaS(), 1, 0, 0); //Update the transform's x rotation
	_parent->transform.RotateBy(angVelocity.y * Timer::GetDeltaS(), 0, 1, 0); //Update the transform's y rotation
	_parent->transform.RotateBy(angVelocity.z * Timer::GetDeltaS(), 0, 0, 1); //Update the transform's z rotation
}