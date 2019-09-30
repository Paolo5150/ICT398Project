#include "pch.h"
#include "Anger.h"
#include "..\..\Core\Logger.h"

Anger::Anger(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier) : Need(NeedType::Anger, "Anger", startValue, 10, 100, positiveGainMultiplier, negativeGainMultiplier, priority)
{
}


Anger::~Anger()
{
}

bool Anger::Seek()
{
	Logger::LogInfo("Agent Seeking Anger Satiation");
	return true;
}
