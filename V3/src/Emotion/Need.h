#pragma once

#include <string>

class AffordanceAgent;
class AIEmotion;

class Need
{
public:
	enum NeedType
	{
		Anger,
		Anticipation,
		Joy,
		Trust,
		Thirst,
		Rest,
		Social,
		Light
	};
	Need(NeedType type, std::string name, float value, float lowSeekThreshold, float highSeekThreshold, float positiveGainMultiplier, float negativeGainMultiplier, int priority);
	Need(NeedType type, std::string name, float lowSeekThreshold, float highSeekThreshold);
	~Need();
	virtual bool Seek(AIEmotion* ai, AffordanceAgent* aa) = 0;
	virtual void FinishSeek(AIEmotion* ai, AffordanceAgent* aa) = 0;
	NeedType GetNeedType();
	std::string GetName();
	float GetValue();
	void SetValue(float newValue);
	float GetLowSeekThreshold();
	float GetHighSeekThreshold();
	float GetPositiveGainMultiplier();
	float GetNegativeGainMultiplier();
	int GetPriority();

private:
	NeedType type;
	std::string name;
	float value;
	float lowSeekThreshold;
	float highSeekThreshold;
	float positiveGainMultiplier;
	float negativeGainMultiplier;
	int priority;

};

