#pragma once

#include "Collider.h"

/**
* @class SphereCollider
* @brief Specialized collider with sphere shape
*
*
* @author Paolo Ferri
* @version 01
* @date 27/04/2019
*
* @bug No known bugs.
*/
class SphereCollider : public Collider
{

public:
	/**
	* @brief		Constructor
	* @pre			The collider does not exist
	* @post			The collider is created
	*/
	SphereCollider() : Collider("SphereCollider")
	{
		colliderType = SPHERE;

	}
	/**
	* @brief		Destructor
	* @pre			The collider must exist
	* @post			The collider is destroyed
	*/
	~SphereCollider(){}

	/**
	* @brief		Initialize mesh renderer to render sphere
	*/
	virtual void InitializeMeshRenderer() override;

	/**
	* @brief		Overridden method for engine update, update transform
	*/
	void Update() override;

	/**
	* @brief		Initialize collider
	*/
	void Initialize(){ transform.SetIgnoreParentRotation(1); };

};