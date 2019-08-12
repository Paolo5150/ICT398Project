#include "pch.h"
#include "Box.h"

#include "..\Components\BoxCollider.h"

Box::Box() : GameObject("Box")
{
	SetIsStatic(false);
}

Box::~Box()
{

}

void Box::Update()
{
	GameObject::Update();
}

void Box::Start()
{

	

	BoxCollider* bc = new BoxCollider();
	bc->enableRender = true;
	bc->transform.SetPosition(0, 0, 0);
	bc->transform.SetScale(1, 1, 1);
	bc->transform.SetRotation(0, 0, 0);
	bc->SetActive(true);
	AddComponent(bc);

	rb = new Rigidbody();
	AddComponent(rb);

	GameObject::Start(); //This will call start on all the object components, so it's better to leave it as last call when the collider
						 // has been added.
}

void Box::OnCollision(GameObject* g, glm::vec3 collPoint, glm::vec3 collNormal)
{
	//glm::vec3 dir = transform.GetGlobalPosition() - collPoint;
	glm::vec3 dir = rb->GetVelocity();
	dir = glm::normalize(dir);
	dir = -dir;
	glm::vec3 normal = collPoint + collNormal;
	dir = dir - 2 * glm::dot(dir, normal) * normal;
	dir = glm::normalize(dir);
	Logger::LogInfo("BOX COLL POINT: ", collPoint[0], " ", collPoint[1], " ", collPoint[2]);
	Logger::LogInfo("BOX COLL NORMAL: ", collNormal[0], " ", collNormal[1], " ", collNormal[2]);
	Logger::LogInfo("BOX COLL REVERT DIR: ", dir[0], " ", dir[1], " ", dir[2]);
	rb->SetVelocity(dir * glm::length(rb->GetVelocity()));

	
}
