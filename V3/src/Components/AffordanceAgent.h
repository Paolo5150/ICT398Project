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
	bool IsAffordanceSupported();

	template<class T>
	void AddAffordanceDisengageCallback(std::function<void()>);

	template<class T>
	void ExecuteAffordanceEngageCallback(AffordanceObject* obj);

	template<class T>
	void ExecuteAffordanceDisengageCallback();

	template<class T>
	bool LookForBestScoreAffordanceObjectInRange(float range);

	AffordanceObject* selectedObj;

	void Update() override;


protected:

	std::map<std::string, std::function<void(AffordanceObject*)>> affordanceEngageCallbackMap;
	std::map<std::string, std::function<void()>> affordanceDisengageCallbackMap;

	AffordanceObject* inUseObj;



};

template<class T>
bool AffordanceAgent::LookForBestScoreAffordanceObjectInRange(float range)
{
	if (IsAffordanceSupported<T>() && inUseObj == nullptr)
	{
		if (selectedObj == nullptr)
		{
			selectedObj = AffordanceManager::Instance().GetBestScoreObjectOfTypeWithinRange<SitAffordance>(_parent->transform.GetGlobalPosition(), range);
			return selectedObj != nullptr;
		}
		else
			return true;
	}
	else
		return false;

}

template<class T>
bool AffordanceAgent::IsAffordanceSupported()
{
	std::string affName = FileUtils::GetClassNameW<T>();
	auto objIt = affordanceEngageCallbackMap.find(affName);
	return objIt != affordanceEngageCallbackMap.end();

}

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

	if (inUseObj == nullptr)
	{
		auto it = affordanceEngageCallbackMap.find(affName);

		if (it != affordanceEngageCallbackMap.end())
		{
			it->second(obj);
			obj->ExecuteAffordanceCallback(affName);
			inUseObj = obj;
			obj->AddUser(_parent);			
		}
	}
}


template<class T>
void AffordanceAgent::ExecuteAffordanceDisengageCallback()
{
	if (selectedObj == nullptr || inUseObj == nullptr) return;

	std::string affName = FileUtils::GetClassNameW<T>();

	if (inUseObj != nullptr)
	{
		auto it = affordanceDisengageCallbackMap.find(affName);

		if (it != affordanceDisengageCallbackMap.end())
		{
			it->second();
			inUseObj->ReleaseUse(_parent);
			inUseObj = nullptr;
			selectedObj = nullptr;

		}
	}
}
