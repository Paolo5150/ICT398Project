#pragma once

#include "Stimuli.h"

#include <string>
#include <list>

/**
* @class Trait
* @brief Class for holding traits that modify incoming stimuli for the AIEmotion component
*
* @author Drew Paridaens
* @version 01
* @date 22/09/2019
*
*
* @bug No known bugs.
*/
class Trait
{
public:
	enum TraitType
	{
		Aggressive
	};
/**
* @brief		Creates a default Trait
*
*/
	Trait();
/**
* @brief		Destroys the Trait
*
*/
	~Trait();
/**
* @brief		Pure abstract method to modify incoming stimuli
*
* @param		stimuli		A reference to the stimuli to modify
*
* @return		Returns a reference to the modified stimuli
*/
	virtual Stimuli& ModifyStimuli(Stimuli& stimuli) = 0;
/**
* @brief		Returns whether the Trait effects the given Stimuli type
*
* @param		stimuliType		The stimuli type to check
*
* @return		True if the trait effects the given stimuli type
*/
	bool HasStimuliType(Stimuli::StimuliType stimuliType);

private:
	std::string name;

protected:
	std::list<Stimuli::StimuliType> stimuliTypes = std::list<Stimuli::StimuliType>();

};

