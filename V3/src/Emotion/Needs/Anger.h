#pragma once
#include "..\Need.h"
class Anger :
	public Need
{
public:
	Anger(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier);
	~Anger();
	bool Seek() override;
};

