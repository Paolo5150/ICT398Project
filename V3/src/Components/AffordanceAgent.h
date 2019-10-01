#pragma once
#include "..\Affordances\Affordance.h"
#include "..\Affordances\AffordanceManager.h"
#include "..\Affordances\AffordanceObject.h"
#include "..\Core\Component.h"
#include "..\Utils\FileUtils.h"



class AffordanceAgent : public Component
{
public:
	AffordanceAgent();
	virtual ~AffordanceAgent();

	void AddAffordanceEngageCallback(std::string affordanceName, std::function<void(AffordanceObject*)>);

	bool IsAffordanceSupported(std::string affordanceName);

	void AddAffordanceDisengageCallback(std::string affordanceName, std::function<void()>);

	void ExecuteAffordanceDisengageCallback(std::string name);
	void ExecuteAffordanceEngageCallback(std::string name);

	bool LookForBestScoreAffordanceObjectByAffordanceTypeInRange(Affordance::AffordanceTypes type, float range);

	bool LookForBestScoreAffordanceObjectInRange(std::string affordanceName, float range);

	AffordanceObject* selectedObj;

	void Update() override;

	std::string& GetSelectedAffordanceName() { return selectedAffordanceName; }

protected:

	std::map<std::string, std::function<void(AffordanceObject*)>> affordanceEngageCallbackMap;
	std::map<std::string, std::function<void()>> affordanceDisengageCallbackMap;

	AffordanceObject* inUseObj;
	std::string selectedAffordanceName; //Used when looking for affordance objs by type
};



