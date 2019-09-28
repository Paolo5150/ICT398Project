#include "pch.h"
#include "NeedFactory.h"
#include "Needs/Rage.h"
#include "Needs/Thirst.h"
#include "Needs/Rest.h"
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
	if (strcmp("rage", needName.c_str()) == 0)
	{
		return Need::NeedType::Rage;
	}
	else if (strcmp("thirst", needName.c_str()) == 0)
	{
		return Need::NeedType::Thirst;
	}
	else if (strcmp("rest", needName.c_str()) == 0)
	{
		return Need::NeedType::Rest;
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
	case Need::NeedType::Rage:
		need = std::unique_ptr<Rage>(new Rage(startValue, priority, positiveGainMultiplier, negativeGainMultiplier));
		break;
	case Need::NeedType::Thirst:
		need = std::unique_ptr<Thirst>(new Thirst(startValue, priority, positiveGainMultiplier, negativeGainMultiplier));
		break;
	case Need::NeedType::Rest:
		need = std::unique_ptr<Rest>(new Rest(startValue, priority, positiveGainMultiplier, negativeGainMultiplier));
		break;
	}

	return need;
}
