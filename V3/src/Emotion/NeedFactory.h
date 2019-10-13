#pragma once

#include "Need.h"

#include <memory>

class NeedFactory
{
public:
	NeedFactory();
	~NeedFactory();
	static int GetNeedType(std::string needName);
	static std::unique_ptr<Need> GetNeed(Need::NeedType type, float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier);
};

