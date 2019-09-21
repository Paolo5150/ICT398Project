#pragma once

#include <string>
#include <map>
#include <functional>
#include "AffordanceManager.h"

class Affordance;
class GameObject;

class AffordanceObject
{
public:
	friend class AffordanceManager;
	AffordanceObject(GameObject* go);
	virtual ~AffordanceObject() {};
	void AddPerceviedAffordance(Affordance* a);
	GameObject* gameObject;

	void ExecuteAffordanceCallback(std::string afName);
	bool IsAvailableForAffordance(std::string);
	Affordance* GetInUseAffordance() { return inUse; };
	void ReleaseUse();

private:
	Affordance* inUse;
	std::map<std::string,std::unique_ptr<Affordance>> perceivedAffordances;





};

