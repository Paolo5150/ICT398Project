#pragma once
#include "..\Need.h"

/**
* @class Trust
* @brief Child class of Need for tracking AI trust
*
* @author Drew Paridaens
* @version 01
* @date 06/10/2019
*
*
* @bug No known bugs.
*/
class Trust :
	public Need
{
public:
	Trust(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier);
	~Trust();
	bool Seek(AIEmotion* ai, AffordanceAgent* aa) override;
	void FinishSeek(AIEmotion* ai, AffordanceAgent* aa) override;
};

