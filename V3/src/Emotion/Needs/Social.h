#pragma once
#include "..\Need.h"

class Social :
	public Need
{
public:
	Social(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier);
	~Social();
	bool Seek(AIEmotion* ai, AffordanceAgent* aa) override;
	void FinishSeek(AIEmotion* ai, AffordanceAgent* aa) override;
};

