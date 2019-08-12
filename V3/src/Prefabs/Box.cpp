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

void Box::OnCollision(GameObject* g, glm::vec3 collPoint)
{
	glm::vec3 dir = transform.GetGlobalPosition() - collPoint;
	dir = glm::normalize(dir);
	rb->SetVelocity(dir * glm::abs(rb->GetVelocity()));
	//transform.set
	//rb->SetVelocity(-rb->GetVelocity());
	Logger::LogInfo("Collided against", g->GetName());
}
