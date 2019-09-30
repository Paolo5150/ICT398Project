#include "pch.h"
#include "AIEmotionManager.h"


AIEmotionManager::AIEmotionManager()
{
}


AIEmotionManager::~AIEmotionManager()
{
	Clear();
}

AIEmotionManager& AIEmotionManager::Instance()
{
	static AIEmotionManager instance;
	return instance;
}

bool AIEmotionManager::RegisterEmotion(AIEmotion * aiEmotion)
{
	std::list<AIEmotion*>::iterator it = agents.begin();
	while (it != agents.end())
	{
		if ((*it) == aiEmotion)
			return false;
		it++;
	}
	agents.push_back(aiEmotion);
	Logger::LogInfo("AI Emotion Registered on", aiEmotion->GetName());
	return true;
}

bool AIEmotionManager::DeregisterEmotion(AIEmotion * aiEmotion)
{
	std::list<AIEmotion*>::iterator it = agents.begin();
	while (it != agents.end())
	{
		if ((*it) == aiEmotion)
		{
			agents.erase(it);
			return true;
		}
		it++;
	}
	return false;
}

void AIEmotionManager::Clear()
{
	agents.clear();
}

void AIEmotionManager::GenerateStimuli(Need::NeedType needType, Stimuli::StimuliType stimuliType, float magnitude, bool instant, float duration, const glm::vec3& pos, float distance, float tickSize)
{
	Stimuli stimuli = Stimuli(needType, stimuliType, magnitude, instant, duration, tickSize);

	std::list<AIEmotion*>::iterator it = agents.begin();
	while (it != agents.end())
	{
		if ((*it)->HasNeedType(needType))
		{
			if (glm::length(((*it)->GetParent()->transform.GetGlobalPosition() - pos)) <= distance)
				(*it)->AddStimuli(stimuli);
		}
		it++;
	}
}

void AIEmotionManager::GenerateStimuli(Need::NeedType needType, Stimuli::StimuliType stimuliType, float magnitude, bool instant, float duration, AIEmotion* target, float tickSize)
{
	Stimuli stimuli = Stimuli(needType, stimuliType, magnitude, instant, duration, tickSize);

	std::list<AIEmotion*>::iterator it = agents.begin();
	while (it != agents.end())
	{
		if ((*it)->HasNeedType(needType))
		{
			if ((*it) == target)
				(*it)->AddStimuli(stimuli);
		}
		it++;
	}
}
