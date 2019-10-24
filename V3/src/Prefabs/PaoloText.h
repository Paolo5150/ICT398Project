#pragma once
#include "..\Core\GameObject.h"

/**
* @class PaoloText
* @brief Premade gameobject for a PaoloText object
*
*
* @author Paolo Ferri
* @version 01
* @date 05/10/2019
*
*
* @bug No known bugs.
*/

class PaoloText : public GameObject
{

public:
	/**
	* @brief						Create a new object
	*/
	PaoloText();
	/**
	* @brief						Destroy the object
	*/
	~PaoloText();

	/**
	* @brief						Update the object
	* @pre							The object must exist
	*/
	void Update() override;


private:

};