#pragma once
#include "..\Need.h"

/**
* @class Anticipation
* @brief Child class of Need for tracking AI anticipation
*
* @author Drew Paridaens
* @version 01
* @date 06/10/2019
*
*
* @bug No known bugs.
*/
class Anticipation :
	public Need
{
public:
	Anticipation(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier);
	~Anticipation();
	bool Seek(AIEmotion* ai, AffordanceAgent* aa) override;
	void FinishSeek(AIEmotion* ai, AffordanceAgent* aa) override;
};

