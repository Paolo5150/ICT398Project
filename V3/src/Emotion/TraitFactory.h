#pragma once

#include "Trait.h"

#include <memory>

class TraitFactory
{
public:
	TraitFactory();
	~TraitFactory();
	static int GetTraitType(std::string traitName);
	static std::unique_ptr<Trait> GetTrait(Trait::TraitType traitName);
};

