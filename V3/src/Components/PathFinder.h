#pragma once

#include "..\Core\Component.h"
#include "..\Physics\PathFindingManager.h"


class PathFinder : public Component
{
public:
	PathFinder();
	~PathFinder();
	void GeneratePath(glm::vec3 start, glm::vec3 end);
	std::vector<PathNode*> GetNodes();
	std::vector<glm::vec3> GetPath();
	glm::vec3 GetNextNode();
	void UnlockEndNode();

private:
	std::vector<PathNode*> nodePath;
	PathNode* lockedNode;
};

