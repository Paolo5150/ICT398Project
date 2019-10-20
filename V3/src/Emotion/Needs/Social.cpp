#include "pch.h"
#include "Social.h"
#include "../../Core/Logger.h"
#include "../../Components/AIEmotion.h"
#include "..\..\Components\AffordanceAgent.h"
#include "..\..\Core\Timer.h"

Social::Social(float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier) : Need(NeedType::Social, "Social", startValue, 50, 70, positiveGainMultiplier, negativeGainMultiplier, priority)
{
}


Social::~Social()
{
}

bool Social::Seek(AIEmotion* ai, AffordanceAgent* aa)
{
	AffordanceObject* ao = dynamic_cast<AffordanceObject*>(aa->GetParent());
	if (ao == nullptr)
		return false;
	if (aa->LookForBestScoreAffordanceObjectByAffordanceTypeInRangeNotTarget(Affordance::AffordanceTypes::SOCIAL, ao, 40))
	{
		//// If the method is true, we have found an affordance object in the specified range
		//// That would be pointed by "selectedObj" in the Affordance Agent
		//glm::vec3 toObj = aa->selectedObj->gameObject->transform.GetGlobalPosition() - aa->GetParent()->transform.GetGlobalPosition();

		//// Walk towards the affordance object
		//if (glm::length2(toObj) > 30)
		//{
		//	aa->GetParent()->transform.Translate(glm::normalize(toObj) * Timer::GetDeltaS() * 4.0f);
		//	aa->GetParent()->transform.RotateYTowards(aa->selectedObj->gameObject->transform.GetGlobalPosition());
		//}
		//else
		//{
		//	// When close enough enage it
		//	aa->ExecuteAffordanceEngageCallback(aa->GetSelectedAffordanceName(), ai);
		//}

		return true;
	}
	else
	{
		/*if (aa->HasInUseObject())
		{
			//glm::vec3 toObj = aa->selectedObj->gameObject->transform.GetGlobalPosition() - aa->GetParent()->transform.GetGlobalPosition();

			// Check if affordance is now out of range
			/*if (glm::length2(toObj) < 30)
			{*/
			//aa->ExecuteAffordanceUpdateCallback(aa->GetSelectedAffordanceName(), ai);
			//return true;
			/*}
			else
				return false;*/
		//}
		//else
			return false;
	}
}

void Social::FinishSeek(AIEmotion* ai, AffordanceAgent * aa)
{
	aa->ExecuteAffordanceDisengageCallback(aa->GetSelectedAffordanceName());
	Logger::LogInfo("Finished Socialising");
}
