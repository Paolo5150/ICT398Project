#pragma once

#include "Need.h"

#include <memory>

/**
* @class NeedFactory
* @brief Factory class for returning pointers to new needs
*
* @author Drew Paridaens
* @version 01
* @date 22/09/2019
*
*
* @bug No known bugs.
*/
class NeedFactory
{
public:
/**
* @brief		Creates a default NeedFactory
*
*/
	NeedFactory();
/**
* @brief		Destroys the NeedFactory
*
*/
	~NeedFactory();
/**
* @brief		Static method returns an int corresponding to a NeedType, or -1 ifthe need type is not found
*
* @param		needName		The string name of the need
*
* @return		Returns an int corresponding to a NeedType, or -1 if the need type is not found
*/
	static int GetNeedType(std::string needName);
/**
* @brief		Static method returns a unique pointer to a new Need object
*
* @param		type						The type of need to create
* @param		startValue					The starting value for the need
* @param		priority					The priority of the need
* @param		positiveGainMultiplier		The positive gain multiplier of the need
* @param		negativeGainMultiplier		The negative gain multiplier of the need
*
* @return		Returns a unique pointer to a new Need object
*/
	static std::unique_ptr<Need> GetNeed(Need::NeedType type, float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier);
};

