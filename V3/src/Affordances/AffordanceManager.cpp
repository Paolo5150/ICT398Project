#include "pch.h"
#include "AffordanceManager.h"
#include "AffordanceObject.h"
#include "Affordance.h"
#include "..\Events\ApplicationEvents.h"
#include "..\Events\EventDispatcher.h"

AffordanceManager& AffordanceManager::Instance()
{
	static AffordanceManager instance;
	return instance;
}

AffordanceManager::~AffordanceManager()
{

}

AffordanceManager::AffordanceManager()
{
	// When the scene changes, removes all canvas and recreate the main one as per default
	EventDispatcher::Instance().SubscribeCallback<SceneChangedEvent>([this](Event* e) {
		affordanceMap.clear();
	
		return 0;
	});
	
}

void AffordanceManager::RegisterAffordanceObject(std::string affName,AffordanceObject* obj)
{
	affordanceMap[affName].insert(obj);
}


