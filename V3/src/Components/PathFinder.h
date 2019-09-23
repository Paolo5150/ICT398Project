#pragma once

#include "..\Core\Component.h"
#include "..\Physics\PathFindingManager.h"


class PathFinder : public Component
{
public:
	PathFinder();
	~PathFinder();
	void GeneratePath(glm::vec3 start, glm::vec3 end);
	glm::vec3 GetNextNode();

private:
	std::vector<glm::vec3> path;
};

