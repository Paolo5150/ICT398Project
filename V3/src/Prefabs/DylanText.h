#pragma once
#include "..\Core\GameObject.h"

/**
* @class DylanText
* @brief Premade gameobject for a DylanText object
*
*
* @author Paolo Ferri
* @version 01
* @date 05/10/2019
*
*
* @bug No known bugs.
*/

class DylanText : public GameObject
{

public:
	/**
	* @brief						Create a new object
	*/
	DylanText();
	/**
	* @brief						Destroy the object
	*/
	~DylanText();

	/**
	* @brief						Update the object
	* @pre							The object must exist
	*/
	void Update() override;


private:

};