#pragma once
#include "..\Core\GameObject.h"


/**
* @class Dylan
* @brief Premade gameobject for a Dylan face object
*
*
* @author Paolo Ferri
* @version 01
* @date 05/10/2019
*
*
* @bug No known bugs.
*/

class Dylan : public GameObject
{

public:
	/**
	* @brief						Create a new object
	*/
	Dylan();
	/**
	* @brief						Destroy the object
	*/
	~Dylan();

	/**
	* @brief						Update the object
	* @pre							The object must exist
	*/
	void Update() override;


private:

};