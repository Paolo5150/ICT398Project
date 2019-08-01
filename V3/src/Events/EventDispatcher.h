#pragma once
#include "Event.h"
#include "..\Core\Logger.h"
#include "..\Utils\FileUtils.h"
#include <functional>
#include <list>
#include <map>
#include <sstream>

/**
* @class CallbackObj
* @brief Wrapper class for a callback
*
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class CallbackObj
{
public:
	/**
	* @brief		Creates a callback object to be stored
	*
	* @pre			The callback object does not exist
	* @post			The callback object is created
	* @param id		The id of the callback
	* @param f		The callback function
	*/
	CallbackObj(std::string id, std::function<bool(Event*)> f) : ID(id),fn(f){};

	/**
	* @brief The callback function
	*/
	std::function<bool(Event*)> fn;

	/**
	* @brief The callback id
	*/
	std::string ID;

};

/**
* @class EventDispatcher
* @brief Manages and dispatch events to subscribed callbacks
*
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class EventDispatcher
{
public:
	/**
	* @brief		Return the event dispatcher instance
	*
	* @pre			The event dispatcher instance exists
	* @post			The event dispatcher instance is returned
	*/
	static EventDispatcher& Instance();

	/**
	* @brief		Dispatch an event to subscribed callbacks to that event
	*
	* @pre			The event dispatcher instance exists
	* @post			The event is dispatched
	* @param e		The event to be dispatched
	*/
	void DispatchEvent(Event* e);

	/**
	* @brief		Subscribe callback to event
	*
	* @pre			The event dispatcher instance exists
	* @post			The callback is subscribed
	* @param T		The event to be subscribed to
	* @param callback	The function to subscribe
	* @return		The token needed to unsubscribe the callback
	*/
	template<class T>	
	std::string SubscribeCallback(std::function<bool(Event*)> callback);

	/**
	* @brief		Unsubscribe callback by token
	*
	* @pre			The event dispatcher instance exists
	* @post			The callback to unsubscribed
	* @param token	The token used to subscribed the callback
	*/
	template<class T>
	void UnsubscribeCallback(std::string token);

private:
	/**
	* @brief		Create the event dispatche instance
	*
	* @pre			The event dispatcher instance does not exists
	* @post			The event dispatcher instance is created
	*/
	EventDispatcher() {};
	EventDispatcher& operator=(const EventDispatcher& other) = delete;
	EventDispatcher(const EventDispatcher& other) = delete;

	/**
	* @brief		The list of callbacks
	*/
	std::map<std::string,std::list < CallbackObj >> allCallbacks;

	/**
	* @brief		Incremental number for callbackIDs
	*/
	int incrementalID = 0;
};


template<class T>
void EventDispatcher::UnsubscribeCallback(std::string token)
{
	std::string eventName = FileUtils::GetClassNameW<T>();

	auto it = allCallbacks[eventName].begin();

	for (; it != allCallbacks[eventName].end();)
	{
		if (it->ID == token)
		{
			it = allCallbacks[eventName].erase(it);
		}
		else
			it++;
	}

}


template<class T>
std::string EventDispatcher::SubscribeCallback(std::function<bool(Event*)> callback)
{
	std::string eventName = FileUtils::GetClassNameW<T>();

	std::stringstream ss;
	ss << eventName;
	ss << "_";
	ss << *(long *)(char *)&callback;
	ss << "_";
	ss << incrementalID;
	incrementalID++;

	allCallbacks[eventName].push_back(CallbackObj(ss.str(),callback));
	std::string myS = ss.str();
	return myS;
}