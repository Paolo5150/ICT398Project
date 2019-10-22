#include "pch.h"
#include "LightNeed.h"
#include "..\..\Core\Logger.h"
#include "..\..\Components\AIEmotion.h"
#include "..\..\Components\AffordanceAgent.h"

LightNeed::LightNeed(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier) : Need(NeedType::Light, "Light", startValue, 20, 100, positiveGainMultiplier, negativeGainMultiplier, priority)
{
}


LightNeed::~LightNeed()
{
}

bool LightNeed::Seek(AIEmotion* ai, AffordanceAgent* aa)
{
	if (aa->LookForBestScoreAffordanceObjectByAffordanceTypeInRange(Affordance::AffordanceTypes::LIGHT, 100,1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void LightNeed::FinishSeek(AIEmotion* ai, AffordanceAgent * aa)
{
	aa->ExecuteAffordanceDisengageCallback(aa->GetSelectedAffordanceName());

}
