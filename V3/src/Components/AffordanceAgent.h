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
	void ExecuteAffordanceEngageCallback();

	template<class T>
	void ExecuteAffordanceDisengageCallback();

	void ExecuteAffordanceDisengageCallback(std::string name);
	void ExecuteAffordanceEngageCallback(std::string name);

	bool LookForBestScoreAffordanceObjectByAffordanceTypeInRange(Affordance::AffordanceTypes type, float range);


	template<class T>
	bool LookForBestScoreAffordanceObjectInRange(float range);

	AffordanceObject* selectedObj;

	void Update() override;

	std::string& GetSelectedAffordanceName() { return selectedAffordanceName; }

protected:

	std::map<std::string, std::function<void(AffordanceObject*)>> affordanceEngageCallbackMap;
	std::map<std::string, std::function<void()>> affordanceDisengageCallbackMap;

	AffordanceObject* inUseObj;
	std::string selectedAffordanceName; //Used when looking for affordance objs by type
};

template<class T>
bool AffordanceAgent::LookForBestScoreAffordanceObjectInRange(float range)
{
	if (IsAffordanceSupported<T>() && inUseObj == nullptr)
	{
		if (selectedObj == nullptr)
		{
			selectedObj = AffordanceManager::Instance().GetBestScoreObjectWithinRange<T>(_parent->transform.GetGlobalPosition(), range);
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
void AffordanceAgent::ExecuteAffordanceEngageCallback()
{

	std::string affName = FileUtils::GetClassNameW<T>();

	if (inUseObj == nullptr)
	{
		auto it = affordanceEngageCallbackMap.find(affName);

		if (it != affordanceEngageCallbackMap.end())
		{
			it->second(selectedObj);
			selectedObj->ExecuteAffordanceCallback(affName);
			inUseObj = selectedObj;
			selectedObj->AddUser(_parent);
		}
	}
}


template<class T>
void AffordanceAgent::ExecuteAffordanceDisengageCallback()
{
	// If there's no affordance object in use, no need to disengage it
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
			selectedAffordanceName = "";

		}
	}
}
