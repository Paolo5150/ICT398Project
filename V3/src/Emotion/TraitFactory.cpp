#include "pch.h"
#include "TraitFactory.h"
#include "Traits/Aggressive.h"

#include <boost/algorithm/string.hpp>

TraitFactory::TraitFactory()
{
}


TraitFactory::~TraitFactory()
{
}

int TraitFactory::GetTraitType(std::string traitName)
{
	if (strcmp("aggressive", traitName.c_str()) == 0)
	{
		return Trait::TraitType::Aggressive;
	}
	else
	{
		return -1;
	}
}

std::unique_ptr<Trait> TraitFactory::GetTrait(Trait::TraitType traitType)
{
	std::unique_ptr<Trait> trait(nullptr);
	
	switch (traitType)
	{
	case Trait::TraitType::Aggressive:
		trait = std::unique_ptr<Aggressive>(new Aggressive());
		break;
	}

	return trait;
}
