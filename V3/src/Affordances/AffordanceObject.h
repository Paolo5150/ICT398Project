#pragma once

#include <string>
#include <map>
#include <functional>
#include "AffordanceManager.h"

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

	template <class T>
	int GetAffordanceScore();

	int GetAffordanceScore(std::string name);


	void ReleaseUse();

private:
	Affordance* inUse;
	std::map<std::string,std::unique_ptr<Affordance>> perceivedAffordances;  	 

};

template <class T>
int AffordanceObject::GetAffordanceScore()
{
	std::string name = FileUtils::GetClassNameW<T>();

	auto it = perceivedAffordances.find(name);
	if (it != perceivedAffordances.end())
	{
		return it->second->GetScore();
	}
	return -1;
}