#pragma once
#include "Light.h"

/**
* @class PointLight
* @brief Specialized class for a point light object
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class PointLight : public Light
{
public:
	friend class LightManager;
	/**
	* @brief						Create a new point light object
	*
	* @post							The light object is created
	*/
	PointLight();

	/**
	* @brief					Destroy the light object
	* @pre						The light object must exist
	* @post						The light object is destroyed
	*/
	~PointLight();


};
