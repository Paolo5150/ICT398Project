#include "pch.h"
#include "Need.h"


Need::Need(NeedType type, std::string name, float value, float minSeekThreshold, float positiveGainMultiplier, float negativeGainMultiplier, int priority) : type(type),
			name(name),	value(value), minSeekThreshold(minSeekThreshold), positiveGainMultiplier(positiveGainMultiplier), negativeGainMultiplier(negativeGainMultiplier), priority(priority)
{
}

Need::Need(NeedType type, std::string name, float minSeekThreshold) : type(type), name(name), minSeekThreshold(minSeekThreshold)
{
}


Need::~Need()
{
}

Need::NeedType Need::GetNeedType()
{
	return type;
}

std::string Need::GetName()
{
	return name;
}

float Need::GetValue()
{
	return value;
}

void Need::SetValue(float newValue)
{
	if (newValue < 0)
		value = 0;
	else if (newValue > 100)
		value = 100;
	else
		value = newValue;
}

float Need::GetMinSeekThreshold()
{
	return minSeekThreshold;
}

float Need::GetPositiveGainMultiplier()
{
	return positiveGainMultiplier;
}

float Need::GetNegativeGainMultiplier()
{
	return negativeGainMultiplier;
}

int Need::GetPriority()
{
	return priority;
}
