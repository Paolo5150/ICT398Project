#include "pch.h"
#include "Joy.h"
#include "..\..\Core\Logger.h"
#include "..\..\Components\AIEmotion.h"

Joy::Joy(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier) : Need(NeedType::Joy, "Joy", startValue, 0, 100, positiveGainMultiplier, negativeGainMultiplier, priority)
{
}


Joy::~Joy()
{
}

bool Joy::Seek(AIEmotion* ai, AffordanceAgent* aa)
{
	Logger::LogInfo("Agent Seeking Joy Satiation");
	return true;
}

void Joy::FinishSeek(AIEmotion* ai, AffordanceAgent * aa)
{
}
