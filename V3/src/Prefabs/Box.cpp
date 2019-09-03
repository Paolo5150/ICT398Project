#include "pch.h"
#include "Box.h"

#include "..\Components\BoxCollider.h"
#include "..\Diag\DiagRenderer.h"

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
	std::string name = "BoxCollider";
	BoxCollider* col = GetComponentInChild<BoxCollider>(name, name);
	if (col != nullptr)
	{
		std::vector<glm::vec3> points = col->GetBoxPoints();
		for (int i = 0; i < points.size(); i++)
		{
			DiagRenderer::Instance().RenderSphere(points[i]);
		}
	}
}

void Box::Start()
{

	PrintHierarchy();

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

void Box::OnCollisionEnter(Collider* g, Collision col)
{
	if (rb->GetUseGravity())
		rb->AddVelocity(-PhysicsWorld::Instance().gravity * Timer::GetDeltaS()); //If enabled, add gravity to the velocity vector

	//_parent->transform.Translate(-rb->GetVelocity() * Timer::GetDeltaS()); //Update the transform's postion in world space
	_parent->transform.RotateBy(-rb->GetAngularVelocity().x * Timer::GetDeltaS(), 1, 0, 0); //Update the transform's x rotation
	_parent->transform.RotateBy(-rb->GetAngularVelocity().y * Timer::GetDeltaS(), 0, 1, 0); //Update the transform's y rotation
	_parent->transform.RotateBy(-rb->GetAngularVelocity().z * Timer::GetDeltaS(), 0, 0, 1); //Update the transform's z rotation

	//glm::vec3 dir = transform.GetGlobalPosition() - collPoint;
	glm::vec3 dir = rb->GetVelocity();
	dir = glm::normalize(dir);
	dir = -dir;
	glm::vec3 normal = col.Point(); + col.Normal();
	DiagRenderer::Instance().RenderSphere(col.Point());
	//DiagRenderer::Instance().RenderSphere(normal);
	dir = dir - 2 * glm::dot(dir, normal) * normal;
	dir = glm::normalize(dir);
	Logger::LogInfo("BOX COLL POINT: ", col.Point()[0], " ", col.Point()[1], " ", col.Point()[2]);
	Logger::LogInfo("BOX COLL NORMAL: ", col.Normal()[0], " ", col.Normal()[1], " ", col.Normal()[2]);
	Logger::LogInfo("BOX COLL REVERT DIR: ", dir[0], " ", dir[1], " ", dir[2]);
	rb->SetVelocity(dir * glm::length(rb->GetVelocity()));
	//rb->SetVelocity(glm::vec3());

	
}
