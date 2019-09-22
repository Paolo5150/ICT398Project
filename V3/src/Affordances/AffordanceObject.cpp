#include "pch.h"
#include "AffordanceObject.h"
#include "Affordance.h"
#include "AffordanceManager.h"
#include "..\Utils\FileUtils.h"

AffordanceObject::AffordanceObject(GameObject* go) {
	gameObject = go;
	inUse = nullptr;
};

void AffordanceObject::AddPerceviedAffordance(Affordance* a)
{
	std::string name = FileUtils::GetClassNameW(a);
	perceivedAffordances[name] = std::unique_ptr<Affordance>(a);
	perceivedAffordances[name]->currentUsers = 0;
	AffordanceManager::Instance().RegisterAffordanceObject(name, this);
}




bool AffordanceObject::IsAvailableForAffordance(std::string affName)
{
	if (inUse == nullptr)
	{

		auto it = perceivedAffordances.find(affName);
		if (it != perceivedAffordances.end())
		{
			return it->second->currentUsers < it->second->maxUsers;
		}
	}
	else
	{
		return inUse->currentUsers < inUse->maxUsers;
	}
	return false;
}

void AffordanceObject::ExecuteAffordanceCallback(std::string afName)
{
	auto it = perceivedAffordances.find(afName);
	if (it != perceivedAffordances.end())
	{
		it->second->Callback();
		inUse = it->second.get();
		inUse->currentUsers++;
	}
}

void AffordanceObject::ReleaseUse()
{
	inUse->currentUsers--;
	if (inUse->currentUsers <= 0)
	{
		inUse->currentUsers = 0;
		inUse = nullptr;
	}
}

int AffordanceObject::GetAffordanceScore(std::string name)
{
	auto it = perceivedAffordances.find(name);
	if (it != perceivedAffordances.end())
	{
		return it->second->GetScore();
	}
	return -1;
}



