#include "pch.h"
#include "AIEmotion.h"
#include "../Emotion/AIEmotionManager.h"
#include "../Core/Timer.h"

AIEmotion::AIEmotion() : Component("Emotion")
{
	this->personalityName = "default";
	timer = 0;
}

AIEmotion::AIEmotion(std::string personalityName) : Component("Emotion")
{
	this->personalityName = personalityName;
	timer = 0;
}


AIEmotion::~AIEmotion()
{
	AIEmotionManager::Instance().DeregisterEmotion(this);
}

void AIEmotion::AddStimuli(const Stimuli & original)
{
	effectedStimuli.push_back(std::make_unique<Stimuli>(original));
	Stimuli* copy = effectedStimuli.back().get();

	std::list<std::unique_ptr<Trait>>::iterator it = traits.begin();
	while (it != traits.end())
	{
		if (it->get()->HasStimuliType(copy->GetType()))
			it->get()->ModifyStimuli(*copy);
		it++;
	}
}

bool AIEmotion::LoadPersonality()
{
	needs = std::map<Need::NeedType, std::unique_ptr<Need>>();
	traits = std::list<std::unique_ptr<Trait>>();

	std::string absoluteFilePath = "Assets\\Personalities\\" + personalityName + ".personality";

	return FileUtils::ReadPersonalityFile(absoluteFilePath, needs, traits);
}

bool AIEmotion::HasNeedType(Need::NeedType needType)
{
	std::map<Need::NeedType, std::unique_ptr<Need>>::iterator it = needs.find(needType);
	if (it != needs.end())
		return true;
	else
		return false;
}

float AIEmotion::GetNeedValue(Need::NeedType needType)
{
	return needs[needType]->GetValue();
}

void AIEmotion::OnAttach(GameObject * go)
{
	LoadPersonality();
	AIEmotionManager::Instance().RegisterEmotion(this);
}

void AIEmotion::EngineUpdate()
{
	timer += Timer::GetDeltaS();
	if (timer < 2.5)
	{
		AIEmotionManager::Instance().GenerateStimuli(Need::NeedType::Rest, Stimuli::StimuliType::Default, -30 * Timer::GetDeltaS(), true, 0, this);
		AIEmotionManager::Instance().GenerateStimuli(Need::NeedType::Thirst, Stimuli::StimuliType::Default, -20 * Timer::GetDeltaS(), true, 0, this);
	}
	if (timer > 2.5 && timer < 3.0f)
	{
		AIEmotionManager::Instance().GenerateStimuli(Need::NeedType::Thirst, Stimuli::StimuliType::Default, 30, true, 0, this);
	}

	UpdateStimuli();

	UpdateNeeds();
}

void AIEmotion::UpdateStimuli()
{
	std::list<std::unique_ptr<Stimuli>>::iterator it = effectedStimuli.begin();
	while (it != effectedStimuli.end())
	{
		Stimuli* stimuli = it->get();
		std::map<Need::NeedType, std::unique_ptr<Need>>::iterator it2 = needs.find(it->get()->GetNeedType());
		if (it2 != needs.end())
		{
			Need* need = it2->second.get();
			if (stimuli->GetInstant())
			{
				float multiplier;
				if (stimuli->GetMagnitude() > 0)
					multiplier = need->GetPositiveGainMultiplier();
				else
					multiplier = need->GetNegativeGainMultiplier();
				need->SetValue(need->GetValue() + stimuli->GetMagnitude() * multiplier);
				it = effectedStimuli.erase(it);
			}
			else
			{
				float duration = stimuli->GetDuration();
				float tickDuration = stimuli->GetTickSize();
				int numTicks = duration / tickDuration;
				duration -= Timer::GetDeltaS();
				if (numTicks != (int)(duration / tickDuration))
				{
					numTicks = duration / tickDuration;
					if (numTicks > 0)
					{
						float multiplier;
						if (stimuli->GetMagnitude() > 0)
							multiplier = need->GetPositiveGainMultiplier();
						else
							multiplier = need->GetNegativeGainMultiplier();
						need->SetValue(need->GetValue() + stimuli->GetMagnitude() * multiplier);
						it++;
					}
					else
					{
						it = effectedStimuli.erase(it);
					}
				}
				else
				{
					it++;
				}
			}
		}
		else
			it++;
	}
}

void AIEmotion::UpdateNeeds()
{
	std::map<Need::NeedType, std::unique_ptr<Need>>::iterator it = needs.begin();

	std::list<Need*> priorityOrderedNeeds = std::list<Need*>();

	//Order need satisfaction priority list
	while (it != needs.end())
	{
		Need* need = it->second.get();
		if (need->GetValue() < need->GetMinSeekThreshold())
		{
			if (priorityOrderedNeeds.empty())
			{
				priorityOrderedNeeds.emplace_front(need);
			}
			else
			{
				std::list<Need*>::iterator it2 = priorityOrderedNeeds.begin();
				while (it2 != priorityOrderedNeeds.end())
				{
					if (need->GetPriority() < (*it2)->GetPriority())
					{
						priorityOrderedNeeds.emplace(it2, need);
						it2 = priorityOrderedNeeds.end();
					}
					else
					{
						if ((*it2) == priorityOrderedNeeds.back())
						{
							priorityOrderedNeeds.emplace_back(need);
							it2 = priorityOrderedNeeds.end();
						}
						else
							it2++;
					}
				}
			}
		}
		else
		{
			//Need has been satisfied, free up pointer to seek other needs
			if (currentlySeekedNeed != nullptr && currentlySeekedNeed == need)
				currentlySeekedNeed = nullptr;
		}
		it++;
	}

	//Operate on need satisfaction priority list 
	if (!priorityOrderedNeeds.empty())
	{
		std::list<Need*>::iterator it = priorityOrderedNeeds.begin();

		while (it != priorityOrderedNeeds.end())
		{
			if ((*it) != currentlySeekedNeed)
			{
				if ((*it)->Seek())
				{
					currentlySeekedNeed = (*it);
					it = priorityOrderedNeeds.end();
				}
				else
					it++;
			}
			else
				it = priorityOrderedNeeds.end();
		}
	}
}
