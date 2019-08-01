#pragma once
#include "Event.h"

/**
* @class WindowResizeEvent
* @brief Event dispatched when the user resizes the window
*
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class WindowResizeEvent : public Event
{
public:
	/**
	* @brief		Creates event object
	*
	* @pre			The event object does not exist
	* @post			The event object is created
	* @param w		The new window width
	* @param h		The new window height
	*/
	WindowResizeEvent(int w, int h) : width(w),height(h) {}
	/**
	* @brief		Destroy the event object
	*
	* @pre			The event object exists
	* @post			The event object is destroyed
	*/
	~WindowResizeEvent() {}
	/**
	* @brief		The new window width
	*/
	int width;
	/**
	* @brief		The new window height
	*/
	int height;
};

/**
* @class WindowCloseEvent
* @brief Event dispatched when the user closes the window
*
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/

class WindowCloseEvent : public Event
{
public:
	/**
	* @brief		Creates event object
	*
	* @pre			The event object does not exist
	* @post			The event object is created
	*/
	WindowCloseEvent()  {}
	/**
	* @brief		Destroy the event object
	*
	* @pre			The event object exists
	* @post			The event object is destroyed
	*/
	~WindowCloseEvent() {}


};

