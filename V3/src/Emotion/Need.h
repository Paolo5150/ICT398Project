#pragma once

#include <string>

class AffordanceAgent;
class AIEmotion;

/**
* @class Need
* @brief Abstract parent class for all needs
*
*
* Contains all the relevant data relevant for the processing a need
*
* @author Drew Paridaens
* @version 01
* @date 22/09/2019
*
*
* @bug No known bugs.
*/
class Need
{
public:
	enum NeedType
	{
		Anger,
		Anticipation,
		Joy,
		Trust,
		Thirst,
		Rest,
		Social,
		Light
	};
/**
* @brief		Creates a parameterized Need
*
* @param		type					The type of need for the instantiated object
* @param		name					The name of the need for display purposes
* @param		value					The current value of the need
* @param		lowSeekThreshold		The bottom of the threshold that will prompt a seek call
* @param		highSeekThreshold		The top of the threshold that will prompt a seek call
* @param		positiveGainMultiplier	The rate at which positive incoming modifier values will be improved by
* @param		negativeGainMultiplier	The rate at which negative incoming modifier values will be reduced by
* @param		priority				The priority that determines the order that needs will be satisfied
*/
	Need(NeedType type, std::string name, float value, float lowSeekThreshold, float highSeekThreshold, float positiveGainMultiplier, float negativeGainMultiplier, int priority);
/**
* @brief		Creates a parameterized Need
*
* @param		type					The type of need for the instantiated object
* @param		name					The name of the need for display purposes
* @param		lowSeekThreshold		The bottom of the threshold that will prompt a seek call
* @param		highSeekThreshold		The top of the threshold that will prompt a seek call
*/
	Need(NeedType type, std::string name, float lowSeekThreshold, float highSeekThreshold);
/**
* @brief		Destroys the Need
*
*/
	~Need();
/**
* @brief		Abstract method that must be overriden that is called when the need is being seeked to be satiated
*
* @param		ai		A reference to the AIEmotion component that is attached to the object with this need
* @param		aa		A reference to the AffordanceAgent component that is attached to the object with this need
*
* @return		True if the need was able to successfully sought
*/
	virtual bool Seek(AIEmotion* ai, AffordanceAgent* aa) = 0;
/**
* @brief		Abstract method that must be overriden that is called when the need is finished being satiated
*
* @param		ai		A reference to the AIEmotion component that is attached to the object with this need
* @param		aa		A reference to the AffordanceAgent component that is attached to the object with this need
*
*/
	virtual void FinishSeek(AIEmotion* ai, AffordanceAgent* aa) = 0;
/**
* @brief		Returns the type of need for this object
*
* @return		THe NeedType of this need
*/
	NeedType GetNeedType();
/**
* @brief		Returns the name for this need
*
* @return		The name for this need
*/
	std::string GetName();
/**
* @brief		Returns the value for this need
*
* @return		The value for this need
*/
	float GetValue();
/**
* @brief		Sets the value for this need
*
* @param		newValue		The new value for this nees
*
*/
	void SetValue(float newValue);
/**
* @brief		Returns the low seek threshold for this need
*
* @return		The low seek threshold for this need
*/
	float GetLowSeekThreshold();
/**
* @brief		Returns the high seek threshold for this need
*
* @return		The high seek threshold for this need
*/
	float GetHighSeekThreshold();
/**
* @brief		Returns the positive gain multiplier for this need
*
* @return		The positive gain multiplier for this need
*/
	float GetPositiveGainMultiplier();
/**
* @brief		Returns the negative gain multiplier for this need
*
* @return		The negative gain multiplier for this need
*/
	float GetNegativeGainMultiplier();
/**
* @brief		Returns the priority for this need
*
* @return		The priority for this need
*/
	int GetPriority();

private:
	NeedType type;
	std::string name;
	float value;
	float lowSeekThreshold;
	float highSeekThreshold;
	float positiveGainMultiplier;
	float negativeGainMultiplier;
	int priority;

};

