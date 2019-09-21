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
private:

	std::map<int,std::set<std::unique_ptr<Affordance>>> perceivedAffordances;


};

