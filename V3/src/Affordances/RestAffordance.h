#pragma once
#include <string>
#include "Affordance.h"

class SitAffordance : public Affordance
{
public:
	SitAffordance() 
	{
		score = 50;
		Callback = []() { Logger::LogInfo("Someone sit on me"); };
	}
	virtual ~SitAffordance() {};


};

class LaydownAffordance : public Affordance
{
public:
	LaydownAffordance() 
	{

	}
	virtual ~LaydownAffordance() {};


};