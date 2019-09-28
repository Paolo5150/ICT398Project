#pragma once
#include "..\Need.h"

class Rage :
	public Need
{
public:
	Rage(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier);
	~Rage();
	bool Seek() override;
};

