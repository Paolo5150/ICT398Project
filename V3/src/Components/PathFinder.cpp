#include "pch.h"
#include "PathFinder.h"


PathFinder::PathFinder() : Component("PathFinder")
{
}

PathFinder::~PathFinder()
{
}

void PathFinder::GeneratePath(glm::vec3 start, glm::vec3 end)
{
	PathNode* startNode = PathFindingManager::Instance().ClosestNodeAt(start.x, start.y, start.z);
	PathNode* endNode = PathFindingManager::Instance().ClosestNodeAt(end.x, end.y, end.z);

	std::vector<std::unique_ptr<PathNode>> closed;
	std::vector<std::unique_ptr<PathNode>> open = PathFindingManager::Instance().pathNodes;

	while (open.size() != 0)
	{
		for (std::vector<std::unique_ptr<PathNode>>::iterator it = open.begin(); it != open.end(); it++)
		{
			//find least f, assign to q
			//pop q from open
			for (/*each of the nodes around q*/)
			{
				if (i == endNode)
				{
					return;
				}
				else
				{

				}
			}
		}
	}
}

glm::vec3 PathFinder::GetNextNode()
{
	return glm::vec3();
}
