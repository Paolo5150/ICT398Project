#pragma once

#include "../Need.h"

/**
* @class Thirst
* @brief Child class of Need for tracking AI thirst
*
* @author Drew Paridaens
* @version 01
* @date 06/10/2019
*
*
* @bug No known bugs.
*/
class Thirst : public Need
{
public:
	Thirst(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier);
	~Thirst();
	bool Seek(AIEmotion* ai, AffordanceAgent* aa) override;
	void FinishSeek(AIEmotion* ai, AffordanceAgent* aa) override;
};

