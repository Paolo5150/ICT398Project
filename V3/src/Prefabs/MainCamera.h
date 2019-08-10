#pragma once
#include "..\Core\CameraPerspective.h"
#include "..\Core\Input.h"



/**
* @class MainCamera
* @brief Specialized perspective camera used in the MainScene
*
*
* @author Paolo Ferri
* @version 01
* @date 10/04/2019
*
*
* @bug No known bugs.
*/
class MainCamera : public CameraPerspective
{
public:

	/**
	* @brief		Create a MainCamera object
	*
	* @pre			The MainCamera does not exist
	* @post			The MainCamera is created
	*
	*/
	MainCamera();

	void Update() override;



private:
	float m_movementSpeed;
	float m_rotationSpeed;
	bool blockRotation;
};

