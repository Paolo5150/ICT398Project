#pragma once
#include "../Trait.h"

class Aggressive :
	public Trait
{
public:
	Aggressive();
	~Aggressive();
	Stimuli& ModifyStimuli(Stimuli& stimuli) override;
};

