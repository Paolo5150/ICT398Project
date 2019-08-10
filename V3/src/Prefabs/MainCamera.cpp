#include "pch.h"
#include "MainCamera.h"
#include "..\Core\Timer.h"

MainCamera::MainCamera() : CameraPerspective(60.0f, Window::Instance().GetAspectRatio(), 0.1f, 100000.0f)
{
	this->SetName("Main Camera");
	m_rotationSpeed = 20;
	m_movementSpeed = 40;	
	blockRotation = false;
}

void MainCamera::Update()
{	
	if (!blockRotation)
	{

	transform.RotateBy(Input::GetDeltaMousePosX() * Timer::GetDeltaS() * m_rotationSpeed, glm::vec3(0, 1, 0));
	transform.RotateBy(Input::GetDeltaMousePosY() * Timer::GetDeltaS() * m_rotationSpeed, transform.GetLocalRight());
	}

	if (Input::GetKeyDown(GLFW_KEY_KP_ADD))
	{
		m_movementSpeed += 0.2;
	}

	if (Input::GetKeyDown(GLFW_KEY_KP_SUBTRACT))
	{
		m_movementSpeed = m_movementSpeed < 0 ? 0 : m_movementSpeed - 0.2;
	}

	if (Input::GetKeyDown(GLFW_KEY_W) == true && Input::GetKeyDown(GLFW_KEY_S) == false)
	{
		this->transform.SetPosition(this->transform.GetPosition() + (m_movementSpeed * Timer::GetDeltaS() * this->transform.GetLocalFront()));
	}
	else if (Input::GetKeyDown(GLFW_KEY_S) == true && Input::GetKeyDown(GLFW_KEY_W) == false)
	{
		this->transform.SetPosition(this->transform.GetPosition() - (m_movementSpeed * Timer::GetDeltaS() * this->transform.GetLocalFront()));
	}

	//Handle side-to-side movement
	if (Input::GetKeyDown(GLFW_KEY_D) == true && Input::GetKeyDown(GLFW_KEY_A) == false)
	{
		this->transform.SetPosition(this->transform.GetPosition() + (m_movementSpeed * Timer::GetDeltaS() * this->transform.GetLocalRight()));
	}
	else if (Input::GetKeyDown(GLFW_KEY_A) == true && Input::GetKeyDown(GLFW_KEY_D) == false)
	{
		this->transform.SetPosition(this->transform.GetPosition() - (m_movementSpeed * Timer::GetDeltaS() * this->transform.GetLocalRight()));
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

	//Logger::LogInfo("Speed", m_movementSpeed);
	Camera::Update(); //Update last as this will update the view matrix with the new position values
}