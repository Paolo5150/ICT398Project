#pragma once
#include "..\Need.h"

/**
* @class Joy
* @brief Child class of Need for tracking AI joy
*
* @author Drew Paridaens
* @version 01
* @date 06/10/2019
*
*
* @bug No known bugs.
*/
class Joy :
	public Need
{
public:
	Joy(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier);
	~Joy();
	bool Seek(AIEmotion* ai, AffordanceAgent* aa) override;
	void FinishSeek(AIEmotion* ai, AffordanceAgent* aa) override;
};

