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
	PathNode* nextNode = nullptr;
	PathNode* startNode = PathFindingManager::Instance().ClosestNodeAt(start.x, start.y, start.z);
	PathNode* endNode = PathFindingManager::Instance().ClosestNodeAt(end.x, end.y, end.z);

	PathNode* currentNode = startNode;

	std::vector<std::vector<PathNode*>> closed;
	std::vector<std::vector<PathNode*>> open = PathFindingManager::Instance().nodeMap;

	open.erase(std::find(open.begin(), open.end(), startNode));

	while (open.size() != 0 && nextNode != endNode)
	{
		for (auto itx = open.begin(); itx != open.end(); itx++)
		{
			for (auto ity = (*itx).begin(); ity != (*itx).end(); ity++)
			{
				//find least f, assign to q
				//pop q from open
				for (unsigned int i = 0; (*ity)->neighbors.size(); i++)
				{
					if ((*ity)->neighbors[i] == endNode)
					{
						return;
					}
					else
					{
						(*ity)->neighbors[i]->distanceFromPrevious = glm::length((*ity)->transform.GetPosition() - (*ity)->neighbors[i]->transform.GetPosition());
						(*ity)->neighbors[i]->distanceFromTarget = glm::length(endNode->transform.GetPosition() - (*ity)->neighbors[i]->transform.GetPosition());
						double total = (*ity)->neighbors[i]->distanceFromPrevious + (*ity)->neighbors[i]->distanceFromTarget + (*ity)->neighbors[i]->cost;
						(*ity)->neighbors[i]->cost = total;
						(*ity)->neighbors[i]->checked = true;
						if (total < nextNode->cost)
						{
							nextNode = (*ity)->neighbors[i];
						}

					}
				}
			}
		}

		if (nextNode != nullptr)
		{
			path.push_back(nextNode->transform.GetPosition());
		}
		else
		{
			Logger::LogError("No path found");
		}
	}
}

glm::vec3 PathFinder::GetNextNode()
{
	return glm::vec3();
}
