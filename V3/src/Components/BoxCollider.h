#pragma once

#include "Collider.h"
#include <vector>

/**
* @class BoxCollider
* @brief Specialized collider with box shape
*
*
* @author Paolo Ferri
* @version 01
* @date 27/04/2019
*
* @bug No known bugs.
*/
class BoxCollider : public Collider
{

public:
	/**
	* @brief		Constructor
	* @pre			The collider does not exist
	* @post			The collider is created
	*/
	BoxCollider() : Collider("BoxCollider")
	{
		colliderType = BOX;
		InitializeMeshRenderer();
	}
	/**
	* @brief		Destructor
	* @pre			The collider must exist
	* @post			The collider is destroyed
	*/
	~BoxCollider(){}

	/**
	* @brief		Initialize mesh renderer to render a box
	*/
	virtual void InitializeMeshRenderer() override;

	/**
	* @brief		Overridden method for engine update, update transform
	*/
	void Update() override;

	/**
	* @brief		Initialize collider
	*/
	void Initialize(){ transform.SetIgnoreParentRotation(0); };

	/**
	* @return	The box points in world spaced
	*/
	std::vector<glm::vec3> GetWorldPoints();


};