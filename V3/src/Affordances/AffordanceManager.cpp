#include "pch.h"
#include "AffordanceManager.h"
#include "AffordanceObject.h"
#include "Affordance.h"
#include "..\Events\ApplicationEvents.h"
#include "..\Events\EventDispatcher.h"

AffordanceManager& AffordanceManager::Instance()
{
	static AffordanceManager instance;
	return instance;
}

AffordanceManager::~AffordanceManager()
{

}

AffordanceManager::AffordanceManager()
{
	// When the scene changes, removes all canvas and recreate the main one as per default
	EventDispatcher::Instance().SubscribeCallback<SceneChangedEvent>([this](Event* e) {
		affordanceMapByAffordanceName.clear();
		affordanceMapByAffordanceType.clear();
	
		return 0;
	});
	
}

AffordanceObject* AffordanceManager::GetBestScoreObjectByAffordanceTypeWithinRange(Affordance::AffordanceTypes type, glm::vec3 pos, float range, std::string& outAffordanceName)
{
	AffordanceObject* r = nullptr;
	int maxScore = -HUGE;
	auto it = affordanceMapByAffordanceType.find(type);

	if (it != affordanceMapByAffordanceType.end())
	{
		std::set<AffordanceObject*> inRange;


		//Get the objects in range first
		for (auto objIt = it->second.begin(); objIt != it->second.end(); objIt++)
		{
			float length2 = glm::length2((*objIt)->gameObject->transform.GetGlobalPosition() - pos);
			if (length2 < range * range)
			{				
				inRange.insert((*objIt));
			}

		}

		int maxScore = -HUGE;
		//Get top score of objects in range
		for (auto best = inRange.begin(); best != inRange.end(); best++)
		{
			Affordance* af = (*best)->GetBestAffordanceOfType(type);
			if (af)
			{
				std::string name = FileUtils::GetClassNameW(af);
				if (af->GetScore() > maxScore && (*best)->IsAvailableForAffordance(name))
				{
					maxScore = af->GetScore();			
				}
			}
		}

		//Get all objects with an affordance of that score
		std::set<AffordanceObject*> bestObjs;
		for (auto best = inRange.begin(); best != inRange.end(); best++)
		{
			Affordance* af = (*best)->GetBestAffordanceOfType(type);
			if (af)
			{
				std::string name = FileUtils::GetClassNameW(af);

				if (af->GetScore() == maxScore && (*best)->IsAvailableForAffordance(name))
				{
					bestObjs.insert((*best));
				}
			}
		
		}

		//If there's more than 1 object with that score, get the closet to the position
		float shortest = HUGE;
		for (auto best = bestObjs.begin(); best != bestObjs.end(); best++)
		{
			float length2 = glm::length2((*best)->gameObject->transform.GetGlobalPosition() - pos);
			Affordance* af = (*best)->GetBestAffordanceOfType(type);
			std::string name = FileUtils::GetClassNameW(af);
			if (length2 < shortest && (*best)->IsAvailableForAffordance(name))
			{
				shortest = length2;
				r = (*best);
				outAffordanceName = name;
			}
		}

		
	}
	
	return r;
}


void AffordanceManager::RegisterAffordanceObject(std::string affName,AffordanceObject* obj)
{
	affordanceMapByAffordanceName[affName].insert(obj);
	
	std::vector<Affordance*> aff = obj->GetPerceivedAffordances();

	for (int i = 0; i < aff.size(); i++)
	{
		affordanceMapByAffordanceType[aff[i]->affordanceType].insert(obj);
	}

}


std::vector<AffordanceObject*> AffordanceManager::GetObjectsOfTypeWithinRange(std::string name, glm::vec3 pos, float range)
{
	std::vector<AffordanceObject*> r;

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

AffordanceObject* AffordanceManager::GetBestScoreObjectWithinRange(std::string name, glm::vec3 pos, float range)
{
	std::vector<AffordanceObject*> r = GetObjectsOfTypeWithinRange(name,pos, range);
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
	else if (bestScore.size() == 1)
		ret = bestScore[0];

	return ret;

}


