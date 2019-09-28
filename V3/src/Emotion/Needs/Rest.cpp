#include "pch.h"
#include "Rest.h"
#include "..\..\Core\Logger.h"


Rest::Rest(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier) : Need(NeedType::Rest, "Rest", startValue, 20, positiveGainMultiplier, negativeGainMultiplier, priority)
{
}


Rest::~Rest()
{
}

bool Rest::Seek()
{
	Logger::LogInfo("Agent Seeking Rest Satiation");
	return true;
}
