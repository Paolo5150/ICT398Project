#pragma once
#include "..\Need.h"

class Joy :
	public Need
{
public:
	Joy(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier);
	~Joy();
	bool Seek() override;
};

