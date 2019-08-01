#pragma once
#include "Event.h"

class Scene;

/**
* @class SceneChangedEvent
* @brief Event dispatched when a new scene is launched
*
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class SceneChangedEvent : public Event
{
public:
	/**
	* @brief		Creates event object
	*
	* @pre			The event object does not exist
	* @post			The event object is created
	*
	* @param s		The new scene
	*/
	SceneChangedEvent(Scene* s) :  currentScene(s) {}


	/**
	* @brief		Destroy the event object
	*
	* @pre			The event object exists
	* @post			The event object is destroyed
	*/
	~SceneChangedEvent() {}


	/**
	* @brief		The new scene
	*/
	Scene* currentScene;
};

/**
* @class QuitRequestEvent
* @brief Event dispatched when the user tries to quit
*
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class QuitRequestEvent : public Event
{
public:
	/**
	* @brief		Creates event object
	*
	* @pre			The event object does not exist
	* @post			The event object is created

	*/
	QuitRequestEvent() {}

	/**
	* @brief		Destroy the event object
	*
	* @pre			The event object exists
	* @post			The event object is destroyed
	*/
	~QuitRequestEvent() {}

};

