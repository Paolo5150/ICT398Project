#pragma once
#include "..\Affordances\Affordance.h"
#include "..\Affordances\AffordanceManager.h"
#include "..\Affordances\AffordanceObject.h"
#include "..\Core\Component.h"
#include "..\Utils\FileUtils.h"

class AIEmotion;

class AffordanceAgent : public Component
{
public:
	AffordanceAgent();
	virtual ~AffordanceAgent();

	void AddAffordanceEngageCallback(std::string affordanceName, std::function<void(AffordanceObject*)>);

	bool IsAffordanceSupported(std::string affordanceName);

	void AddAffordanceDisengageCallback(std::string affordanceName, std::function<void()>);
	
	void AddAffordanceUpdateCallback(std::string affordanceName, std::function<void()>);

	void ExecuteAffordanceDisengageCallback(std::string name);
	void ExecuteAffordanceEngageCallback(std::string name, AIEmotion*);
	void ExecuteAffordanceUpdateCallback(std::string name, AIEmotion* ai);

	bool LookForBestScoreAffordanceObjectByAffordanceTypeInRange(Affordance::AffordanceTypes type, float range);
	bool LookForBestScoreAffordanceObjectByAffordanceTypeInRangeNotTarget(Affordance::AffordanceTypes type, AffordanceObject* notObj, float range);

	bool LookForBestScoreAffordanceObjectInRange(std::string affordanceName, float range);

	AffordanceObject* selectedObj;

	void Update() override;

	std::string& GetSelectedAffordanceName() { return selectedAffordanceName; }

	bool HasInUseObject();

	AffordanceObject* inUseObj;
protected:

	std::map<std::string, std::function<void(AffordanceObject*)>> affordanceEngageCallbackMap;
	std::map<std::string, std::function<void()>> affordanceUpdateCallbackMap;
	std::map<std::string, std::function<void()>> affordanceDisengageCallbackMap;

	std::string selectedAffordanceName; //Used when looking for affordance objs by type
};



