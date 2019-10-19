#include "pch.h"
#include "Thirst.h"
#include "../../Core/Logger.h"
#include "../../Components/AIEmotion.h"
#include "..\..\Components\AffordanceAgent.h"
#include "..\..\Core\Timer.h"

Thirst::Thirst(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier) : Need(NeedType::Thirst, "Thirst", startValue, 10, 50, positiveGainMultiplier, negativeGainMultiplier, priority)
{
}


Thirst::~Thirst()
{
}

bool Thirst::Seek(AIEmotion* ai, AffordanceAgent* aa)
{
	if (aa->LookForBestScoreAffordanceObjectByAffordanceTypeInRange(Affordance::AffordanceTypes::THIRST, 100))
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

			return false;
	}
}

void Thirst::FinishSeek(AIEmotion* ai, AffordanceAgent * aa)
{
}
