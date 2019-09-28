#include "pch.h"
#include "Aggressive.h"


Aggressive::Aggressive()
{
	stimuliTypes.push_back(Stimuli::StimuliType::Threat);
}

Aggressive::~Aggressive()
{
}

Stimuli & Aggressive::ModifyStimuli(Stimuli & stimuli)
{
	if (stimuli.GetNeedType() == Need::NeedType::Rage)
	{
		float mag = stimuli.GetMagnitude();
		stimuli.SetMagnitude(mag + 20);
	}
	return stimuli;
}
