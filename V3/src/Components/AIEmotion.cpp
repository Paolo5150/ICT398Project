#include "pch.h"
#include "AIEmotion.h"
#include "../Emotion/AIEmotionManager.h"
#include "../Core/Timer.h"
#include "../GUI/GUIManager.h"
#include "../GUI/Elements/GUIText.h"
#include "AffordanceAgent.h"

AIEmotion::AIEmotion() : Component("Emotion")
{
	name = "Chadd";
	personalityName = "default";
}

AIEmotion::AIEmotion(std::string name, std::string personalityName) : Component("Emotion")
{
	this->name = name;
	this->personalityName = personalityName;
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

std::string AIEmotion::GetName()
{
	return name;
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

void AIEmotion::Start()
{
	aa = GetParent()->GetComponent<AffordanceAgent>("AffordanceAgent");
	if (aa == nullptr)
	{
		Logger::LogWarning("NO AFFORDANCE AGENT ATTACHED TO AGENT \"", GetParent()->GetName(), "\"");
	}
	isRenderingStats = 0;
}

void AIEmotion::EngineUpdate()
{
	if (HasNeedType(Need::NeedType::Thirst))
		AIEmotionManager::Instance().GenerateStimuli(Need::NeedType::Thirst, Stimuli::StimuliType::Default, -0.2f * Timer::GetDeltaS(), true, 0, this);
	if (HasNeedType(Need::NeedType::Rest))
		AIEmotionManager::Instance().GenerateStimuli(Need::NeedType::Rest, Stimuli::StimuliType::Default, -0.2f * Timer::GetDeltaS(), true, 0, this);
	if (HasNeedType(Need::NeedType::Social))
		AIEmotionManager::Instance().GenerateStimuli(Need::NeedType::Social, Stimuli::StimuliType::Default, -0.4f * Timer::GetDeltaS(), true, 0, this);
	if (HasNeedType(Need::NeedType::Anger))
		AIEmotionManager::Instance().GenerateStimuli(Need::NeedType::Anger, Stimuli::StimuliType::Default, -0.5f * Timer::GetDeltaS(), true, 0, this);

	UpdateStimuli();

	if (seeking)
	{
		SeekNeeds();
	}
	else
	{
		currentlySeekedNeed = nullptr;
	}
}

bool AIEmotion::GetSeeking()
{
	return seeking;
}

void AIEmotion::SetSeeking(bool newSeeking)
{
	seeking = newSeeking;
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
					float magnitude = stimuli->GetMagnitude() / numTicks;
					numTicks = duration / tickDuration;
					if (numTicks >= 0)
					{
						float multiplier;
						if (magnitude > 0)
							multiplier = need->GetPositiveGainMultiplier();
						else
							multiplier = need->GetNegativeGainMultiplier();
						need->SetValue(need->GetValue() + magnitude * multiplier);
						if (numTicks == 0)
							it = effectedStimuli.erase(it);
						else
						{
							stimuli->SetMagnitude(stimuli->GetMagnitude() - magnitude);
							stimuli->SetDuration(duration);
							it++;
						}
					}
					else
					{
						it = effectedStimuli.erase(it);
					}
				}
				else
				{
					stimuli->SetDuration(duration);
					it++;
				}
			}
		}
		else
			it++;
	}
}

void AIEmotion::SeekNeeds()
{
	std::map<Need::NeedType, std::unique_ptr<Need>>::iterator it = needs.begin();

	std::list<Need*> priorityOrderedNeeds = std::list<Need*>();

	//Order need satisfaction priority list
	while (it != needs.end())
	{
		Need* need = it->second.get();
		if (need->GetValue() < need->GetLowSeekThreshold() || (currentlySeekedNeed == need && need->GetValue() < need->GetHighSeekThreshold()))
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
			{
				//Logger::LogInfo("Finish seek FIRST", currentlySeekedNeed->GetName());

				currentlySeekedNeed->FinishSeek(this, aa);
				currentlySeekedNeed = nullptr;
			}
		}
		it++;
	}
	

	//Operate on need satisfaction priority list 
	if (!priorityOrderedNeeds.empty())
	{
		std::list<Need*>::iterator it = priorityOrderedNeeds.begin();

		while (it != priorityOrderedNeeds.end())
		{
			if ((*it)->Seek(this, aa))
			{
				//Logger::LogInfo("Found", (*it)->GetName());

				if (currentlySeekedNeed != nullptr && currentlySeekedNeed != (*it))
				{
				//	Logger::LogInfo("Finish seek MIDDLE", currentlySeekedNeed->GetName());
					currentlySeekedNeed->FinishSeek(this, aa);
					currentlySeekedNeed = nullptr;
				}

				currentlySeekedNeed = (*it);
				it = priorityOrderedNeeds.end();
			}	
	
			else
			{
				if (!aa->HasInUseObject())
				{
					if (currentlySeekedNeed == (*it))
					{
						//Logger::LogInfo("Finish seek OTHER", currentlySeekedNeed->GetName());

						currentlySeekedNeed->FinishSeek(this, aa);
						currentlySeekedNeed = nullptr;
					}
				}
				it++;
			}
		}
	}
}

void AIEmotion::EnableRenderStats()
{

		auto it = needs.begin();
	if (!isRenderingStats)
	{
		int index = 1;

		for (; it != needs.end(); it++)
		{
			std::stringstream ss;
			ss << it->second->GetName();
			ss << ": ";
			ss << GetNeedValue(it->first);

			GUIText* text = new GUIText(it->second->GetName() + GetParent()->GetName(), ss.str(), 5, 5 * index, glm::vec3(1, 0, 0), 1.5, 1);
			index++;
			GUIManager::Instance().GetCanvasByName("MainCanvas")->AddGUIObject(text);
		}		
		isRenderingStats = 1;
	}
	else
	{
		for (; it != needs.end(); it++)
		{
			std::stringstream ss;
			ss << it->second->GetName();
			ss << ": ";
			ss << GetNeedValue(it->first);

			GUIText* text = (GUIText*)GUIManager::Instance().GetCanvasByName("MainCanvas")->GetGUIObjectByName(it->second->GetName() + GetParent()->GetName());
			text->message = ss.str();
		}
	}

}
void AIEmotion::DisableRenderStats()
{
	if (isRenderingStats)
	{
		auto it = needs.begin();

		for (; it != needs.end(); it++)
		{
			GUIManager::Instance().GetCanvasByName("MainCanvas")->RemoveGUIOBject(it->second->GetName() + GetParent()->GetName());
		}

		isRenderingStats = 0;

	}
}
