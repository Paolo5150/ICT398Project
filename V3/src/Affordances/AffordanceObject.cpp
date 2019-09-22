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


std::string AffordanceObject::GetInUseAffordanceName()
{ 
	if(inUse != nullptr)
	return FileUtils::GetClassNameW(inUse); 
	else return "";
};

bool AffordanceObject::IsGameObjectAUser(GameObject* user)
{
	auto it = users.begin();
	for (; it != users.end(); it++)
	{
		if ((*it) == user)
			return 1;
	}
	return 0;
}

void AffordanceObject::AddUser(GameObject* o)
{
	users.push_back(o);		
}
void AffordanceObject::RemoveUser(GameObject* o)
{
	auto it = users.begin();
	for (; it != users.end(); )
	{
		if ((*it) == o)
			it = users.erase(it);
		else
			it++;
	}
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

	//Logger::LogInfo("Object", gameObject->GetName(), "Users:", inUse->currentUsers, "Affordance:", afName);
}

void AffordanceObject::ReleaseUse(GameObject* o)
{
	RemoveUser(o);
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



