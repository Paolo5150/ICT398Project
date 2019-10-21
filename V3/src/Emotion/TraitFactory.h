#pragma once

#include "Trait.h"

#include <memory>

/**
* @class TraitFactory
* @brief Factory class for returning pointers to new Traits
*
* @author Drew Paridaens
* @version 01
* @date 22/09/2019
*
*
* @bug No known bugs.
*/
class TraitFactory
{
public:
/**
* @brief		Creates a default TraitFactory
*
*/
	TraitFactory();
/**
* @brief		Destroys the TraitFactory
*
*/
	~TraitFactory();
/**
* @brief		Static method returns an int corresponding to a TraitType, or -1 ifthe need type is not found
*
* @param		traitName		The string name of the trait
*
* @return		Returns an int corresponding to a TraitType, or -1 if the trait type is not found
*/
	static int GetTraitType(std::string traitName);
/**
* @brief		Static method returns a unique pointer to a new Trait object
*
* @param		traitName				The type of trait to create
*
* @return		Returns a unique pointer to a new Trait object
*/
	static std::unique_ptr<Trait> GetTrait(Trait::TraitType traitName);
};

