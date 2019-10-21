#pragma once
#include "..\Need.h"

class LightNeed :
	public Need
{
public:
	LightNeed(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier);
	~LightNeed();
	bool Seek(AIEmotion* ai, AffordanceAgent* aa) override;
	void FinishSeek(AIEmotion* ai, AffordanceAgent* aa) override;
};

