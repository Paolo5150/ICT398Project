#include "pch.h"
#include "Joy.h"
#include "..\..\Core\Logger.h"


Joy::Joy(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier) : Need(NeedType::Joy, "Joy", startValue, 0, 100, positiveGainMultiplier, negativeGainMultiplier, priority)
{
}


Joy::~Joy()
{
}

bool Joy::Seek()
{
	Logger::LogInfo("Agent Seeking Joy Satiation");
	return true;
}