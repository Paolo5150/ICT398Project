#pragma once

#include "Stimuli.h"

#include <string>
#include <list>

class Trait
{
public:
	enum TraitType
	{
		Aggressive
	};
	Trait();
	~Trait();
	virtual Stimuli& ModifyStimuli(Stimuli& stimuli) = 0;
	bool HasStimuliType(Stimuli::StimuliType stimuliType);

private:
	std::string name;

protected:
	std::list<Stimuli::StimuliType> stimuliTypes = std::list<Stimuli::StimuliType>();

};

