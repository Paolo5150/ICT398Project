#pragma once

#include "..\Core\Transform.h"

/**
* @class Collision
* @brief Class for storing data about a collision between two entities for ease of data transfer
*
*
* @author Drew Paridaens
* @version 01
* @date 09/01/2019
*
* @bug No known bugs.
*/
class Collision
{
public:
	Collision(glm::vec3 collisionPoint, glm::vec3 collisionNormal);
	~Collision();
	glm::vec3 Point() const;
	glm::vec3 Normal() const;

private:
	glm::vec3 collisionPoint;
	glm::vec3 collisionNormal;

};
