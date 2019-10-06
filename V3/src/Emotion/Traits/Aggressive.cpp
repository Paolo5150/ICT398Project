#include "pch.h"
#include "Aggressive.h"
#include "..\..\Core\Timer.h"


Aggressive::Aggressive()
{
	stimuliTypes.push_back(Stimuli::StimuliType::Threat);
}

Aggressive::~Aggressive()
{
}

Stimuli & Aggressive::ModifyStimuli(Stimuli & stimuli)
{
	if (stimuli.GetNeedType() == Need::NeedType::Anger)
	{
		float mag = stimuli.GetMagnitude();
		stimuli.SetMagnitude(mag + 20);
	}
	return stimuli;
}
