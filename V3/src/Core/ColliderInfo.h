#pragma once
#include "..\Utils\Maths.h"
#include <sstream>

class ColliderInfo
{
public:
	glm::vec3 p;
	glm::vec3 s;
	glm::vec3 r;
	float mass;
	bool render;
	bool isActive;
	std::string type;
	ColliderInfo(std::string type,glm::vec3 p, glm::vec3 s, glm::vec3 r, float mass, bool rend, bool isActive)
	{
		this->type = type;
		this->p = p;
		this->s = s;
		this->r = r;
		this->mass = mass;
		this->render = rend;
		this->isActive = isActive;

	}

	// Constructor with no rotation used by sphere collider
	ColliderInfo(std::string type, glm::vec3 p, glm::vec3 s, float mass, bool rend, bool isActive)
	{
		this->type = type;
		this->p = p;
		this->s = s;
		this->mass = mass;

		this->render = rend;
		this->isActive = isActive;
	}
};