#pragma once
#include <string>
#include "Affordance.h"
#include "..\Emotion\AIEmotionManager.h"
#include "..\Core\Timer.h"

class SocialAffordance : public Affordance
{
public:
	SocialAffordance()
	{
		score = 50;
		affordanceType = AffordanceTypes::SOCIAL;
		affordanceName = "SocialAffordance";
		Callback = [](AIEmotion* ai) { Logger::LogInfo("Someone being social"); };
		UpdateCallback = [](AIEmotion* ai) { AIEmotionManager::Instance().GenerateStimuli(Need::NeedType::Social, Stimuli::StimuliType::Compliment, 5.0f * Timer::GetDeltaS(), true, 0, ai); };
	}
	virtual ~SocialAffordance() {};


};