#pragma once
#include "Event.h"

/**
* @class LogicUpdateEvent
* @brief Event dispatched when is time for a logic update
*
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class LogicUpdateEvent : public Event
{
public:
	/**
	* @brief		Creates event object
	*
	* @pre			The event object does not exist
	* @post			The event object is created
	*/
	LogicUpdateEvent() {}
	/**
	* @brief		Destroy the event object
	*
	* @pre			The event object exists
	* @post			The event object is destroyed
	*/
	~LogicUpdateEvent() {/* Logger::LogError("Logic update event destroyed");*/ }
};

/**
* @class LogicUpdateEvent
* @brief Event dispatched when is time for a engine update
*
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class EngineUpdateEvent : public Event
{
public:
	/**
	* @brief		Creates event object
	*
	* @pre			The event object does not exist
	* @post			The event object is created
	*/
	EngineUpdateEvent() { }
	/**
	* @brief		Destroy the event object
	*
	* @pre			The event object exists
	* @post			The event object is destroyed
	*/
	~EngineUpdateEvent() { /*Logger::LogError("Engine update event destroyed");*/ }
};

/**
* @class LogicUpdateEvent
* @brief Event dispatched when is time for a late update
*
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class LateUpdateEvent : public Event
{
public:
	/**
	* @brief		Creates event object
	*
	* @pre			The event object does not exist
	* @post			The event object is created
	*/
	LateUpdateEvent() {}
	/**
	* @brief		Destroy the event object
	*
	* @pre			The event object exists
	* @post			The event object is destroyed
	*/
	~LateUpdateEvent() {}
};

/**
* @class LogicUpdateEvent
* @brief Event dispatched when is time for a rendering
*
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class RenderEvent : public Event
{
public:
	/**
	* @brief		Creates event object
	*
	* @pre			The event object does not exist
	* @post			The event object is created
	*/
	RenderEvent() {}
	/**
	* @brief		Destroy the event object
	*
	* @pre			The event object exists
	* @post			The event object is destroyed
	*/
	~RenderEvent() {}
};