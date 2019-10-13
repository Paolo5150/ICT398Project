#include "pch.h"
#include "Stimuli.h"


Stimuli::Stimuli(Need::NeedType needType, Stimuli::StimuliType stimuliType, float magnitude, bool instant, float duration, float tickSize) : needType(needType),
					type(stimuliType), magnitude(magnitude), instant(instant), duration(duration), tickSize(tickSize)
{
}

Stimuli::Stimuli(const Stimuli & stimuli)
{
	(*this) = stimuli;
}

Stimuli::~Stimuli()
{
}

Stimuli::StimuliType Stimuli::GetType()
{
	return type;
}

Need::NeedType Stimuli::GetNeedType()
{
	return needType;
}

float Stimuli::GetMagnitude()
{
	return magnitude;
}

void Stimuli::SetMagnitude(float newMagnitude)
{
	magnitude = newMagnitude;
}

bool Stimuli::GetInstant()
{
	return instant;
}

float Stimuli::GetDuration()
{
	return duration;
}

void Stimuli::SetDuration(float newDuration)
{
	duration = newDuration;
}

float Stimuli::GetTickSize()
{
	return tickSize;
}
