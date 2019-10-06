#pragma once

#include "Need.h"

class Stimuli
{
public:
	enum StimuliType
	{
		Default,
		Compliment,
		Threat
	};
	Stimuli(Need::NeedType needType, StimuliType stimuliType, float magnitude, bool instant, float duration, float tickSize = 1.0f);
	Stimuli(const Stimuli& stimuli);
	~Stimuli();
	StimuliType GetType();
	Need::NeedType GetNeedType();
	float GetMagnitude();
	void SetMagnitude(float newMagnitude);
	bool GetInstant();
	float GetDuration();
	void SetDuration(float newDuration);
	float GetTickSize();

private:
	Need::NeedType needType;
	StimuliType type;
	float magnitude;
	bool instant;
	float duration;
	float tickSize;

};

