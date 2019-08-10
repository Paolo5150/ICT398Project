#include "pch.h"
#include "Transform.h"
#include "Logger.h"
#include "GameObject.h"
#include <glm/gtx/rotate_vector.hpp>

Transform::Transform(GameObject* go) : gameObject(go)
{
	scale = glm::vec3(1, 1, 1);
	SetPosition(0,0,0);
	SetRotation(0,0,0);
	parent = nullptr;
	ignoreParentRotation = 0;
	modelMatrix = GetTranslateMatrix()* rotationMatrix * GetScaleMatrix();

}

Transform::~Transform() {
	//Logger::LogError("Transform destoryed name", gameObject->name);
}

glm::mat4& Transform::GetMatrix() {

	return modelMatrix;
}

void Transform::UpdateHierarchy(bool forceParent)
{	
	if (parent || forceParent)
		this->modelMatrix = this->parent->modelMatrix * GetTranslateMatrix()* rotationMatrix * GetScaleMatrix();
	else
		this->modelMatrix = GetTranslateMatrix()* rotationMatrix * GetScaleMatrix();

	UpdateVectors();

	if (transformChildren.size()!= 0)
	{
		for (auto it = transformChildren.begin(); it != transformChildren.end();)
		{
			if (*it)
			{
				(*it)->UpdateHierarchy(1);
				it++;
			}
			else
				it = transformChildren.erase(it);
		}

	}
}


void Transform::Translate(glm::vec3 v)
{
	Translate(v.x, v.y, v.z);
}



void Transform::Translate(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;
	UpdateHierarchy();
}


void Transform::SetPosition(glm::vec3 r)
{
	position = r;
	UpdateHierarchy();
}

void Transform::SetScale(float r)
{
	scale *= r;
	UpdateHierarchy();
}


void Transform::SetScale(glm::vec3 r)
{
	scale = r;
	UpdateHierarchy();
}

void Transform::SetRotation(glm::vec3& rot)
{
	SetRotation(rot.x, rot.y, rot.z);
}

void Transform::SetRotation(float x, float y, float z)
{
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
	rotationQuat = glm::quat(glm::radians(rotation));
	rotationMatrix = glm::toMat4(rotationQuat);
	UpdateHierarchy();
}


void Transform::UpdateVectors()
{
	localFront = glm::normalize(glm::vec3(modelMatrix * glm::vec4(0,0,1,0)));
	localRight = -glm::normalize(glm::vec3(modelMatrix * glm::vec4(1, 0, 0, 0)));
	localUp = glm::normalize(glm::cross(localRight, localFront));
}


void Transform::SetRotation(float x, float y, float z, float w)
{

	rotationQuat = glm::quat(x, y, z, w);
	rotationMatrix = glm::toMat4(rotationQuat);
	UpdateHierarchy();
}

void Transform::RotateBy(float angle, glm::vec3 axis)
{	
	if (angle != 0)
	{
		rotation += angle * axis;
		glm::quat q;
		q  = glm::angleAxis(glm::radians(angle), axis);
		rotationQuat = q * rotationQuat;
		rotationMatrix = glm::toMat4(rotationQuat);
		UpdateHierarchy();
	}
}

void Transform::RotateBy(float angle, int x, int y, int z)
{
	RotateBy(angle, glm::vec3(x, y, z));
}
void Transform::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	UpdateHierarchy();

}
void Transform::SetScale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
	UpdateHierarchy();

}



glm::mat4& Transform::GetGlobalRotation()
{
	glm::vec3 s = GetGlobalScale();

	globalRotationMatrix[0][0] = modelMatrix[0][0] / s.x;
	globalRotationMatrix[0][1] = modelMatrix[0][1] / s.x;
	globalRotationMatrix[0][2] = modelMatrix[0][2] / s.x;
	globalRotationMatrix[0][3] = 0.0f;		  
	globalRotationMatrix[1][0] = modelMatrix[1][0] / s.y;
	globalRotationMatrix[1][1] = modelMatrix[1][1] / s.y;
	globalRotationMatrix[1][2] = modelMatrix[1][2] / s.y;
	globalRotationMatrix[1][3] = 0.0f;		 
	globalRotationMatrix[2][0] = modelMatrix[2][0] / s.z;
	globalRotationMatrix[2][1] = modelMatrix[2][1] / s.z;
	globalRotationMatrix[2][2] = modelMatrix[2][2] / s.z;
	globalRotationMatrix[2][3] = 0.0f;
	globalRotationMatrix[3][0] = 0.0f;
	globalRotationMatrix[3][1] = 0.0f;
	globalRotationMatrix[3][2] = 0.0f;
	globalRotationMatrix[3][3] = 1.0f;
	
	return globalRotationMatrix;
}

glm::vec3& Transform::GetGlobalPosition()
{
	globalPosition.x = modelMatrix[3][0];
	globalPosition.y = modelMatrix[3][1];
	globalPosition.z = modelMatrix[3][2];
	return globalPosition;
}

glm::vec3& Transform::GetGlobalScale()
{
	glm::vec3 aei(modelMatrix[0][0], modelMatrix[0][1], modelMatrix[0][2]);
	glm::vec3 bfj(modelMatrix[1][0], modelMatrix[1][1], modelMatrix[1][2]);
	glm::vec3 cgk(modelMatrix[2][0], modelMatrix[2][1], modelMatrix[2][2]);

	globalScale.x = glm::length(aei);
	globalScale.y = glm::length(bfj);
	globalScale.z = glm::length(cgk);
	return globalScale;


}

std::string Transform::RotationQuatToString()
{
	glm::quat q = glm::quat(GetGlobalRotation());
	std::stringstream ss;
	ss << "RQ:{" << q.x;
	ss << " " << q.y;
	ss << " " << q.z;
	ss << " " << q.w;
	ss << "} ";
	   
	return ss.str();
}


glm::mat4 Transform::GetRotationMatrix()
{
	
	return rotationMatrix;
}

glm::mat4 Transform::GetTranslateMatrix()
{
	glm::mat4 trans;
	trans = glm::translate(trans, position);
	return trans;
}



glm::mat4 Transform::GetScaleMatrix()
{
	glm::mat4 trans;
	trans = glm::scale(trans, scale);
	return trans;
}

std::string Transform::VectorsToString()
{
	std::stringstream ss;
	ss << "F:{" << localFront.x;
	ss << " " << localFront.y;
	ss << " " << localFront.z;
	ss << "} ";

	ss << "R:{" << localRight.x;
	ss << " " << localRight.y;
	ss << " " << localRight.z;
	ss << "} ";

	ss << "U:{" << localUp.x;
	ss << " " << localUp.y;
	ss << " " << localUp.z;
	ss << "}";
	return ss.str();
}

std::string Transform::ToString()
{
	std::stringstream ss;
	ss << "P:{" << position.x;
	ss << " " << position.y;
	ss << " " << position.z;
	ss << "} ";

	ss << "R:{" << rotation.x;
	ss << " " << rotation.y;
	ss << " " << rotation.z;
	ss << "} ";

	ss << "S:{" << scale.x;
	ss << " " << scale.y;
	ss << " " << scale.z;
	ss << "}";

	return ss.str();

}

void Transform::LookAt(float x, float y, float z)
{
	glm::vec3 target(x, y, z);
	LookAt(target);
}

void  Transform::LookAt(glm::vec3 target)
{
	localFront = glm::normalize(target - GetGlobalPosition());

	if (abs(localFront.x) < 0.00001 && abs(localFront.z) < 0.00001) {
		if (localFront.y > 0)
			localUp = glm::vec3(0.0, 0.0, -1.0); //if direction points in +y 
		else
			localUp = glm::vec3(0.0, 0.0, 1.0); //if direction points in -y  
	}
	else {
		localUp = glm::vec3(0.0, 1.0, 0.0); //y-axis is the general up 
	}
	localUp = glm::normalize(localUp);
	localRight = glm::normalize(glm::cross(localFront, localUp));
	localUp = glm::normalize(glm::cross(localRight,localFront ));

	rotationMatrix = glm::mat4(localRight.x, localRight.y, localRight.z, 0.0f,
		localUp.x, localUp.y, localUp.z, 0.0f,
		localFront.x, localFront.y, localFront.z, 0.0f,
		position.x, position.y, position.z, 1.0f);

	glm::quat q = glm::quat(rotationMatrix);
	rotation = glm::degrees(glm::eulerAngles(q));
	modelMatrix = GetTranslateMatrix()* rotationMatrix * GetScaleMatrix();
}





glm::vec3& Transform::GetPosition()
{
	return position;
}
glm::vec3& Transform::GetScale()
{
	return scale;
}
glm::vec3& Transform::GetRotation()
{
	return rotation;
}


