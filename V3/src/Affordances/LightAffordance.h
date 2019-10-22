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
		maxUsers = 100;
		affordanceName = "LightAffordance";
		Callback = [](AIEmotion* ai) { };
		UpdateCallback = [](AIEmotion* ai) {  };
	}
	virtual ~LightAffordance() {};


}; 
