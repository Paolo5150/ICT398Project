#pragma once
#include "RestAffordance.h"


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

		return nullptr;

	}
};