#include "pch.h"
#include "NeedFactory.h"
#include "Needs/Anger.h"
#include "Needs/Anticipation.h"
#include "Needs/Thirst.h"
#include "Needs/Rest.h"
#include "Needs/Joy.h"
#include "Needs/Trust.h"
#include "Needs/LightNeed.h"

#include "Needs/Social.h"
#include "..\Core\Logger.h"
#include <boost/algorithm/string.hpp>


NeedFactory::NeedFactory()
{
}


NeedFactory::~NeedFactory()
{
}

int NeedFactory::GetNeedType(std::string needName)
{
	if (strcmp("anger", needName.c_str()) == 0)
	{
		return Need::NeedType::Anger;
	}
	else if (strcmp("anticipation", needName.c_str()) == 0)
	{
		return Need::NeedType::Anticipation;
	}
	else if (strcmp("joy", needName.c_str()) == 0)
	{
		return Need::NeedType::Joy;
	}
	else if (strcmp("trust", needName.c_str()) == 0)
	{
		return Need::NeedType::Trust;
	}
	else if (strcmp("thirst", needName.c_str()) == 0)
	{
		return Need::NeedType::Thirst;
	}
	else if (strcmp("rest", needName.c_str()) == 0)
	{
		return Need::NeedType::Rest;
	}
	else if (strcmp("social", needName.c_str()) == 0)
	{
		return Need::NeedType::Social;
	}
	else if (strcmp("light", needName.c_str()) == 0)
	{
		return Need::NeedType::Light;
	}
	else
	{
		Logger::LogError("NEED FACTORY: \"" + needName + "\" NOT VALID NEED NAME");
		return -1;
	}
}

std::unique_ptr<Need> NeedFactory::GetNeed(Need::NeedType type, float startValue, int priority, float positiveGainMultiplier, float negativeGainMultiplier)
{
	std::unique_ptr<Need> need(nullptr);
	switch (type)
	{
	case Need::NeedType::Anger:
		need = std::unique_ptr<Anger>(new Anger(startValue, priority, positiveGainMultiplier, negativeGainMultiplier));
		break;
	case Need::NeedType::Anticipation:
		need = std::unique_ptr<Anticipation>(new Anticipation(startValue, priority, positiveGainMultiplier, negativeGainMultiplier));
		break;
	case Need::NeedType::Joy:
		need = std::unique_ptr<Joy>(new Joy(startValue, priority, positiveGainMultiplier, negativeGainMultiplier));
		break;
	case Need::NeedType::Trust:
		need = std::unique_ptr<Trust>(new Trust(startValue, priority, positiveGainMultiplier, negativeGainMultiplier));
		break;
	case Need::NeedType::Thirst:
		need = std::unique_ptr<Thirst>(new Thirst(startValue, priority, positiveGainMultiplier, negativeGainMultiplier));
		break;
	case Need::NeedType::Rest:
		need = std::unique_ptr<Rest>(new Rest(startValue, priority, positiveGainMultiplier, negativeGainMultiplier));
		break;
	case Need::NeedType::Social:
		need = std::unique_ptr<Social>(new Social(startValue, priority, positiveGainMultiplier, negativeGainMultiplier));
		break;
	case Need::NeedType::Light:
		need = std::unique_ptr<LightNeed>(new LightNeed(startValue, priority, positiveGainMultiplier, negativeGainMultiplier));
		break;

	}

	return need;
}
