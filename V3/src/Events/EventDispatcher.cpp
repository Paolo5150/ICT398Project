#include "pch.h"

#include "EventDispatcher.h"

EventDispatcher& EventDispatcher::Instance()
{
	static EventDispatcher instance;
	return instance;
}

void EventDispatcher::DispatchEvent(Event* e)
{
	std::unique_ptr<Event> temp = std::unique_ptr<Event>(e);
	std::string eventName = FileUtils::GetClassName(e);
	auto it = allCallbacks.find(eventName);

	if (it != allCallbacks.end())
	{
		for (auto itl = it->second.begin(); itl != it->second.end(); itl++)
		{
			itl->fn(e);
		}
	}
}