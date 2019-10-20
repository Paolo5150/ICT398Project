#include "pch.h"
#include "Rest.h"
#include "..\..\Core\Logger.h"
#include "..\..\Components\AffordanceAgent.h"
#include "..\..\Core\Timer.h"


Rest::Rest(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier) : Need(NeedType::Rest, "Rest", startValue, 30, 65, positiveGainMultiplier, negativeGainMultiplier, priority)
{
}


Rest::~Rest()
{
}

bool Rest::Seek(AIEmotion* ai, AffordanceAgent* aa)
{
	
	if (aa->LookForBestScoreAffordanceObjectByAffordanceTypeInRange(Affordance::AffordanceTypes::REST, 100))
	{
		return true;
	}
	else
	{
			return false;
	}
}

void Rest::FinishSeek(AIEmotion* ai, AffordanceAgent * aa)
{
	//Logger::LogInfo(ai->GetParent()->GetName() + " disengaged affordance");
	aa->ExecuteAffordanceDisengageCallback(aa->GetSelectedAffordanceName());
}
