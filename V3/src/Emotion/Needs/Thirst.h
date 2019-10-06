#pragma once

#include "../Need.h"

class Thirst : public Need
{
public:
	Thirst(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier);
	~Thirst();
	bool Seek(AIEmotion* ai, AffordanceAgent* aa) override;
	void FinishSeek(AIEmotion* ai, AffordanceAgent* aa) override;
};

