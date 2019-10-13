#pragma once
#include <string>
#include "Affordance.h"

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