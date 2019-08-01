#include "pch.h"
#include "CameraPerspective.h"


CameraPerspective::CameraPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) : Camera("Camera_Perspective")
{
	camerType = PERSPECTIVE;

	this->aspectRatio = aspectRatio;
	this->FOV = fieldOfView;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;

	projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);

}

bool CameraPerspective::OnScreenResize(Event* e)
{

	WindowResizeEvent* ev = dynamic_cast<WindowResizeEvent*>(e);

	this->aspectRatio = ev->width / (float)ev->height;
	projectionMatrix = glm::perspective(glm::radians(FOV), aspectRatio, nearPlane, farPlane);
	return 0;

}


float CameraPerspective::GetAspectRatio() { return aspectRatio; }
float CameraPerspective::GetFOV() { return FOV; }
