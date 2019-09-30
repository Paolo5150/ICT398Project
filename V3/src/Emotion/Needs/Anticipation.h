#pragma once
#include "..\Need.h"

class Anticipation :
	public Need
{
public:
	Anticipation(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier);
	~Anticipation();
	bool Seek() override;
};

