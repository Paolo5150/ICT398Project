#include "pch.h"
#include "Anticipation.h"
#include "..\..\Core\Logger.h"
#include "..\..\Components\AIEmotion.h"

Anticipation::Anticipation(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier) : Need(NeedType::Anticipation, "Anticipation", startValue, 0, 100, positiveGainMultiplier, negativeGainMultiplier, priority)
{
}

Anticipation::~Anticipation()
{
}

bool Anticipation::Seek(AIEmotion* ai, AffordanceAgent* aa)
{
	Logger::LogInfo("Agent Seeking Anticipation Satiation");
	return true;
}

void Anticipation::FinishSeek(AIEmotion* ai, AffordanceAgent * aa)
{
}
