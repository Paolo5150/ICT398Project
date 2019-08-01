#include "Camera.h"


/**
* @class Camera_Orthogonal
* @brief Specialized camra for orthographic projection
*
*
* @author Paolo Ferri
* @version 01
* @date 21/03/2019
*
*
* @bug No known bugs.
*/
class CameraOrthogonal : public Camera
{

	friend class Camera;
public:
	/**
	* @brief Create orthographic camera
	*
	* @pre The orthographic camera object does notexists
	* @post The orthographic camera object is created
	*
	* @param l	The left limit
	* @param r	The right limit
	* @param b	The bottom limit
	* @param t	The top limit
	* @param n	The near limit
	* @param f	The far limit
	*/
	CameraOrthogonal(float l, float r, float b, float t, float n, float f) : Camera("Camera_Orthogonal"){

		camerType = ORTHOGONAL;

		left = l;
		right = r;
		bottom = b;
		top = t;
		nearPlane = n;
		farPlane = f;

		projectionMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);

	};

	/*
	* @brief The left limit
	*/
	float left;

	/*
	* @brief The right limit
	*/
	float right;

	/*
	* @brief The bottom limit
	*/
	float bottom;

	/*
	* @brief The top limit
	*/
	float top;

	/**
	* @brief Callback override method invoked when the screen is resied. Updates the projection matrix
	*
	* @param The event
	*/
	bool OnScreenResize(Event* e) { return 0; }; // Currently not implemented



};