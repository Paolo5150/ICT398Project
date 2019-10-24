#pragma once
#include "..\Core\GameObject.h"

/**
* @class DrewText
* @brief Premade gameobject for a drew text object
*
*
* @author Paolo Ferri
* @version 01
* @date 05/10/2019
*
*
* @bug No known bugs.
*/

class DrewText : public GameObject
{

public:
	/**
	* @brief						Create a new object
	*/
	DrewText();
	/**
	* @brief						Destroy the object
	*/
	~DrewText();

	/**
	* @brief						Update the object
	* @pre							The object must exist
	*/
	void Update() override;


private:

};