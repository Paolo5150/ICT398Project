#pragma once
#include "..\Need.h"

class Trust :
	public Need
{
public:
	Trust(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier);
	~Trust();
	bool Seek() override;
};

