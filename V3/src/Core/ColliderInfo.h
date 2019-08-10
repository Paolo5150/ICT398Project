#pragma once
#include "..\Utils\Maths.h"
#include <sstream>

class ColliderInfo
{
public:
	glm::vec3 p;
	glm::vec3 s;
	glm::vec3 r;
	bool render;
	std::string type;
	ColliderInfo(std::string type,glm::vec3 p, glm::vec3 s, glm::vec3 r, bool rend)
	{
		this->type = type;
		this->p = p;
		this->s = s;
		this->r = r;
		this->render = rend;
	}

	// Constructor with no rotation used by sphere collider
	ColliderInfo(std::string type, glm::vec3 p, glm::vec3 s, bool rend)
	{
		this->type = type;
		this->p = p;
		this->s = s;
		this->render = rend;
	}
};