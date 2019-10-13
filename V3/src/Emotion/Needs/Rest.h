#pragma once
#include "../Need.h"

class Rest :
	public Need
{
public:
	Rest(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier);
	~Rest();
	bool Seek(AIEmotion* ai, AffordanceAgent* aa) override;
	void FinishSeek(AIEmotion* ai, AffordanceAgent* aa) override;
};

