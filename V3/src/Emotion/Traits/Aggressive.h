#pragma once
#include "../Trait.h"

/**
* @class Aggressive
* @brief Child class of Trait for modifying stimuli
*
* @author Drew Paridaens
* @version 01
* @date 06/10/2019
*
*
* @bug No known bugs.
*/
class Aggressive :
	public Trait
{
public:
	Aggressive();
	~Aggressive();
	Stimuli& ModifyStimuli(Stimuli& stimuli) override;
};

