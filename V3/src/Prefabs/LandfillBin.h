#pragma once
#include "..\Core\GameObject.h"

class Rigidbody;
/**
* @class LandfillBin
* @brief Premade gameobject for a LandfillBin object
*
*
* @author Paolo Ferri
* @version 01
* @date 05/10/2019
*
*
* @bug No known bugs.
*/
class LandfillBin : public GameObject
{

public:
	/**
		* @brief						Create a new LandfillBin object
		*/
	LandfillBin();
	/**
	* @brief						Destroy the LandfillBin object
	*/
	~LandfillBin();

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
	Rigidbody* rb;

};
