#pragma once
#include "..\Core\GameObject.h"
#include "Billquad.h"

class AffordanceObject;

/**
* @class Joey
* @brief Premade gameobject for a Joey NPC
*
*
* @author Paolo Ferri
* @version 01
* @date 05/10/2019
*
*
* @bug No known bugs.
*/
class Joey : public GameObject
{


public:
	/**
	* @brief						Create a new object
	*/
	Joey();
	/**
	* @brief						Destroy the object
	*/
	~Joey();
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
	void Test(AffordanceObject*);
	/**
	* @brief						Return the billquad object
	*/
	Billquad& GetBillquad() { return *billquad; }
private:
	Billquad* billquad;
	void Move(); //Navigates to affordances or wanders if no affordance is selected

};