#include "pch.h"
#include "Rage.h"
#include "..\..\Core\Logger.h"


Rage::Rage(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier) : Need(NeedType::Rage, "Rage", startValue, 0, positiveGainMultiplier, negativeGainMultiplier, priority)
{
}


Rage::~Rage()
{
}

bool Rage::Seek()
{
	Logger::LogInfo("Agent Seeking Rage Satiation");
	return true;
}
