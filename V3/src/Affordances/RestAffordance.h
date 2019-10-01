#pragma once
#include <string>
#include "Affordance.h"

class SitAffordance : public Affordance
{
public:
	SitAffordance() 
	{
		score = 50;
		affordanceType = AffordanceTypes::REST;
		affordanceName = "SitAffordance";
		Callback = []() { Logger::LogInfo("Someone sit on me"); };
	}
	virtual ~SitAffordance() {};


};

class LaydownAffordance : public Affordance
{
public:
	LaydownAffordance() 
	{
		score = 50;
		affordanceType = AffordanceTypes::REST;
		affordanceName = "LaydownAffordance";
		Callback = []() { Logger::LogInfo("Someone laid down on me"); };
	}
	virtual ~LaydownAffordance() {};


};