#pragma once

#include <string>
#include <map>
#include <functional>
#include "AffordanceManager.h"
#include "..\Utils\FileUtils.h"

class Affordance;
class GameObject;

class AffordanceObject
{
public:
	friend class AffordanceManager;
	AffordanceObject(GameObject* go);
	virtual ~AffordanceObject() {};
	void AddPerceviedAffordance(Affordance* a);
	GameObject* gameObject;

	void ExecuteAffordanceCallback(std::string afName);
	bool IsAvailableForAffordance(std::string);
	Affordance* GetInUseAffordance() { return inUse; };
	std::string GetInUseAffordanceName();

	bool IsGameObjectAUser(GameObject* user);
	void AddUser(GameObject* o);

	template <class T>
	int GetAffordanceScore();

	int GetAffordanceScore(std::string name);
	std::set<Affordance*> GetAffordancesOfType(Affordance::AffordanceTypes type);

	std::vector<Affordance*> GetPerceivedAffordances();

	Affordance* GetBestAffordanceOfType(Affordance::AffordanceTypes type);

	void ReleaseUse(GameObject* o);

private:
	void RemoveUser(GameObject* o);
	Affordance* inUse;
	std::map<std::string,std::unique_ptr<Affordance>> perceivedAffordancesByName;  	
	std::map<Affordance::AffordanceTypes, std::set<Affordance*>> perceivedAffordancesByType;

	std::list<GameObject*> users;

};

template <class T>
int AffordanceObject::GetAffordanceScore()
{
	std::string name = FileUtils::GetClassNameW<T>();

	auto it = perceivedAffordancesByName.find(name);
	if (it != perceivedAffordancesByName.end())
	{
		return it->second->GetScore();
	}
	return -1;
}