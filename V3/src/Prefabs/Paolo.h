#pragma once
#include "..\Core\GameObject.h"

/**
* @class Paolo
* @brief Premade gameobject for a Paolo face object
*
*
* @author Paolo Ferri
* @version 01
* @date 05/10/2019
*
*
* @bug No known bugs.
*/

class Paolo : public GameObject
{

public:
	/**
	* @brief						Create a new object
	*/
	Paolo();
	/**
	* @brief						Destroy the object
	*/
	~Paolo();

	/**
	* @brief						Update the object
	* @pre							The object must exist
	*/
	void Update() override;


private:

};