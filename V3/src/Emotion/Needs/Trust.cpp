#include "pch.h"
#include "Trust.h"
#include "..\..\Core\Logger.h"

Trust::Trust(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier) : Need(NeedType::Trust, "Trust", startValue, 0, 100, positiveGainMultiplier, negativeGainMultiplier, priority)
{
}

Trust::~Trust()
{
}

bool Trust::Seek()
{
	Logger::LogInfo("Agent Seeking Trust Satiation");
	return true;
}