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
	/**
	* @brief		Get instance
	*/
	static AffordanceManager& Instance();

	/**
	* @brief		Destroy object
	*/
	~AffordanceManager() ;

	/**
	* @brief					Register an affordance object
	* @param affordanceName		The name of the affordance to register the object against
	* @param obj				The object to be registered
	*/
	void RegisterAffordanceObject(std::string affordanceName, AffordanceObject* obj);	


	/**
	* @brief					Get list of AffordanceObject in specified range
	* @param pos				The position of the check point
	* @param range				The range
	* @return					The affordance objects in range
	*/
	std::vector<AffordanceObject*> GetObjectsOfTypeWithinRange(std::string affName,glm::vec3 pos, float range);

	/**
	* @brief					Get best affordance object with specific affordance within range
	* @param pos				The position of the check point
	* @param range				The range
	* @return					The best affordance object in range
	*/
	AffordanceObject* GetBestScoreObjectWithinRange(std::string affName, glm::vec3 pos, float range);

	/**
	* @brief					Get best affordance object by typewithin range
	* @param type				The type of the affordance object
	* @param pos				The position of the check point
	* @param range				The range
	* @return					The best affordance object in range
	*/
	AffordanceObject* GetBestScoreObjectByAffordanceTypeWithinRange(Affordance::AffordanceTypes type, glm::vec3 pos, float range, std::string& outAffordanceName);



private:
	AffordanceManager();
	std::map<std::string, std::set<AffordanceObject*>> affordanceMapByAffordanceName;
	std::map<Affordance::AffordanceTypes, std::set<AffordanceObject*>> affordanceMapByAffordanceType;

};




