#include "pch.h"
#include "MainCamera.h"
#include "..\Core\Timer.h"
#include "..\Components\Rigidbody.h"
#include "..\Components\BoxCollider.h"
#include "Box2.h"
#include "..\Scene\SceneManager.h"

MainCamera::MainCamera() : CameraPerspective(60.0f, Window::Instance().GetAspectRatio(), 0.1f, 100000.0f)
{
	this->SetName("Main Camera");
	m_rotationSpeed = 20;
	m_movementSpeed = 20;	
	blockRotation = false;
	blockMovement = false;
	SetIsStatic(0);
}

void MainCamera::Start()
{

BoxCollider* bc = new BoxCollider();
	bc->transform.SetScale(0.5,3.0,1.0);
	//bc->RemoveCollideAgainstLayer(CollisionLayers::DEFAULT);
	bc->enableRender = 1;

	AddComponent(bc);

	rb = new Rigidbody();
	rb->UseGravity(false);
	rb->SetUseDynamicPhysics(false);
	AddComponent(rb);
	//Logger::LogInfo("Camera trans child", transform.transformChildren.size());

}

void MainCamera::OnCollisionEnter(Collider* c, Collision& collision)
{

	transform.Translate(rb->GetVelocity() * -Timer::GetDeltaS());

		
}

void MainCamera::OnCollisionStay(Collider* c, Collision& collision)
{
	//Logger::LogInfo("Camera colliding with", c->GetParent()->name);
	transform.Translate(rb->GetVelocity() * -Timer::GetDeltaS());

}


void MainCamera::Update()
{	
	if (!blockRotation)
	{

	transform.RotateBy(Input::GetDeltaMousePosX() * Timer::GetDeltaS() * m_rotationSpeed, glm::vec3(0, 1, 0));
	transform.RotateBy(Input::GetDeltaMousePosY() * Timer::GetDeltaS() * m_rotationSpeed, transform.GetLocalRight());
	}

	if (!blockMovement)
	{

	if (Input::GetKeyDown(GLFW_KEY_KP_ADD))
	{
		m_movementSpeed += 0.5;
	}

	if (Input::GetKeyDown(GLFW_KEY_KP_SUBTRACT))
	{
		m_movementSpeed = m_movementSpeed < 0 ? 0 : m_movementSpeed - 0.5;
	}
	rb->SetVelocity(0, 0, 0);

	if (Input::GetKeyDown(GLFW_KEY_W) == true && Input::GetKeyDown(GLFW_KEY_S) == false)
	{
		//this->transform.SetPosition(this->transform.GetPosition() + (m_movementSpeed * Timer::GetDeltaS() * this->transform.GetLocalFront()));
		rb->SetVelocity(this->transform.GetLocalFront());
	}
	else if (Input::GetKeyDown(GLFW_KEY_S) == true && Input::GetKeyDown(GLFW_KEY_W) == false)
	{
		//this->transform.SetPosition(this->transform.GetPosition() - (m_movementSpeed * Timer::GetDeltaS() * this->transform.GetLocalFront()));
		rb->SetVelocity(-this->transform.GetLocalFront());

	}

	//Handle side-to-side movement
	if (Input::GetKeyDown(GLFW_KEY_D) == true && Input::GetKeyDown(GLFW_KEY_A) == false)
	{
		//this->transform.SetPosition(this->transform.GetPosition() + (m_movementSpeed * Timer::GetDeltaS() * this->transform.GetLocalRight()));
		rb->AddVelocity(this->transform.GetLocalRight());

	}
	else if (Input::GetKeyDown(GLFW_KEY_A) == true && Input::GetKeyDown(GLFW_KEY_D) == false)
	{
		//this->transform.SetPosition(this->transform.GetPosition() - (m_movementSpeed * Timer::GetDeltaS() * this->transform.GetLocalRight()));
		rb->AddVelocity(-this->transform.GetLocalRight());

	}
	}

	if (Input::GetKeyPressed(GLFW_KEY_SPACE))
	{
		Box2* l = new Box2();

		l->transform.SetPosition(transform.GetPosition() + transform.GetLocalFront() * 5.0f);
		l->rb->AddVelocity(transform.GetLocalFront() * 10.0f);

		l->Start();
		SceneManager::Instance().GetCurrentScene().AddGameObject(l);
	}

	//Common inputs for all scenes
	if (Input::GetKeyDown(GLFW_KEY_T))
	{
		Input::SetCursorMode("normal");
		blockRotation = true;
	}

	if (Input::GetKeyDown(GLFW_KEY_Y))
	{
		Input::SetCursorMode("disabled");
		blockRotation = false;
	}
	if(glm::length2(rb->GetVelocity()) != 0)
		rb->SetVelocity(glm::normalize(rb->GetVelocity()) * m_movementSpeed);


	Camera::Update(); //Update last as this will update the view matrix with the new position values

	//transform.SetPosition(transform.GetPosition().x,4,transform.GetPosition().z);
}