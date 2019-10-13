#include "pch.h"
#include "Trust.h"
#include "..\..\Core\Logger.h"
#include "../../Components/AIEmotion.h"

Trust::Trust(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier) : Need(NeedType::Trust, "Trust", startValue, 0, 100, positiveGainMultiplier, negativeGainMultiplier, priority)
{
}

Trust::~Trust()
{
}

bool Trust::Seek(AIEmotion* ai, AffordanceAgent* aa)
{
	Logger::LogInfo("Agent Seeking Trust Satiation");
	return true;
}

void Trust::FinishSeek(AIEmotion* ai, AffordanceAgent * aa)
{
}
