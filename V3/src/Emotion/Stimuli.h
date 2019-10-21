#pragma once

#include "Need.h"

/**
* @class Stimuli
* @brief Class for holding stimuli to modify AIEmotion Need values
*
* @author Drew Paridaens
* @version 01
* @date 22/09/2019
*
*
* @bug No known bugs.
*/
class Stimuli
{
public:
	enum StimuliType
	{
		Default,
		Compliment,
		Threat
	};
/**
* @brief		Creates a parameterized Stimuli
*
* @param		needType				The type of need for the instantiated stimuli
* @param		stimuliType				The type of stimuli for the instantiated stimuli
* @param		magnitude				The magnitude value of the instantiated stimuli
* @param		instant					Whether the stimuli should be consumed instantly or use the duration and tick size
* @param		duration				The duration for the stimuli in seconds
* @param		tickSize				The size of a single tick down of the stimuli in seconds
*/
	Stimuli(Need::NeedType needType, StimuliType stimuliType, float magnitude, bool instant, float duration, float tickSize = 1.0f);
/**
* @brief		Copy constructor for Stimuli
*
* @param		stimuli				A reference to another stimuli object
*/
	Stimuli(const Stimuli& stimuli);
/**
* @brief		Destroys the Stimuli
*
*/
	~Stimuli();
/**
* @brief		Returns the type of stimuli
*
* @return		The StimuliType for this object
*/
	StimuliType GetType();
/**
* @brief		Returns the type of need for this object
*
* @return		THe NeedType of this need
*/
	Need::NeedType GetNeedType();
/**
* @brief		Returns the magnitude of the stimuli
*
* @return		The magnitude of the stimuli
*/
	float GetMagnitude();
/**
* @brief		Sets the magnitude of the stimuli
*
* @param		newMagnitude		The new magnitude for the stimuli
*/
	void SetMagnitude(float newMagnitude);
/**
* @brief		Returns whether the stimuli is instant
*
* @return		Whether the stimuli is instant
*/
	bool GetInstant();
/**
* @brief		Returns the duration of the stimuli
*
* @return		Whether the stimuli is instant
*/
	float GetDuration();
/**
* @brief		Sets the duration of the stimuli
*
* @param		newDuration		The new duration for the stimuli
*/
	void SetDuration(float newDuration);
/**
* @brief		Returns the tick size of the stimuli
*
* @return		The tick size of the stimuli
*/
	float GetTickSize();

private:
	Need::NeedType needType;
	StimuliType type;
	float magnitude;
	bool instant;
	float duration;
	float tickSize;

};

