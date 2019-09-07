#include "pch.h"
#include "Box.h"

#include "..\Components\BoxCollider.h"
#include "..\Diag\DiagRenderer.h"

int Box::count = 0;

Box::Box() : GameObject("Box")
{
	SetIsStatic(false);
	id = count;
	count++;
}

Box::~Box()
{

}

void Box::Update()
{
	GameObject::Update();
	std::string name = "BoxCollider";
	BoxCollider* col = GetComponentInChild<BoxCollider>(name, name);
	std::cout << transform.GetGlobalPosition().x << " " << transform.GetGlobalPosition().y << " " << transform.GetGlobalPosition().z << std::endl;
	if (col != nullptr)
	{
		//std::vector<glm::vec3> points = col->GetBoxPoints();
		//for (int i = 0; i < points.size(); i++)
		//{
			//DiagRenderer::Instance().RenderSphere(points[i]);
		//}
	}
}

void Box::Start()
{

	PrintHierarchy();

	rb = new Rigidbody();
	AddComponent(rb);
	//rb->SetAngularVelocity(5, 0, 0);
	if (id == 0)
	{
		rb->SetVelocity(0, 0, 0);
		rb->SetAngularVelocity(10, 20, 0);
	}
	else
	{
		rb->SetVelocity(0, 0, 0);
		rb->SetAngularVelocity(-10, 0, 0);
	}
	//rb->UseGravity(false);
	LoadCollidersFromFile("Assets\\Colliders\\Box.txt");

	GameObject::Start(); //This will call start on all the object components, so it's better to leave it as last call when the collider
						 // has been added.
}

void Box::OnCollisionEnter(Collider* g, Collision col)
{
	//if (rb->GetUseGravity())
		//rb->AddVelocity(-PhysicsWorld::Instance().gravity * Timer::GetDeltaS()); //If enabled, add gravity to the velocity vector
	
	//Calculate lambda value

	//This object treated as object 1, collided object as object 2
	if (id == 0)
	{
		DiagRenderer::Instance().RenderSphere(col.Point(), 1, glm::vec3(1, 0, 1));

		std::cout << "BEFORE COLLISION ADJUST POS: " << transform.GetGlobalPosition().x << " " << transform.GetGlobalPosition().y << " " << transform.GetGlobalPosition().z << std::endl;

		transform.Translate(-rb->GetVelocity() * Timer::GetDeltaS()); //Update the transform's postion in world space
		transform.RotateBy(-rb->GetAngularVelocity().z * Timer::GetDeltaS(), 0, 0, 1); //Update the transform's z rotation
		transform.RotateBy(-rb->GetAngularVelocity().x * Timer::GetDeltaS(), 1, 0, 0); //Update the transform's x rotation
		transform.RotateBy(-rb->GetAngularVelocity().y * Timer::GetDeltaS(), 0, 1, 0); //Update the transform's y rotation

		std::cout << "AFTER COLLISION ADJUST POS: " << transform.GetGlobalPosition().x << " " << transform.GetGlobalPosition().y << " " << transform.GetGlobalPosition().z << std::endl;

		float epsilon = 0.01f;

		Rigidbody* otherRB = g->GetParent()->GetComponent<Rigidbody>("Rigidbody");
		glm::vec3 otherVel = glm::vec3();
		glm::vec3 otherAngVel = glm::vec3();

		if (otherRB != nullptr)
		{
			std::cout << "IM SAFE!" << std::endl;
			//g->GetParent()->transform.Translate(-otherRB->GetVelocity() * Timer::GetDeltaS()); //Update the transform's postion in world space
			//g->GetParent()->transform.RotateBy(-otherRB->GetAngularVelocity().z * Timer::GetDeltaS(), 0, 0, 1); //Update the transform's z rotation
			//g->GetParent()->transform.RotateBy(-otherRB->GetAngularVelocity().x * Timer::GetDeltaS(), 1, 0, 0); //Update the transform's x rotation
			//g->GetParent()->transform.RotateBy(-otherRB->GetAngularVelocity().y * Timer::GetDeltaS(), 0, 1, 0); //Update the transform's y rotation

			otherVel = otherRB->GetVelocity();
			otherAngVel = otherRB-> GetAngularVelocity();
		}

		glm::vec3 r1 = col.Point() - (transform.GetGlobalPosition() + GetCentreOfMass());
		glm::vec3 r2 = col.Point() - (g->GetParent()->transform.GetGlobalPosition() + g->GetParent()->GetCentreOfMass());
		/*
		float top = -(1 + epsilon) * (glm::dot(col.Normal(), rb->GetVelocity() - otherVel)
			+ glm::dot(rb->GetAngularVelocity(), glm::cross(r1, col.Normal()))
			- glm::dot(otherAngVel, glm::cross(r2, col.Normal())));
			*/
		//Logger::LogInfo("TOP: ", top);
/*
		glm::vec3 bottom = (1 / GetTotalMass())
			+ (1 / g->GetParent()->GetTotalMass())
			+ ((glm::cross(r1, col.Normal()) * glm::inverse(GetInertiaTensor()) * glm::cross(r1, col.Normal()))
				+ (glm::cross(r2, col.Normal()) * glm::inverse(g->GetParent()->GetInertiaTensor()) * glm::cross(r2, col.Normal())));
				*/
		//Logger::LogInfo("BOTTOM: ", bottom.x, bottom.y, bottom.z);

		glm::vec3 lambda;

		//lambda = top / bottom * col.Normal();

		float top = GetTotalMass() * g->GetParent()->GetTotalMass() * (1 + epsilon) * glm::dot(rb->GetVelocity() - otherVel, col.Normal());
		float bottom = GetTotalMass() + g->GetParent()->GetTotalMass();

		lambda = -(top / bottom) * col.Normal();

		Logger::LogInfo("LAMBDA: ", lambda.x, lambda.y, lambda.z);

		//Velocity of this object after contact
		Logger::LogInfo("VELOCITY-PRE: ", rb->GetVelocity().x, rb->GetVelocity().y, rb->GetVelocity().z);
		rb->SetVelocity(rb->GetVelocity() + (lambda / GetTotalMass()));
		Logger::LogInfo("VELOCITY-POST: ", rb->GetVelocity().x, rb->GetVelocity().y, rb->GetVelocity().z);
		//rb->SetAngularVelocity(rb->GetAngularVelocity() + lambda * glm::inverse(GetInertiaTensor()) * glm::cross(r1, col.Normal()));
		//rb->SetAngularVelocity(rb->GetAngularVelocity() + lambda * glm::cross(r1, col.Normal()));
		//Logger::LogInfo(rb->GetAngularVelocity().x, rb->GetAngularVelocity().y, rb->GetAngularVelocity().z);
		if (otherRB != nullptr)
		{
			otherRB->SetVelocity(otherRB->GetVelocity() - (lambda / g->GetParent()->GetTotalMass()));
			otherRB->SetAngularVelocity(otherRB->GetAngularVelocity() - lambda * glm::inverse(g->GetParent()->GetInertiaTensor()) * glm::cross(r2, col.Normal()));
		}
		//if (rb->GetVelocity().length() * Timer::GetDeltaS() <= 0.01)
			//rb->SetVelocity(glm::vec3());
	}
	//rb->SetActive(false);
}

void Box::OnCollisionStay(Collider * g, Collision col)
{
	std::cout << "CALLED" << std::endl;
	std::cout << "PRE-COLLISION STAY POS: " << transform.GetGlobalPosition().x << " " << transform.GetGlobalPosition().y << " " << transform.GetGlobalPosition().z << std::endl;
	DiagRenderer::Instance().RenderSphere(col.Point(), 0.4f, glm::vec3(1, 0, 0));
	DiagRenderer::Instance().RenderSphere(col.Point() + col.Normal(), 0.4f, glm::vec3(1, 0, 1));
	transform.Translate(-rb->GetVelocity() * Timer::GetDeltaS()); //Update the transform's postion in world space
	transform.RotateBy(-rb->GetAngularVelocity().z * Timer::GetDeltaS(), 0, 0, 1); //Update the transform's z rotation
	transform.RotateBy(-rb->GetAngularVelocity().x * Timer::GetDeltaS(), 1, 0, 0); //Update the transform's x rotation
	transform.RotateBy(-rb->GetAngularVelocity().y * Timer::GetDeltaS(), 0, 1, 0);
	std::cout << "POST-COLLISION STAY POS: " << transform.GetGlobalPosition().x << " " << transform.GetGlobalPosition().y << " " << transform.GetGlobalPosition().z << std::endl;
	//if (rb->GetVelocity().length() * Timer::GetDeltaS() <= 0.1)
		//rb->SetVelocity(glm::vec3());
	//rb->SetVelocity(-rb->GetVelocity());
	//rb->SetAngularVelocity(-rb->GetAngularVelocity());
}


