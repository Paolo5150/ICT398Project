#include "pch.h"
#include "AffordanceManager.h"
#include "AffordanceObject.h"
#include "Affordance.h"

AffordanceManager& AffordanceManager::Instance()
{
	static AffordanceManager instance;
	return instance;
}

AffordanceManager::~AffordanceManager()
{

}

AffordanceManager::AffordanceManager()
{}

void AffordanceManager::RegisterAffordanceObject(AffordanceObject* obj)
{
	for (auto it = obj->perceivedAffordances.begin(); it != obj->perceivedAffordances.end(); it++)
	{
		affordanceMap[it->first].insert(obj);
		Logger::LogInfo("Affordance manager registered ", it->first, obj->gameObject->GetName());
	}
}

std::set<AffordanceObject*> AffordanceManager::GetAffordancesByType(int type)
{
	auto it = affordanceMap.find(type);

	if (it != affordanceMap.end())
	{
		return it->second;
	}
	std::set<AffordanceObject*> empty;
	return empty;
}

AffordanceObject* AffordanceManager::GetClosestAffordancesByType(int type, glm::vec3 position, float maxRange)
{
	AffordanceObject* closest = nullptr;

	std::set<AffordanceObject*> a = GetAffordancesByType(type);
	float length = 9999999999;
	if (!a.empty())
	{
		auto it = a.begin();
		for (; it != a.end(); it++)
		{
			float toAf = glm::length((*it)->gameObject->transform.GetGlobalPosition() - position);
			if (toAf < length && toAf < maxRange)
			{
				length = toAf;
				closest = (*it);
			}
		}
	}
	return closest;
}

std::set<AffordanceObject*> AffordanceManager::GetClosestAffordancesByTypeWithinRange(int type, glm::vec3 position, float maxRange)
{
	std::set<AffordanceObject*> a = GetAffordancesByType(type);
	std::set<AffordanceObject*> inRange;

	if (!a.empty())
	{
		auto it = a.begin();
		for (; it != a.end(); it++)
		{
			float toAf = glm::length((*it)->gameObject->transform.GetGlobalPosition() - position);
			if (toAf < maxRange)
			{
				inRange.insert((*it));
			}
		}
	}
	return inRange;
}
