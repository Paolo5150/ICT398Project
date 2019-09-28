#pragma once

#include "../Core/Component.h"
#include "../Emotion/Need.h"
#include "../Emotion/Stimuli.h"
#include "../Emotion/Trait.h"

#include <list>
#include <map>
#include <string>

class AIEmotion :
	public Component
{
public:
	AIEmotion();
	AIEmotion(std::string personalityName);
	~AIEmotion();
	void AddStimuli(const Stimuli& stimuli);
	bool HasNeedType(Need::NeedType needType);
	float GetNeedValue(Need::NeedType needType);
	void OnAttach(GameObject* go) override;
	void EngineUpdate() override;

private:
	float timer;
	std::string personalityName;
	Need* currentlySeekedNeed = nullptr;
	bool LoadPersonality();
	std::map<Need::NeedType, std::unique_ptr<Need>> needs = std::map<Need::NeedType, std::unique_ptr<Need>>();
	std::list<std::unique_ptr<Trait>> traits = std::list<std::unique_ptr<Trait>>();
	std::list<std::unique_ptr<Stimuli>> effectedStimuli = std::list<std::unique_ptr<Stimuli>>();
	void UpdateStimuli();
	void UpdateNeeds();

};

