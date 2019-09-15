#include "pch.h"
#include "Box.h"

#include "..\Components\BoxCollider.h"

Box::Box() : GameObject("Box")
{
	SetIsStatic(false);
	rb = new Rigidbody();
	AddComponent(rb);
	rb->UseGravity(false);
	LoadCollidersFromFile("Assets\\Colliders\\Box.txt");
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
	PrintHierarchy();

	GameObject::Start(); //This will call start on all the object components, so it's better to leave it as last call when the collider
						 // has been added.
}

void Box::OnCollisionEnter(Collider* g, Collision& col)
{
}

void Box::OnCollisionStay(Collider * g, Collision& col)
{
}


