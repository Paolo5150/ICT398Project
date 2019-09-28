#include "pch.h"
#include "Trait.h"


Trait::Trait()
{
}


Trait::~Trait()
{
}

bool Trait::HasStimuliType(Stimuli::StimuliType stimuliType)
{
	std::list<Stimuli::StimuliType>::iterator it = stimuliTypes.begin();
	while (it != stimuliTypes.end())
	{
		if (*it == stimuliType)
			return true;
		it++;
	}
	return false;
}
