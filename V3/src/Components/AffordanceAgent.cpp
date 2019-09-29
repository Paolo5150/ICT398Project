#include "pch.h"
#include "AffordanceAgent.h"


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
void AffordanceAgent::ExecuteAffordanceEngageCallback(std::string affName)
{

	if (inUseObj == nullptr)
	{
		auto it = affordanceEngageCallbackMap.find(affName);

		if (it != affordanceEngageCallbackMap.end())
		{
			it->second(selectedObj);
			selectedObj->ExecuteAffordanceCallback(affName);
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
}


