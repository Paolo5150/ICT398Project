#include "pch.h"
#include "AffordanceAgent.h"


AffordanceAgent::AffordanceAgent() : Component("AffordanceAgent")
{
	selectedObj = nullptr;
}

AffordanceAgent::~AffordanceAgent()
{
	affordanceEngageCallbackMap.clear();
}


