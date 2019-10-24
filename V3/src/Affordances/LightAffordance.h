#pragma once
#include <string>
#include "Affordance.h"
#include "..\Emotion\AIEmotionManager.h"
#include "..\Core\Timer.h"

/**
* @class LightAffordance
* @brief Defines an affordance of type LIGHT
*
*
* @author Paolo Ferri
* @version 01
* @date 20/10/2019
*
*
* @bug No known bugs.
*/
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
