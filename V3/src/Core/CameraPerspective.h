#pragma once
#include "Camera.h"

/**
* @class CameraPerspective
* @brief Specialized camra for perspective projection
*
*
* @author Paolo Ferri
* @version 01
* @date 21/03/2019
*
*
* @bug No known bugs.
*/

class CameraPerspective : public Camera
{

public:
	/**
	* @brief Create perspective camera
	*
	* @pre The perspective camera object does notexists
	* @post The perspective camera object is created
	*
	* @param fieldOfView	The field of view of the camera
	* @param aspectRatio	The aspect ratio of the camera
	* @param nearPlane		The near clipping plane view of the camera
	* @param farPlane		The far clipping plane view of the camera
	*/
	CameraPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);

	/**
	* @brief Return the aspect ratio
	*/
	float GetAspectRatio();

	/**
	* @brief Return the field of view
	*/
	float GetFOV();




private:

	/**
	* @brief Callback method invoked when the screen is resied. Updates the projection matrix
	*
	* @param The event
	*/
	bool OnScreenResize(Event* e) override;

	/**
	* @brief The aspect ratio
	*/
	float aspectRatio;

	/**
	* @brief The field of view
	*/
	float FOV;
};