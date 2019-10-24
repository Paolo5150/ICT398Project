#pragma once
#include <string>
#include "Affordance.h"

/**
* @class CollectableAffordance
* @brief Defines an affordance of type COLLECTABLE
*
*
* @author Paolo Ferri
* @version 01
* @date 20/10/2019
*
*
* @bug No known bugs.
*/
class CollectableAffordance : public Affordance
{
public:
	CollectableAffordance()
	{
		score = 50;
		affordanceType = AffordanceTypes::COLLECTABLE;
		affordanceName = "CollectableAffordance";
		Callback = [](AIEmotion* ai) { };
		UpdateCallback = [](AIEmotion* ai) { };
	}
	virtual ~CollectableAffordance() {};


};