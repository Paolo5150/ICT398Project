#pragma once
#include <string>
#include "Affordance.h"
#include "..\Emotion\AIEmotionManager.h"
#include "..\Core\Timer.h"

/**
* @class RestAffordance
* @brief Defines an affordance of type REST
*
*
* @author Paolo Ferri
* @version 01
* @date 20/10/2019
*
*
* @bug No known bugs.
*/
class SitAffordance : public Affordance
{
public:
	SitAffordance() 
	{
		score = 50;
		affordanceType = AffordanceTypes::REST;
		affordanceName = "SitAffordance";
		Callback = [](AIEmotion* ai) { Logger::LogInfo("Someone sit on me"); };
		UpdateCallback = [](AIEmotion* ai) { AIEmotionManager::Instance().GenerateStimuli(Need::NeedType::Rest, Stimuli::StimuliType::Default, 2.0f * Timer::GetDeltaS(), true, 0, ai); };
	}
	virtual ~SitAffordance() {};


};

class LaydownAffordance : public Affordance
{
public:
	LaydownAffordance() 
	{
		score = 50;
		affordanceType = AffordanceTypes::REST;
		affordanceName = "LaydownAffordance";
		Callback = [](AIEmotion* ai) { Logger::LogInfo("Someone laid down on me"); };
		UpdateCallback = [](AIEmotion* ai) { AIEmotionManager::Instance().GenerateStimuli(Need::NeedType::Rest, Stimuli::StimuliType::Default, 2.4f * Timer::GetDeltaS(), true, 0, ai); };
	}
	virtual ~LaydownAffordance() {};


};