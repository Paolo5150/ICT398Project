#pragma once
#include "..\Core\GameObject.h"

/**
* @class Drew
* @brief Premade gameobject for a drew face object
*
*
* @author Paolo Ferri
* @version 01
* @date 05/10/2019
*
*
* @bug No known bugs.
*/
class Drew : public GameObject
{

public:
	/**
	* @brief						Create a new object
	*/
	Drew();
	/**
	* @brief						Destroy the object
	*/
	~Drew();
	/**
	* @brief						Update the object
	* @pre							The object must exist
	*/
	void Update() override;


private:

};