#pragma once
#include "../Need.h"

/**
* @class Rest
* @brief Child class of Need for tracking AI rest
*
* @author Drew Paridaens
* @version 01
* @date 06/10/2019
*
*
* @bug No known bugs.
*/
class Rest :
	public Need
{
public:
	Rest(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier);
	~Rest();
	bool Seek(AIEmotion* ai, AffordanceAgent* aa) override;
	void FinishSeek(AIEmotion* ai, AffordanceAgent* aa) override;
};

