#pragma once
#include "..\Affordances\Affordance.h"
#include "..\Affordances\AffordanceManager.h"
#include "..\Affordances\AffordanceObject.h"
#include "..\Core\Component.h"
#include "..\Utils\FileUtils.h"



class AffordanceAgent : public Component
{
public:
	AffordanceAgent();
	virtual ~AffordanceAgent();

	template<class T>
	void AddAffordanceEngageCallback(std::function<void(AffordanceObject*)>);

	template<class T>
	void AddAffordanceDisengageCallback(std::function<void()>);

	template<class T>
	void ExecuteAffordanceEngageCallback(AffordanceObject* obj);

	template<class T>
	void ExecuteAffordanceDisengageCallback();

	AffordanceObject* selectedObj;


protected:

	std::map<std::string, std::function<void(AffordanceObject*)>> affordanceEngageCallbackMap;
	std::map<std::string, std::function<void()>> affordanceDisengageCallbackMap;

	std::map<std::string,  AffordanceObject*> affordanceObjectUsedmap;


};

template<class T>
void AffordanceAgent::AddAffordanceDisengageCallback(std::function<void()> callback)
{
	std::string affName = FileUtils::GetClassNameW<T>();
	affordanceDisengageCallbackMap[affName] = callback;
}

template<class T>
void AffordanceAgent::AddAffordanceEngageCallback(std::function<void(AffordanceObject*)> callback)
{
	std::string affName = FileUtils::GetClassNameW<T>();
	affordanceEngageCallbackMap[affName] = callback;

}

template<class T>
void AffordanceAgent::ExecuteAffordanceEngageCallback(AffordanceObject* obj)
{
	std::string affName = FileUtils::GetClassNameW<T>();
	auto objIt = affordanceObjectUsedmap.find(affName);
	if (objIt == affordanceObjectUsedmap.end())
	{
		auto it = affordanceEngageCallbackMap.find(affName);

		if (it != affordanceEngageCallbackMap.end())
		{
			it->second(obj);
			obj->ExecuteAffordanceCallback(affName);
			affordanceObjectUsedmap[affName] = obj;
		}
	}
}


template<class T>
void AffordanceAgent::ExecuteAffordanceDisengageCallback()
{
	if (selectedObj == nullptr) return;
	std::string affName = FileUtils::GetClassNameW<T>();
	auto objIt = affordanceObjectUsedmap.find(affName);
	if (objIt != affordanceObjectUsedmap.end())
	{
		auto it = affordanceDisengageCallbackMap.find(affName);

		if (it != affordanceDisengageCallbackMap.end())
		{
			it->second();
			affordanceObjectUsedmap[affName] = nullptr;
			selectedObj = nullptr;
		}
	}
}
