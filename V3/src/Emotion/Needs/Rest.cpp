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
		
		// If the method is true, we have found an affordance object in the specified range
		// That would be pointed by "selectedObj" in the Affordance Agent
		glm::vec3 toObj = aa->selectedObj->gameObject->transform.GetGlobalPosition() - aa->GetParent()->transform.GetGlobalPosition();

		// Walk towards the affordance object
		if (glm::length2(toObj) > 0.1)
		{
			aa->GetParent()->transform.Translate(glm::normalize(toObj) * Timer::GetDeltaS() * 4.0f);
			aa->GetParent()->transform.RotateYTowards(aa->selectedObj->gameObject->transform.GetGlobalPosition());
		}
		else
		{
			// When close enough enage it
			aa->ExecuteAffordanceEngageCallback(aa->GetSelectedAffordanceName(), ai);
		}
		
		return true;
	}
	else
	{
		if (aa->HasInUseObject())
		{
			aa->ExecuteAffordanceUpdateCallback(aa->GetSelectedAffordanceName(), ai);
			return true;
		}
		else
			return false;
	}
}

void Rest::FinishSeek(AIEmotion* ai, AffordanceAgent * aa)
{
	Logger::LogInfo(ai->GetParent()->GetName() + " disengaged affordance");
	aa->ExecuteAffordanceDisengageCallback(aa->GetSelectedAffordanceName());
}
