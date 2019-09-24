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

	PathNode* currentNode = startNode;

	std::vector<std::unique_ptr<PathNode>> closed;
	std::vector<std::unique_ptr<PathNode>> open = PathFindingManager::Instance().pathNodes;

	open.erase(std::find(open.begin(), open.end(), startNode));

	while (open.size() != 0)
	{
		for (auto it = open.begin(); it != open.end(); it++)
		{
			//find least f, assign to q
			//pop q from open
			for (unsigned int i = 0; (*it)->neighbors.size(); i++)
			{
				if ((*it)->neighbors.at(i) == endNode)
				{
					return;
				}
				else
				{
					currentNode->neighbors[i]->distanceFromPrevious = glm::length(currentNode->transform.GetPosition() - currentNode->neighbors[i]->transform.GetPosition());
					currentNode->neighbors[i]->distanceFromTarget = glm::length(endNode->transform.GetPosition() - currentNode->neighbors[i]->transform.GetPosition());
				}
			}
		}
	}
}

glm::vec3 PathFinder::GetNextNode()
{
	return glm::vec3();
}
