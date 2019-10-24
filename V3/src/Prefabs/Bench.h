#pragma once
#include "..\Core\GameObject.h"


/**
* @class Bench
* @brief Premade gameobject for a bench object
*
*
* @author Paolo Ferri
* @version 01
* @date 05/10/2019
*
*
* @bug No known bugs.
*/
class Bench : public GameObject
{

public:
	/**
	* @brief						Create a new bench object
	*/
	Bench();
	/**
	* @brief						Destroy the bench object
	*/
	~Bench();
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

};