#pragma once

#include "..\Components\AIEmotion.h"
#include "Stimuli.h"
#include "Need.h"

#include <list>

class AIEmotionManager
{
public:
	AIEmotionManager();
	~AIEmotionManager();
	static AIEmotionManager& Instance();
	bool RegisterEmotion(AIEmotion* aiEmotion);
	bool DeregisterEmotion(AIEmotion* aiEmotion);
	void Clear();
	void GenerateStimuli(Need::NeedType needType, Stimuli::StimuliType stimuliType, float magnitude, bool instant, float duration, const glm::vec3& pos, float distance, float tickSize = 1.0f);
	void GenerateStimuli(Need::NeedType needType, Stimuli::StimuliType stimuliType, float magnitude, bool instant, float duration, AIEmotion* target, float tickSize = 1.0f);

private:
	std::list<AIEmotion*> agents = std::list<AIEmotion*>();

};

