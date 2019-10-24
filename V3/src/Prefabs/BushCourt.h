#pragma once
#include "..\Core\GameObject.h"

/**
* @class BushCourt
* @brief Premade gameobject for a BsuhCourt object
*
*
* @author Drew Paridanes
* @version 01
* @date 05/10/2019
*
*
* @bug No known bugs.
*/
class BushCourt : public GameObject
{

public:
	/**
	* @brief						Create a new BushCourt object
	*/
	BushCourt();
	/**
	* @brief						Destroy the BushCourt object
	*/
	~BushCourt();

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

private:

};