#pragma once

#include <map>
#include <set>

#include "..\Core\Logger.h"
#include "..\Core\GameObject.h"

class AffordanceObject;


class AffordanceManager
{
public:

	static AffordanceManager& Instance();
	~AffordanceManager() ;
	void RegisterAffordanceObject(std::string, AffordanceObject* obj);	

	template <class T>
	std::vector<AffordanceObject*> GetObjectsOfTypeWithinRange(glm::vec3 pos, float range);


private:
	AffordanceManager();
	std::map<std::string, std::set<AffordanceObject*>> affordanceMap;


};


template <class T>
std::vector<AffordanceObject*> AffordanceManager::GetObjectsOfTypeWithinRange(glm::vec3 pos, float range)
{
	std::vector<AffordanceObject*> r;
	std::string name = FileUtils::GetClassNameW<T>();

	auto it = affordanceMap.find(name);
	if (it != affordanceMap.end())
	{
		auto objIt = it->second.begin();
		
		for (; objIt != it->second.end(); objIt++)
		{
			if ((*objIt)->IsAvailableForAffordance(name))
			{
				float length = glm::length((*objIt)->gameObject->transform.GetGlobalPosition() - pos);
				if (length < range)
					r.push_back(*objIt);
			}
		}
	}

	return r;
}


