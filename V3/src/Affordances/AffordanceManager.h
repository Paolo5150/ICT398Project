#pragma once

#include <map>
#include <set>

#include "..\Core\Logger.h"
#include "..\Core\GameObject.h"
#include "Affordance.h"

class AffordanceObject;


class AffordanceManager
{
public:

	static AffordanceManager& Instance();
	~AffordanceManager() ;
	void RegisterAffordanceObject(std::string, AffordanceObject* obj);	

	template <class T>
	std::vector<AffordanceObject*> GetObjectsOfTypeWithinRange(glm::vec3 pos, float range);

	template <class T>
	AffordanceObject* GetBestScoreObjectWithinRange(glm::vec3 pos, float range);

	AffordanceObject* GetBestScoreObjectByAffordanceTypeWithinRange(Affordance::AffordanceTypes type, glm::vec3 pos, float range, std::string& outAffordanceName);



private:
	AffordanceManager();
	std::map<std::string, std::set<AffordanceObject*>> affordanceMapByAffordanceName;
	std::map<Affordance::AffordanceTypes, std::set<AffordanceObject*>> affordanceMapByAffordanceType;

};


template <class T>
std::vector<AffordanceObject*> AffordanceManager::GetObjectsOfTypeWithinRange(glm::vec3 pos, float range)
{
	std::vector<AffordanceObject*> r;
	std::string name = FileUtils::GetClassNameW<T>();

	auto it = affordanceMapByAffordanceName.find(name);
	if (it != affordanceMapByAffordanceName.end())
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

template <class T>
AffordanceObject* AffordanceManager::GetBestScoreObjectWithinRange(glm::vec3 pos, float range)
{
	std::string name = FileUtils::GetClassNameW<T>();

	std::vector<AffordanceObject*> r = GetObjectsOfTypeWithinRange<T>(pos, range);
	std::vector<AffordanceObject*> bestScore;

	int max = -HUGE;
	// Find max
	for (int i = 0; i < r.size(); i++)
	{
		int score = r[i]->GetAffordanceScore(name);
		if (score >= max)
		{
			max = score;
		}
	}

	for (int i = 0; i < r.size(); i++)
	{
		int score = r[i]->GetAffordanceScore(name);
		if (score == max)
			bestScore.push_back(r[i]);
	}

	AffordanceObject* ret = nullptr;
	// If there's more than one affordance obj with high same score, get closest one
	if (bestScore.size() > 1)
	{
		float length2 = HUGE;
		for (int i = 0; i < bestScore.size(); i++)
		{
			float lenngth = glm::length2(bestScore[i]->gameObject->transform.GetGlobalPosition() - pos);
			if (lenngth < length2)
			{
				length2 = lenngth;
				ret = bestScore[i];
			}
		}
	}
	else if(bestScore.size() == 1)
		ret = bestScore[0];

	return ret;

}


