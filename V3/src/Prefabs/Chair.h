#pragma once
#include "..\Core\GameObject.h"
#include "..\Affordances\AffordanceObject.h"
#include "..\Affordances\RestAffordance.h"

/**
* @class Chair
* @brief Premade gameobject for a chair object
*
*
* @author Paolo Ferri
* @version 01
* @date 05/10/2019
*
*
* @bug No known bugs.
*/

class Chair : public GameObject, public AffordanceObject
{

public:
	/**
	* @brief						Create a new Chair object
	*/
	Chair();
	/**
	* @brief						Destroy the Chair object
	*/
	~Chair();

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
	/**
	* @brief						Collision enter callbackt
	* @param g						The other collider
	* @param collisioni				Collision information
	*/
	void OnCollisionEnter(Collider* g, Collision& collision) override;
	/**
	* @brief						Collision stay callbackt
	* @param g						The other collider
	* @param collisioni				Collision information
	*/
	void OnCollisionStay(Collider* g, Collision& collision) override;
	/**
	* @brief						Collision exit callbackt
	* @param g						The other collider
	*/
	void OnCollisionExit(Collider* g) override;

private:

};