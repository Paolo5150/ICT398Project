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


