#include "AIBase.h"
#include <thread>
#include <future>

AIBase::AIBase() : Component("AIBase")
{
	_type = "AI";
	SetState("");
	_parentTransform = nullptr;
	_targetTransform = nullptr;
	_otherTarget.x = -1;
	_otherTarget.y = -1;
	_otherTarget.z = -1;
	_nextNode.x = -1;
	_nextNode.y = -1;
	_nextNode.z = -1;
	_lastStateChange = 0.0f;
	_randomTimer = 0.0f;
	_updateTimer = 0.0f;
	_eventReceived = false;
}

AIBase::AIBase(Transform& targetTransform) : Component("AIBase")
{
	_type = "AI";
	SetState("");
	_parentTransform = nullptr;
	SetTarget(targetTransform);
	_otherTarget.x = -1;
	_otherTarget.y = -1;
	_otherTarget.z = -1;
	_nextNode.x = -1;
	_nextNode.y = -1;
	_nextNode.z = -1;
	_lastStateChange = 0.0f;
	_randomTimer = 0.0f;
	_updateTimer = 0.0f;
	_eventReceived = false;
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

float AIBase::GetReverseRotationToTarget() const
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
}

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

void AIBase::SetAnimation(int index)
{
	GetParent()->GetComponent<Animator>("Animator")->SetCurrentAnimation(index);
}

glm::vec3 Test(glm::vec3 position, glm::vec3 target)
{
	return PathFinder::Instance().GeneratePath(position, target).at(0);
}

void AIBase::Update()
{
	if (Timer::GetTimeS() >= _updateTimer + 0.5f)
	{
		_updateTimer = Timer::GetTimeS();
		if (_otherTarget.x != -1 && _otherTarget.y != -1 && _otherTarget.z != -1)
		{
			auto f1 = std::async(std::launch::async, Test, _parentTransform->GetPosition(), _otherTarget);
			_nextNode = f1.get();
		}
		else if (_targetTransform != nullptr)
		{
		//	_nextNode = PathFinder::Instance().GeneratePath(_parentTransform->GetPosition(), _targetTransform->GetPosition()).at(0);
			auto f1 = std::async(std::launch::async, Test, _parentTransform->GetPosition(), _targetTransform->GetPosition());
			_nextNode = f1.get();
		}
	}

	Think();
}

void AIBase::OnAttach(GameObject* go)
{
	_parentTransform = &go->transform;
}

void AIBase::Think()
{

}

void AIBase::DumpVariables()
{
	Logger::LogInfo("State: ", GetState());
	Logger::LogInfo("DistanceToTarget: ", GetDistanceToTarget());
	Logger::LogInfo("RotationToTarget: ", GetRotationToTarget());
	Logger::LogInfo("ReverseRotationToTarget: ", GetReverseRotationToTarget());
	Logger::LogInfo("DistanceToNode: ", GetDistanceToNode());
	Logger::LogInfo("RotationToNode: ", GetRotationToNode());
	Logger::LogInfo("ReverseRotationToNode: ", GetReverseRotationToNode());
	Logger::LogInfo("OtherTargetX: ", _otherTarget.x);
	Logger::LogInfo("OtherTargetY: ", _otherTarget.y);
	Logger::LogInfo("OtherTargetZ: ", _otherTarget.z);
	//Logger::LogInfo("TerrainMaxX: ", Terrain::Instance().GetTerrainMaxX());
	//Logger::LogInfo("TerrainMaxZ: ", Terrain::Instance().GetTerrainMaxZ());
	Logger::LogInfo("TimeS: ", Timer::GetTimeS());
	Logger::LogInfo("DeltaS: ", Timer::GetDeltaS());
	Logger::LogInfo("LastStateChange: ", _lastStateChange);
	Logger::LogInfo("RandomTimer: ", _randomTimer);
	Logger::LogInfo("EventReceived: ", _eventReceived);
}