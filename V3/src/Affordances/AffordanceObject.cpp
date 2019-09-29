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
	perceivedAffordancesByName[name] = std::unique_ptr<Affordance>(a);
	perceivedAffordancesByName[name]->currentUsers = 0;
	perceivedAffordancesByType[a->affordanceType].insert(a);

	AffordanceManager::Instance().RegisterAffordanceObject(name, this);
}

std::set<Affordance*> AffordanceObject::GetAffordancesOfType(Affordance::AffordanceTypes type)
{
	std::set<Affordance*> a;

	auto it = perceivedAffordancesByType.find(type);

	if (it != perceivedAffordancesByType.end())
		return it->second;

	return a;

}

Affordance* AffordanceObject::GetBestAffordanceOfType(Affordance::AffordanceTypes type)

{
	Affordance* af = nullptr;

	int maxScore = -HUGE;
	auto it = perceivedAffordancesByType.find(type);
	if (it != perceivedAffordancesByType.end())
	{
		auto affIt = it->second.begin();

		for (; affIt != it->second.end(); affIt++)
		{
			if ((*affIt)->GetScore() > maxScore)
			{
				maxScore = (*affIt)->GetScore();
				af = (*affIt);
			}
		}
	}

	return af;
}


std::vector<Affordance*> AffordanceObject::GetPerceivedAffordances()
{
	std::vector<Affordance*> r;

	auto it = perceivedAffordancesByName.begin();
	
	for (; it != perceivedAffordancesByName.end(); it++)
	{
		r.push_back(it->second.get());
	}

	return r;
}



std::string AffordanceObject::AffordanceObject::GetInUseAffordanceName()
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
		auto it = perceivedAffordancesByName.find(affName);
		if (it != perceivedAffordancesByName.end())
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
	auto it = perceivedAffordancesByName.find(afName);
	if (it != perceivedAffordancesByName.end())
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
	auto it = perceivedAffordancesByName.find(name);
	if (it != perceivedAffordancesByName.end())
	{
		return it->second->GetScore();
	}
	return -1;
}



