#include "pch.h"
#include "Thirst.h"
#include "../../Core/Logger.h"
#include "../../Components/AIEmotion.h"

Thirst::Thirst(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier) : Need(NeedType::Thirst, "Thirst", startValue, 10, 50, positiveGainMultiplier, negativeGainMultiplier, priority)
{
}


Thirst::~Thirst()
{
}

bool Thirst::Seek(AIEmotion* ai, AffordanceAgent* aa)
{
	Logger::LogInfo("Agent Seeking Thirst Satiation");
	return true;
}

void Thirst::FinishSeek(AIEmotion* ai, AffordanceAgent * aa)
{
}
