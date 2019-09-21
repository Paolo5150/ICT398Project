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

	void RegisterAffordanceObject(AffordanceObject* obj);
	std::set<AffordanceObject*> GetAffordancesByType(int type);
	AffordanceObject* GetClosestAffordancesByType(int type, glm::vec3 position, float maxRange);
	std::set<AffordanceObject*> GetClosestAffordancesByTypeWithinRange(int type, glm::vec3 position, float maxRange);



private:
	AffordanceManager();
	std::map<int, std::set<AffordanceObject*>> affordanceMap;


};


