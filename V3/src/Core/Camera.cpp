#include "pch.h"
#include "Camera.h"
#include "..\Events\WindowEvents.h"

std::list<Camera*> Camera::allCameras;
std::vector<Camera*> Camera::allCamerasVector;

Camera::Camera(std::string name) : GameObject(name)
{
	
	//cullingMask = Layers::DEFAULT | Layers::GUI;
	//Load all layers
	for (int i = 0; i < 30; i++)
		AddLayerMask(1 << i);

	depth = 0;
	allCameras.push_back(this);
	UpdateOrdererdCameras();

	resizeEventToken = EventDispatcher::Instance().SubscribeCallback<WindowResizeEvent>(std::bind(&Camera::OnScreenResize, this, std::placeholders::_1));

}

Camera* Camera::GetCameraByName(std::string name)
{
	for (int i = 0; i < GetAllCameras().size(); i++)
	{
		if (GetAllCameras()[i]->GetName() == name)
			return GetAllCameras()[i];
	}

	return nullptr;
}

void Camera::Update()
{
	GameObject::Update();
	UpdateViewMatrix();

}

void Camera::UpdateViewMatrix()
{
	viewMatrix = glm::mat4();
	//transform.InvertMatrix();

	viewMatrix = glm::lookAt(transform.GetPosition(), transform.GetPosition() + transform.GetLocalFront(), transform.GetLocalUp());
	
}


void Camera::UpdateOrdererdCameras()
{
	allCamerasVector.clear();

	auto it = allCameras.begin();
	for (; it != allCameras.end(); it++)
		allCamerasVector.push_back(*it);

	std::sort(allCamerasVector.begin(), allCamerasVector.end(), [](Camera* l, Camera* r) {

		return l->GetDepth() < r->GetDepth();
	});


}

Camera::~Camera()
{
	EventDispatcher::Instance().UnsubscribeCallback<WindowResizeEvent>(resizeEventToken);

	auto it = allCameras.begin();

	for (; it != allCameras.end();)
	{
		if ((*it) == this)
		{
			it = allCameras.erase(it);
		}
		else
			it++;
	}
	Camera::UpdateOrdererdCameras();

}