#include "pch.h"
#include "Anger.h"
#include "..\..\Core\Logger.h"
#include "..\..\Components\AIEmotion.h"

Anger::Anger(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier) : Need(NeedType::Anger, "Anger", startValue, 10, 100, positiveGainMultiplier, negativeGainMultiplier, priority)
{
}


Anger::~Anger()
{
}

bool Anger::Seek(AIEmotion* ai, AffordanceAgent* aa)
{
	Logger::LogInfo("Agent Seeking Anger Satiation");
	return true;
}

void Anger::FinishSeek(AIEmotion* ai, AffordanceAgent * aa)
{
}
