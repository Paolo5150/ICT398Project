#pragma once
#include "RestAffordance.h"
#include "CollectableAffordances.h"
#include "ThirstAffordance.h"
#include "SocialAffordance.h"

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
		else if (name == "ThirstAffordance")
		{
			return new ThirstAffordance();
		}
		else if (name == "SocialAffordance")
		{
			return new SocialAffordance();
		}

		return nullptr;

	}
};