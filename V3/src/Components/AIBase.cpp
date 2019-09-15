#include "pch.h"
#include "AIBase.h"
#include <thread>
#include <future>


AIBase::AIBase() : Component("AIBase")
{
	_type = "AI";
	SetState("");
	_parentTransform = nullptr;
	_targetTransform = nullptr;
	_nextNode.x = -1;
	_nextNode.y = -1;
	_nextNode.z = -1;
	_lastStateChange = 0.0f;
	_eventReceived = false;

	//------------------------------
	//Considered for removal
	//------------------------------
	//_otherTarget.x = -1;
	//_otherTarget.y = -1;
	//_otherTarget.z = -1;
	//_randomTimer = 0.0f;
	//_updateTimer = 0.0f;
	//------------------------------
}

AIBase::AIBase(Transform& targetTransform) : Component("AIBase")
{
	_type = "AI";
	SetState("");
	_parentTransform = nullptr;
	SetTarget(targetTransform);
	_nextNode.x = -1;
	_nextNode.y = -1;
	_nextNode.z = -1;
	_lastStateChange = 0.0f;
	_eventReceived = false;

	//------------------------------
	//Considered for removal
	//------------------------------
	//_otherTarget.x = -1;
	//_otherTarget.y = -1;
	//_otherTarget.z = -1;
	//_randomTimer = 0.0f;
	//_updateTimer = 0.0f;
	//------------------------------
}

AIBase::~AIBase()
{
}

void AIBase::SetTarget(Transform& targetTransform)
{
	_targetTransform = &targetTransform;
}

float AIBase::GetDistanceToTarget() const
{
	return sqrt(pow(_targetTransform->GetPosition().x - _parentTransform->GetPosition().x, 2) + pow(_targetTransform->GetPosition().y - _parentTransform->GetPosition().y, 2) + pow(_targetTransform->GetPosition().z - _parentTransform->GetPosition().z, 2));
}

float AIBase::GetRotationToTarget() const
{
	glm::vec3 toTarget = glm::vec3(_targetTransform->GetPosition().x, _parentTransform->GetPosition().y, _targetTransform->GetPosition().z) - _parentTransform->GetPosition();
	float yAngle = glm::degrees(glm::angle(_parentTransform->GetLocalFront(), glm::normalize(toTarget)));
	glm::vec3 cross = glm::normalize(glm::cross(_parentTransform->GetLocalFront(), glm::normalize(toTarget)));
	int s = glm::sign(cross.y);
	return yAngle * s;
}

//------------------------------
//Considered for removal
//------------------------------
/*float AIBase::GetReverseRotationToTarget() const
{
	glm::vec3 toTarget = glm::vec3(_targetTransform->GetPosition().x, _parentTransform->GetPosition().y, _targetTransform->GetPosition().z) - _parentTransform->GetPosition();
	float yAngle = glm::degrees(glm::angle(_parentTransform->GetLocalFront(), glm::normalize(toTarget))) - 180;
	glm::vec3 cross = glm::normalize(glm::cross(_parentTransform->GetLocalFront(), glm::normalize(toTarget)));
	int s = glm::sign(cross.y);
	return yAngle * s;
}

float AIBase::GetDistanceToNode() const
{
	return sqrt(pow(_nextNode.x - _parentTransform->GetPosition().x, 2) + pow(_nextNode.y - _parentTransform->GetPosition().y, 2) + pow(_nextNode.z - _parentTransform->GetPosition().z, 2));
}

float AIBase::GetRotationToNode() const
{
	glm::vec3 toTarget = glm::vec3(_nextNode.x, _parentTransform->GetPosition().y, _nextNode.z) - _parentTransform->GetPosition();
	float yAngle = glm::degrees(glm::angle(_parentTransform->GetLocalFront(), glm::normalize(toTarget)));
	glm::vec3 cross = glm::normalize(glm::cross(_parentTransform->GetLocalFront(), glm::normalize(toTarget)));
	int s = glm::sign(cross.y);
	return yAngle * s;
}

float AIBase::GetReverseRotationToNode() const
{
	glm::vec3 toTarget = glm::vec3(_nextNode.x, _parentTransform->GetPosition().y, _nextNode.z) - _parentTransform->GetPosition();
	float yAngle = glm::degrees(glm::angle(_parentTransform->GetLocalFront(), glm::normalize(toTarget))) - 180;
	glm::vec3 cross = glm::normalize(glm::cross(_parentTransform->GetLocalFront(), glm::normalize(toTarget)));
	int s = glm::sign(cross.y);
	return yAngle * s;
}*/
//------------------------------

Transform* AIBase::GetTarget() const
{
	return _targetTransform;
}

void AIBase::SetState(std::string state)
{
	if (state != _state)
	{
		_state = state;
		_lastStateChange = Timer::GetTimeS();
	}
}

std::string AIBase::GetState() const
{
	return _state;
}

void AIBase::SetEventReceived(bool received)
{
	_eventReceived = received;
}

bool AIBase::GetEventReceived() const
{
	return _eventReceived;
}

void AIBase::Move(float forward, float right)
{
	_parentTransform->SetPosition(_parentTransform->GetPosition() + (forward * _parentTransform->GetLocalFront()));
	_parentTransform->SetPosition(_parentTransform->GetPosition() + (right * _parentTransform->GetLocalRight()));
}

void AIBase::MoveForward(float forward)
{
	_parentTransform->SetPosition(_parentTransform->GetPosition() + (forward * _parentTransform->GetLocalFront()));
}

void AIBase::MoveRight(float right)
{
	_parentTransform->SetPosition(_parentTransform->GetPosition() + (right * _parentTransform->GetLocalRight()));
}

void AIBase::Rotate(float amount)
{
	_parentTransform->RotateBy(amount, 0, 1, 0);
}

//------------------------------
//To be updated
//------------------------------
/*void AIBase::SetAnimation(int index)
{
	//GetParent()->GetComponent<Animator>("Animator")->SetCurrentAnimation(index);
}*/
//------------------------------

void AIBase::Update()
{
	Think();
}

void AIBase::OnAttach(GameObject* go)
{
	_parentTransform = &go->transform;
}