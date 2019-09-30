#include "pch.h"
#include "Thirst.h"
#include "../../Core/Logger.h"

Thirst::Thirst(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier) : Need(NeedType::Thirst, "Thirst", startValue, 10, 100, positiveGainMultiplier, negativeGainMultiplier, priority)
{
}


Thirst::~Thirst()
{
}

bool Thirst::Seek()
{
	Logger::LogInfo("Agent Seeking Thirst Satiation");
	return true;
}
