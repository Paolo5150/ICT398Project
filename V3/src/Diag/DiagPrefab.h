#pragma once

#include <iostream>
#include "..\Components\MeshRenderer.h"
#include "..\Utils\Maths.h"
#include "..\Utils\ContentManager.h"
#include "..\Core\Transform.h"


/**
* @class DiagPrefab
* @brief Parent class that defines a diagnostic renderable shape
*
*
* @author Paolo Ferri
* @version 01
* @date 21/09/2019
*
*
* @bug No known bugs.
*/

class DiagPrefab
{
public:
	/**
	* @brief Constructor
	*/
	DiagPrefab();
	/**
	* @brief Destructor
	*/
	virtual ~DiagPrefab();
	/**
	* @brief The transform of the object
	*/
	Transform transform;
	/**
	* @brief The mesh renderer component
	*/
	std::unique_ptr<MeshRenderer> meshRenderer;
	/**
	* @brief The color of the object
	*/
	glm::vec3 color;

protected:
	Material material;

};