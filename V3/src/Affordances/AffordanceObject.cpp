#include "pch.h"
#include "AffordanceObject.h"
#include "Affordance.h"
#include "AffordanceManager.h"
#include "..\Utils\FileUtils.h"
#include "AffordanceFactory.h"

AffordanceObject::AffordanceObject(GameObject* go) {
	gameObject = go;
	inUse = nullptr;
};

void AffordanceObject::AddPerceviedAffordance(Affordance* a)
{
	std::string name = FileUtils::GetClassNameW(a);
	perceivedAffordancesByName[name] = std::unique_ptr<Affordance>(a);
	perceivedAffordancesByName[name]->SetCurrentUsers(0);
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

void AffordanceObject::LoadAffordancesFromFile(std::string filePath)
{
	if (FileUtils::IsFileThere(filePath))
	{
		FILE* file = NULL;
		file = fopen(filePath.c_str(), "r");


		while (!feof(file))
		{
			char line[200];
			std::string name;
			int score;

			char c	= fgetc(file);
		//	Logger::LogInfo("Char", c);

			if (c == ' ' || c == '\0' || c == '#')
			{
				fgets(line, 200, file);
				continue;
			}
			if (c == '\n') continue;


			// Get prefab name
			for (int j = 0; j < 100; j++)
			{
				if (c != ' ')
					line[j] = c;
				else
				{
					line[j] = '\0';
					break;
				}
				c = fgetc(file);
			}


			name = std::string(line);
			fscanf(file,"%d", &score);

			Affordance* af = AffordanceFactory::GetAffordanceByName(name);
			if (af)
			{
			af->SetScore(score);
			AddPerceviedAffordance(af);

			}
		}
	}
	else
		Logger::LogError("Failed to locate AFFORDANCE FILE", filePath);
}



bool AffordanceObject::IsAvailableForAffordance(std::string affName)
{
	if (inUse == nullptr)
	{
		auto it = perceivedAffordancesByName.find(affName);
		if (it != perceivedAffordancesByName.end())
		{
			return it->second->GetCurrentUsers() < it->second->GetMaxUsers();
		}
	}
	else
	{
		return inUse->GetCurrentUsers() < inUse->GetMaxUsers();
	}
	return false;
}

void AffordanceObject::ExecuteAffordanceCallback(std::string afName, AIEmotion* ai)
{
	auto it = perceivedAffordancesByName.find(afName);
	if (it != perceivedAffordancesByName.end())
	{
		it->second->Callback(ai);
		inUse = it->second.get();
		inUse->currentUsers++;
	}

	//Logger::LogInfo("Object", gameObject->GetName(), "Users:", inUse->currentUsers, "Affordance:", afName);
}

void AffordanceObject::ExecuteAffordanceUpdateCallback(std::string afName, AIEmotion * ai)
{
	auto it = perceivedAffordancesByName.find(afName);
	if (it != perceivedAffordancesByName.end())
	{
		it->second->UpdateCallback(ai);
		inUse = it->second.get();
	}
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



