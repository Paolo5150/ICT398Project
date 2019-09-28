#pragma once

#include "..\Core\Component.h"
#include "..\Physics\PathFindingManager.h"


class PathFinder : public Component
{
public:
	PathFinder();
	~PathFinder();
	std::vector<glm::vec3> GeneratePath(glm::vec3 start, glm::vec3 end);
	std::vector<glm::vec3> GeneratePathV1(glm::vec3 start, glm::vec3 end);
	std::vector<glm::vec3> GeneratePathV2(glm::vec3 start, glm::vec3 end);
	std::vector<glm::vec3> GetPath();
	glm::vec3 GetNextNode();


private:
	std::vector<glm::vec3> path_;
};

