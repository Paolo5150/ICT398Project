#pragma once

#include "..\Components\AIEmotion.h"
#include "Stimuli.h"
#include "Need.h"

#include <list>

/**
* @class AIEmotionManager
* @brief Manager for AIEmotion components in the scene
*
*
* Manages the active AIEmotion components
*
* @author Drew Paridaens
* @version 01
* @date 22/09/2019
*
*
* @bug No known bugs.
*/
class AIEmotionManager
{
public:
/**
* @brief		Creates a default AIEmotionManager
*
*/
	AIEmotionManager();
/**
* @brief		Destroys the AIComponentManager
*
*/
	~AIEmotionManager();
/**
* @brief		Static method that returns the singleton instance of the AIEmotionManager
*
* @return		The singleton instance of the AIEmotionManager
*/
	static AIEmotionManager& Instance();
/**
* @brief		Registers the AIEmotion component and returns whether the AIEmotion component was succesfully registered
*
* @param		aiEmotion		The AIEmotion component to register
*
* @return		Whether the AIEmotion component was succesfully registered
*/
	bool RegisterEmotion(AIEmotion* aiEmotion);
/**
* @brief		Deregisters the AIEmotion component and returns whether the AIEmotion component was succesfully deregistered
*
* @param		aiEmotion		The AIEmotion component to deregister
*
* @return		Whether the AIEmotion component was succesfully deregistered
*/
	bool DeregisterEmotion(AIEmotion* aiEmotion);
/**
* @brief		Clears the AIEmotion components registered to the manager
*
*/
	void Clear();
/**
* @brief		Sends a stimuli to all AIEmotion components within a range of the given position
*
* @param		needType				The type of need for the instantiated stimuli
* @param		stimuliType				The type of stimuli for the instantiated stimuli
* @param		magnitude				The magnitude value of the instantiated stimuli
* @param		instant					Whether the stimuli should be consumed instantly or use the duration and tick size
* @param		duration				The duration for the stimuli in seconds
* @param		pos						The world position of the generated stimuli
* @param		distance				The distance from the world position that AIEmotion components will receive the stimuli
* @param		tickSize				The size of a single tick down of the stimuli in seconds
*/
	void GenerateStimuli(Need::NeedType needType, Stimuli::StimuliType stimuliType, float magnitude, bool instant, float duration, const glm::vec3& pos, float distance, float tickSize = 1.0f);
/**
* @brief		Sends a stimuli to the AIEmotion component target
*
* @param		needType				The type of need for the instantiated stimuli
* @param		stimuliType				The type of stimuli for the instantiated stimuli
* @param		magnitude				The magnitude value of the instantiated stimuli
* @param		instant					Whether the stimuli should be consumed instantly or use the duration and tick size
* @param		duration				The duration for the stimuli in seconds
* @param		target					The AIEmotion component target for the stimuli
* @param		tickSize				The size of a single tick down of the stimuli in seconds
*/
	void GenerateStimuli(Need::NeedType needType, Stimuli::StimuliType stimuliType, float magnitude, bool instant, float duration, AIEmotion* target, float tickSize = 1.0f);

private:
	std::list<AIEmotion*> agents = std::list<AIEmotion*>();

};

