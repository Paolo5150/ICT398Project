#pragma once
#include "..\Core\GameObject.h"
#include "..\Components\Rigidbody.h"
#include "..\Affordances\AffordanceObject.h"

/**
* @class Table
* @brief Premade gameobject for a Table object
*
*
* @author Paolo Ferri
* @version 01
* @date 05/10/2019
*
*
* @bug No known bugs.
*/

class Table : public GameObject, public AffordanceObject
{

public:
	/**
		* @brief						Create a new Chair object
		*/
	Table();
	/**
	* @brief						Destroy the Chair object
	*/
	~Table();

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

private:
	Rigidbody* rb;
};