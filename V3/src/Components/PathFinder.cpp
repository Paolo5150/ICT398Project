#include "pch.h"
#include "PathFinder.h"
#include <vector>
#include <algorithm>


PathFinder::PathFinder() : Component("PathFinder")
{
}

PathFinder::~PathFinder()
{
}

void PathFinder::GeneratePath(glm::vec3 start, glm::vec3 end)
{
	double fromStartCost = 0;
	double bestDistance = 999999999;
	PathNode* startNode = PathFindingManager::Instance().ClosestNodeAt(start.x, start.y, start.z);
	PathNode* endNode = PathFindingManager::Instance().ClosestNodeAt(end.x, end.y, end.z);

	PathNode* currentNode = startNode;
	PathNode* bestNode = nullptr;

	//std::vector<std::vector<PathNode*>> closed;
	std::vector<std::vector<PathNode*>> open = PathFindingManager::Instance().nodeMap;
	//closed.resize(open.size());

	//closed.push_back(startNode);
	//open.erase(std::find(std::begin(open), std::end(open), startNode));

	/*while (bestNode != endNode)
	{
		for (unsigned i = 0; i < open.size(); i++)
		{
			for (unsigned j = 0; j < open.at(i).size(); j++)
			{
				open.at(i).at(j)
			}
		}
	}*/

	while (open.size() != 0 && bestNode != endNode)
	{
		for (auto itx = open.begin(); itx != open.end(); itx++)
		{
			for (auto ity = (*itx).begin(); ity != (*itx).end(); ity++)
			{
				(*ity)->checked = false;
			}
		}

		for (auto itx = open.begin(); itx != open.end(); itx++)
		{
			for (auto ity = (*itx).begin(); ity != (*itx).end(); ity++)
			{

				for (unsigned int i = 0; (*ity)->neighbors.size(); i++)
				{
					if ((*ity)->neighbors[i] == endNode)
					{
						return;
					}
					else if((*ity)->neighbors[i]->checked == false)
					{
						(*ity)->neighbors[i]->distanceFromPrevious = glm::length((*ity)->transform.GetPosition() - (*ity)->neighbors[i]->transform.GetPosition());
						(*ity)->neighbors[i]->distanceFromTarget = glm::length(endNode->transform.GetPosition() - (*ity)->neighbors[i]->transform.GetPosition());
						double total = (*ity)->neighbors[i]->distanceFromPrevious + (*ity)->neighbors[i]->distanceFromTarget + (*ity)->neighbors[i]->cost;
						(*ity)->neighbors[i]->checked = true;
						if (total < bestDistance)
						{
							bestDistance = total;
							bestNode = (*ity)->neighbors[i];
						}

					}

					//open.erase(std::find(std::begin(open), std::end(open), (*ity)));
				}
			}
		}

		if (bestNode != nullptr)
		{
			path_.push_back(bestNode->transform.GetPosition());
		}
		else
		{
			Logger::LogError("No further path found");
		}
	}
}

std::vector<glm::vec3> PathFinder::GetPath() const
{
	return path_;
}

glm::vec3 PathFinder::GetNextNode() const
{
	glm::vec3 node = path_.at(0);
	//path_.erase(std::find(path_.begin(), path_.end(), node));
	return node;
}
