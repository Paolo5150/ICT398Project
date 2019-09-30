#pragma once

#include <string>

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
		Rest
	};
	Need(NeedType type, std::string name, float value, float lowSeekThreshold, float highSeekThreshold, float positiveGainMultiplier, float negativeGainMultiplier, int priority);
	Need(NeedType type, std::string name, float lowSeekThreshold, float highSeekThreshold);
	~Need();
	virtual bool Seek() = 0;
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

