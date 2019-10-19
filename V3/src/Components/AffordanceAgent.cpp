#include "pch.h"
#include "AffordanceAgent.h"
#include "AIEmotion.h"
namespace
{
	AIEmotion* ai;
}

AffordanceAgent::AffordanceAgent() : Component("AffordanceAgent")
{
	selectedObj = nullptr;
	inUseObj = nullptr;
}

AffordanceAgent::~AffordanceAgent()
{
	affordanceEngageCallbackMap.clear();
}

void AffordanceAgent::ExecuteAffordanceDisengageCallback(std::string affName)
{
	// If there's no affordance object in use, no need to disengage it
	if (selectedObj == nullptr || inUseObj == nullptr) return;

	if (inUseObj != nullptr)
	{
		auto it = affordanceDisengageCallbackMap.find(affName);

		if (it != affordanceDisengageCallbackMap.end())
		{
			it->second();
			inUseObj->ReleaseUse(_parent);
			inUseObj = nullptr;
			selectedObj = nullptr;
			selectedAffordanceName = "";
		}
	}
}
void AffordanceAgent::ExecuteAffordanceEngageCallback(std::string affName, AIEmotion* ai)
{

	if (inUseObj == nullptr)
	{
		auto it = affordanceEngageCallbackMap.find(affName);

		if (it != affordanceEngageCallbackMap.end())
		{
			it->second(selectedObj);
			selectedObj->ExecuteAffordanceCallback(affName, ai);
			inUseObj = selectedObj;
			selectedObj->AddUser(_parent);
		}
	}
}

void AffordanceAgent::ExecuteAffordanceUpdateCallback(std::string affName, AIEmotion * ai)
{
	if (inUseObj != nullptr)
	{
		auto it = affordanceUpdateCallbackMap.find(affName);

		if (it != affordanceUpdateCallbackMap.end())
		{
			it->second();
			selectedObj->ExecuteAffordanceUpdateCallback(affName, ai);
			inUseObj = selectedObj;
			selectedObj->AddUser(_parent);
		}
	}
}

bool AffordanceAgent::LookForBestScoreAffordanceObjectByAffordanceTypeInRange(Affordance::AffordanceTypes type, float range)
{
	if (inUseObj == nullptr)
	{
		if (selectedObj == nullptr)
		{
			selectedObj = AffordanceManager::Instance().GetBestScoreObjectByAffordanceTypeWithinRange(type,_parent->transform.GetGlobalPosition(), range,selectedAffordanceName);
			return selectedObj != nullptr;
		}
		else
			return true;
	}
	else
		return false;
}

bool AffordanceAgent::LookForBestScoreAffordanceObjectByAffordanceTypeInRangeNotTarget(Affordance::AffordanceTypes type, AffordanceObject * notTarget, float range)
{
	if (inUseObj == nullptr)
	{
		if (selectedObj == nullptr)
		{
			selectedObj = AffordanceManager::Instance().GetBestScoreObjectByAffordanceTypeWithinRangeNotTarget(type, _parent->transform.GetGlobalPosition(), range, selectedAffordanceName, notTarget);
			return selectedObj != nullptr;
		}
		else
			return true;
	}
	else
		return false;
}


void AffordanceAgent::Update()
{
	Component::Update();
	//Constantly check that the selected affordance object is not in use
	if (selectedObj != nullptr)
	{
		if (selectedObj->GetInUseAffordanceName() != "")
		{
			// If the selected affordance object is in use by someone else, unselect it
			if (!selectedObj->IsAvailableForAffordance(selectedObj->GetInUseAffordanceName()) && !selectedObj->IsGameObjectAUser(_parent))
			{
				selectedObj = nullptr;
			}
		}
	}

	if (inUseObj != nullptr)
	{
		ai = GetParent()->GetComponent<AIEmotion>("Emotion");
		ExecuteAffordanceUpdateCallback(GetSelectedAffordanceName(), ai);

	}
}

bool AffordanceAgent::HasInUseObject()
{
	return inUseObj != nullptr;
}

bool AffordanceAgent::LookForBestScoreAffordanceObjectInRange(std::string name, float range)
{
	if (IsAffordanceSupported(name) && inUseObj == nullptr)
	{
		if (1)
		{
			selectedObj = AffordanceManager::Instance().GetBestScoreObjectWithinRange(name, _parent->transform.GetGlobalPosition(), range);
			return selectedObj != nullptr;
		}
		else
			return true;
	}
	else
		return false;

}

bool AffordanceAgent::IsAffordanceSupported(std::string affName)
{

	auto objIt = affordanceEngageCallbackMap.find(affName);
	return objIt != affordanceEngageCallbackMap.end();

}


void AffordanceAgent::AddAffordanceDisengageCallback(std::string affName,std::function<void()> callback)
{
	affordanceDisengageCallbackMap[affName] = callback;
}

void AffordanceAgent::AddAffordanceUpdateCallback(std::string affName, std::function<void()> callback)
{
	affordanceUpdateCallbackMap[affName] = callback;
}


void AffordanceAgent::AddAffordanceEngageCallback(std::string affName,std::function<void(AffordanceObject*)> callback)
{
	affordanceEngageCallbackMap[affName] = callback;
}





