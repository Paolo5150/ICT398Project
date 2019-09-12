#include "pch.h"
#include "Box2.h"

Box2::Box2() : GameObject("Box")
{
	SetIsStatic(false);
	rb = new Rigidbody();
	AddComponent(rb);
	rb->UseGravity(false);
	LoadCollidersFromFile("Assets\\Colliders\\Box2.txt");
}

Box2::~Box2()
{

}

void Box2::Update()
{
	GameObject::Update();
}

void Box2::Start()
{
	PrintHierarchy();

	GameObject::Start(); //This will call start on all the object components, so it's better to leave it as last call when the collider
						 // has been added.
}

void Box2::OnCollisionEnter(Collider* g, Collision col)
{
}

void Box2::OnCollisionStay(Collider * g, Collision col)
{
}


