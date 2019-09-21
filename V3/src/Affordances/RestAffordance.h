#pragma once
#include <string>
#include "Affordance.h"

class SitAffordance : public Affordance
{
public:
	SitAffordance() : Affordance("SitAffordance")
	{
		
		Callback = []() {Logger::LogInfo("Someone sit on me!"); };
		score = 50;
		AddAffordanceType(REST);
	}
	virtual ~SitAffordance() {};


};

class LaydownAffordance : public Affordance
{
public:
	LaydownAffordance() : Affordance("LaydownAffordance")
	{

		Callback = []() {Logger::LogInfo("Someone laid down on me!"); };
		score = 80;
		AddAffordanceType(REST);

	}
	virtual ~LaydownAffordance() {};


};