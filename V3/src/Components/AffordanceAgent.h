#pragma once
#include "..\Affordances\Affordance.h"
#include "..\Affordances\AffordanceManager.h"
#include "..\Affordances\AffordanceObject.h"
#include "..\Core\Component.h"
#include "..\Utils\FileUtils.h"

class AIEmotion;

/**
* @class AffordanceAgent
* @brief Defines a component specialized in dealing with affordances objects
*
*
* @author Paolo Ferri
* @version 01
* @date 10/10/2019
*
*
* @bug No known bugs.
*/

class AffordanceAgent : public Component
{
public:
	/**
	* @brief		Constructor
	* @pre			The component does not exist
	* @post			The component is created
	*/
	AffordanceAgent();

	/**
	* @brief		Destructor
	* @pre			The component must exist
	* @post			The component is destroyed
	*/
	virtual ~AffordanceAgent();

	/**
	* @brief					Register engage callback
	* @param affordanceName		The name of the associated affordance
	* @param callback			The callback function
	*/
	void AddAffordanceEngageCallback(std::string affordanceName, std::function<void(AffordanceObject*)> callback);

	/**
	* @brief					Checks if a specified affordance is supported (callbakc registered)
	* @param affordanceName		The name of the associated affordance
	* @return					TRUE if the specified affordance is supported
	*/
	bool IsAffordanceSupported(std::string affordanceName);


	/**
	* @brief					Register disengage callback
	* @param affordanceName		The name of the associated affordance
	* @param callback			The callback function
	*/
	void AddAffordanceDisengageCallback(std::string affordanceName, std::function<void()>);
	
	/**
	* @brief					Register update callback
	* @param affordanceName		The name of the associated affordance
	* @param callback			The callback function
	*/
	void AddAffordanceUpdateCallback(std::string affordanceName, std::function<void()>);

	/**
	* @brief					Call disengage callback
	* @param affordanceName		The name of the associated affordance
	*/
	void ExecuteAffordanceDisengageCallback(std::string affordanceName);
	/**
	* @brief					Call engage callback
	* @param affordanceName		The name of the associated affordance
	* @param ai					The AIEmotion affected
	*/
	void ExecuteAffordanceEngageCallback(std::string affordanceName, AIEmotion* ai);
	/**
	* @brief					Call update callback
	* @param affordanceName		The name of the associated affordance
	* @param ai					The AIEmotion affected
	*/
	void ExecuteAffordanceUpdateCallback(std::string affordanceName, AIEmotion* ai);


	/**
	* @brief					Get best affordance object of type within range
	* @param type				The affordance type to look for
	* @param range				The range limit
	* @return					TRUE if an affordance object of specified type withing range was found
	*/
	bool LookForBestScoreAffordanceObjectByAffordanceTypeInRange(Affordance::AffordanceTypes type, float range);

	/**
	* @brief					Get best affordance object of type within range
	* @param type				The affordance type to look for
	* @param notObj				
	* @param range				The range limit
	* @return					TRUE if an affordance object of specified type withing range was found
	*/
	bool LookForBestScoreAffordanceObjectByAffordanceTypeInRangeNotTarget(Affordance::AffordanceTypes type, AffordanceObject* notObj, float range);


	/**
	* @brief					Get best affordance object by name within range
	* @param affordanceName		The name of the affordance to look for
	* @param range				The range limit
	* @return					TRUE if an affordance object of specified type withing range was found
	*/
	bool LookForBestScoreAffordanceObjectInRange(std::string affordanceName, float range);

	/**
	* @brief					The found affordance object
	*/
	AffordanceObject* selectedObj;

	/**
	* @brief					Update callback from engine
	*/
	void Update() override;

	/**
	* @brief					Returns the name of the affordance in use by agent
	*/
	std::string& GetSelectedAffordanceName() { return selectedAffordanceName; }

	/**
	* @brief					Returns true if the agent is using an affordance object
	*/
	bool HasInUseObject();

	/**
	* @brief					The affordance object in use
	*/
	AffordanceObject* inUseObj;
protected:

	std::map<std::string, std::function<void(AffordanceObject*)>> affordanceEngageCallbackMap;
	std::map<std::string, std::function<void()>> affordanceUpdateCallbackMap;
	std::map<std::string, std::function<void()>> affordanceDisengageCallbackMap;

	std::string selectedAffordanceName; //Used when looking for affordance objs by type
};



