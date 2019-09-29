#pragma once

#include <string>
#include <map>
#include <functional>
#include "AffordanceManager.h"
#include "..\Utils\FileUtils.h"

class Affordance;
class GameObject;

/**
* @class AffordanceObject
* @brief Defines an object that has perceived affordances
*
*
* @author Paolo Ferri
* @version 01
* @date 29/09/2019
*
*
* @bug No known bugs.
*/

class AffordanceObject
{
public:
	friend class AffordanceManager;

	/**
	* @brief		Creates object
	*/
	AffordanceObject(GameObject* go);

	/**
	* @brief		Destroy object
	*/
	virtual ~AffordanceObject() {};

	/**
	* @brief		Add affordance 
	* @param a		The new affordance
	*/
	void AddPerceviedAffordance(Affordance* a);

	/**
	* @brief		Pointer to the gameObject
	*/
	GameObject* gameObject;

	/**
	* @brief		Call to callback method for specified affordance name
	*/
	void ExecuteAffordanceCallback(std::string afName);

	/**
	* @brief		Check if object is being used
	* @return		TRUE if no other gameobject is currently using this object
	*/
	bool IsAvailableForAffordance(std::string);

	/**
	* @brief		Get which affordance of the object is being used
	* @return		The affordance being used
	*/
	Affordance* GetInUseAffordance() { return inUse; };

	/**
	* @brief		Get the name of the affordance in use
	* @return		The name of the affordance being used
	*/
	std::string GetInUseAffordanceName();

	/**
	* @brief		Check if gameobject is a user of this object
	* @param user	The game object to be checked
	* @return		TRUE if the argument is a user
	*/
	bool IsGameObjectAUser(GameObject* user);

	/**
	* @brief		Register a new user
	* @param user	The new game object user
	*/
	void AddUser(GameObject* user);

	/**
	* @brief		Return the score for the specified affordance
	* @return		The score for the specified affordance
	*/
	template <class T>
	int GetAffordanceScore();

	/**
	* @brief		Return the score for the specified affordance by affordance name
	* @param name	The affordance name
	* @return		The score for the specified affordance
	*/
	int GetAffordanceScore(std::string name);

	/**
	* @brief		Return the affordances of specified type
	* @param type	The type of affordances
	* @return		All affordances of that type for this object
	*/
	std::set<Affordance*> GetAffordancesOfType(Affordance::AffordanceTypes type);

	/**
	* @brief		Return al laffordances
	* @return		All affordances
	*/
	std::vector<Affordance*> GetPerceivedAffordances();

	/**
	* @brief		Get affordance with best score of specified type
	* @param type	The type
	* @return		The affordance with best score of specified type
	*/
	Affordance* GetBestAffordanceOfType(Affordance::AffordanceTypes type);

	/**
	* @brief		Disengage this object by users
	* @param user	The user to be unregistered
	*/
	void ReleaseUse(GameObject* o);

private:
	/**
	* @brief		Unregister specified gameobject as user
	*/
	void RemoveUser(GameObject* o);

	/**
	* @brief		The affordance being used
	*/
	Affordance* inUse;

	/**
	* @brief		Map of affordances by name
	*/
	std::map<std::string,std::unique_ptr<Affordance>> perceivedAffordancesByName;  

	/**
	* @brief		Map of affordances by type
	*/
	std::map<Affordance::AffordanceTypes, std::set<Affordance*>> perceivedAffordancesByType;

	/**
	* @brief		Users of this object
	*/
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