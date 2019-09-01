#include "pch.h"
#include "Collision.h"


Collision::Collision(glm::vec3 collisionPoint, glm::vec3 collisionNormal) : collisionPoint(collisionPoint), collisionNormal(collisionNormal)
{
}


Collision::~Collision()
{
}

glm::vec3 Collision::Point()
{
	return collisionPoint;
}

glm::vec3 Collision::Normal()
{
	return collisionNormal;
}
