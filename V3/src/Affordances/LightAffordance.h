#pragma once
#include <string>
#include "Affordance.h"
#include "..\Emotion\AIEmotionManager.h"
#include "..\Core\Timer.h"

class LightAffordance : public Affordance
{
public:
	LightAffordance()
	{
		score = 50;
		affordanceType = AffordanceTypes::LIGHT;
		affordanceName = "LightAffordance";
		Callback = [](AIEmotion* ai) { };
		UpdateCallback = [](AIEmotion* ai) { AIEmotionManager::Instance().GenerateStimuli(Need::NeedType::Light, Stimuli::StimuliType::Default, 1.0, true, 0.1, glm::vec3(), 500.0); };
	}
	virtual ~LightAffordance() {};


}; 
