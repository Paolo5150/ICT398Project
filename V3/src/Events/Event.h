#pragma once

/**
* @class Event
* @brief Generic class that describes an event
*
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class Event
{
public:
	/**
	* @brief		Creates event object
	*
	* @pre			The event object does not exist
	* @post			The event object is created
	*/
	Event() {};

	/**
	* @brief		Destroy the event object
	*
	* @pre			The event object exists
	* @post			The event object is destroyed
	*/
	virtual ~Event() {};

};

