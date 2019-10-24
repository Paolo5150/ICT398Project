#pragma once
#include "RestAffordance.h"
#include "CollectableAffordances.h"
#include "ThirstAffordance.h"
#include "SocialAffordance.h"
#include "LightAffordance.h"

/**
* @class AffordanceFactory
* @brief Factory used to get specific Affordane object, by name
*
*
* @author Paolo Ferri
* @version 01
* @date 05/10/2019
*
*
* @bug No known bugs.
*/

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
		else if (name == "LightAffordance")
		{
			return new LightAffordance();
		}

		return nullptr;

	}
};