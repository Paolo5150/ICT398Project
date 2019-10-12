#pragma once
#include "RestAffordance.h"
#include "CollectableAffordances.h"

class AffordanceFactory
{
public:
	static Affordance* GetAffordanceByName(std::string name)
	{
		if (name == "SitAffordance")
		{
			return new SitAffordance();
		}
		else if (name == "LaydownAffordance")
		{
			return new LaydownAffordance();
		}
		else if (name == "CollectableAffordance")
		{
			return new CollectableAffordance();
		}

		return nullptr;

	}
};