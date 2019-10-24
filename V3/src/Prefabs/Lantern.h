#pragma once
#include "..\Core\GameObject.h"
#include "..\Affordances\AffordanceObject.h"

class Rigidbody;

/**
* @class Lantern
* @brief Premade gameobject for a Lantern object
*
*
* @author Paolo Ferri
* @version 01
* @date 05/10/2019
*
*
* @bug No known bugs.
*/

class Lantern : public GameObject, public AffordanceObject
{

public:
	/**
	* @brief						Create a new Lantern object
	*/
	Lantern();
	/**
	* @brief						Destroy the Lantern object
	*/
	~Lantern();

	/**
	* @brief						Update the object
	* @pre							The object must exist
	*/
	void Update() override;
	/**
	* @brief						Strt callbackt
	* @pre							The object must exist
	*/
	void Start() override;
	Rigidbody* rb;

private:

};