#pragma once

#include "..\Core\GameObject.h"
#include "..\Components\Rigidbody.h"
#include "..\Affordances\AffordanceObject.h"

/**
* @class Box2
* @brief Premade gameobject for a box object
*
*
* @author Drew Paridanes
* @version 01
* @date 05/10/2019
*
*
* @bug No known bugs.
*/
class Box2 :
	public GameObject, public AffordanceObject
{
public:
	/**
	* @brief						Create a new box object
	*/
	Box2();
	/**
	* @brief						Destroy the box object
	*/
	~Box2();

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

	/**
	* @brief						The rigidbody component
	*/
	Rigidbody* rb;
private:
	
};
