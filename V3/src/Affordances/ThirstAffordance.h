#pragma once
#include <string>
#include "Affordance.h"
#include "..\Emotion\AIEmotionManager.h"
#include "..\Core\Timer.h"

class ThirstAffordance : public Affordance
{
public:
	ThirstAffordance()
	{
		score = 50;
		affordanceType = AffordanceTypes::THIRST;
		affordanceName = "ThirstAffordance";
		Callback = [](AIEmotion* ai) { Logger::LogInfo("Someone drinking"); };
		UpdateCallback = [](AIEmotion* ai) { AIEmotionManager::Instance().GenerateStimuli(Need::NeedType::Thirst, Stimuli::StimuliType::Default, 10.0f * Timer::GetDeltaS(), true, 0, ai); };
	}
	virtual ~ThirstAffordance() {};


};