#pragma once
#include "..\Need.h"


/**
* @class Anger
* @brief Child class of Need for tracking AI anger
*
* @author Drew Paridaens
* @version 01
* @date 06/10/2019
*
*
* @bug No known bugs.
*/
class Anger :
	public Need
{
public:
	Anger(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier);
	~Anger();
	bool Seek(AIEmotion* ai, AffordanceAgent* aa) override;
	void FinishSeek(AIEmotion* ai, AffordanceAgent* aa) override;
};

