#pragma once

#include <string>

class Need
{
public:
	enum NeedType
	{
		Rage,
		Thirst,
		Rest
	};
	Need(NeedType type, std::string name, float value, float minSeekThreshold, float positiveGainMultiplier, float negativeGainMultiplier, int priority);
	Need(NeedType type, std::string name, float minSeekThreshold);
	~Need();
	virtual bool Seek() = 0;
	NeedType GetNeedType();
	std::string GetName();
	float GetValue();
	void SetValue(float newValue);
	float GetMinSeekThreshold();
	float GetPositiveGainMultiplier();
	float GetNegativeGainMultiplier();
	int GetPriority();

private:
	NeedType type;
	std::string name;
	float value;
	float minSeekThreshold;
	float positiveGainMultiplier;
	float negativeGainMultiplier;
	int priority;

};

