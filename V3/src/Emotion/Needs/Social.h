#pragma once
#include "..\Need.h"

/**
* @class Social
* @brief Child class of Need for tracking AI social needs
*
* @author Drew Paridaens
* @version 01
* @date 12/10/2019
*
*
* @bug No known bugs.
*/
class Social :
	public Need
{
public:
	Social(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier);
	~Social();
	bool Seek(AIEmotion* ai, AffordanceAgent* aa) override;
	void FinishSeek(AIEmotion* ai, AffordanceAgent* aa) override;
};

