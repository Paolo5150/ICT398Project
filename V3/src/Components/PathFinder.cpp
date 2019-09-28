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
	PathNode* startNode = PathFindingManager::Instance().ClosestNodeAt(start.x, start.y, start.z);
	PathNode* currentNode = startNode;
	PathNode* endNode = PathFindingManager::Instance().ClosestNodeAt(end.x, end.y, end.z);

	if (endNode->lock == false)
	{
		std::vector<PathNode*> open;
		std::vector<PathNode*> closed;

		open.push_back(startNode);
		startNode->totalCost = 0.0;

		while (open.size() > 0)// && closed.size() < 10)
		{
			double bestCost = 999999999;
			unsigned currentIndex = 0;

			for (unsigned i = 0; i < open.size(); i++) //Search through all open nodes
			{
				if (open.at(i)->totalCost < bestCost) //If this node is a better value than the current node
				{
					bestCost = open.at(i)->totalCost;
					currentNode = open.at(i);
					currentIndex = i;
				}
			}

			closed.push_back(currentNode); //Move this node into the closed list
			open.erase(std::begin(open) + currentIndex); //Remove this node from the open list

			if (currentNode == endNode) //If this node is the end node, stop looking for more nodes
			{
				break;
			}

			for (unsigned i = 0; i < currentNode->neighbors.size(); i++) //For the nodes around the current node
			{
				if (std::find(std::begin(closed), std::end(closed), currentNode->neighbors[i]) == std::end(closed)) //Check that the neighbor is not in the closed list
				{
					currentNode->neighbors[i]->parentNode = currentNode; //Set this neighbor's parent to this node
					currentNode->neighbors[i]->distanceFromPrevious = currentNode->distanceFromPrevious + glm::length(currentNode->transform.GetPosition() - currentNode->neighbors[i]->transform.GetPosition()); //Calculate the distance from this node to the start node
					currentNode->neighbors[i]->distanceFromTarget = glm::length(endNode->transform.GetPosition() - currentNode->neighbors[i]->transform.GetPosition()); //Calculate the distance from this node to the end node
					currentNode->neighbors[i]->totalCost = currentNode->neighbors[i]->distanceFromPrevious + currentNode->neighbors[i]->distanceFromTarget + currentNode->neighbors[i]->cost; //Calculate the total cost of this node

					if (std::find(std::begin(open), std::end(open), currentNode->neighbors[i]) == std::end(open)) //Check that the neighbor is not in the open list
					{
						open.push_back(currentNode->neighbors[i]); //Add to open list
					}
					else
					{
						//Could check distanceFromPrevious here and re-evaluate path
					}
				}
			}
		}

		endNode->lock = true; //Lock the end node so no one else will use it
		lockedNode = endNode;
		nodePath = closed;
	}
}

std::vector<PathNode*> PathFinder::GetNodes()
{
	return nodePath;
}

std::vector<glm::vec3> PathFinder::GetPath()
{
	std::vector<glm::vec3> path;
	for (unsigned i = 0; i < nodePath.size(); i++)
	{
		path.push_back(nodePath.at(i)->transform.GetGlobalPosition());
	}
	return path;
}

glm::vec3 PathFinder::GetNextNode()
{
	return nodePath.at(1)->transform.GetGlobalPosition();
}

void PathFinder::UnlockEndNode()
{
	if (lockedNode != nullptr)
	{
		lockedNode->lock = false;
		lockedNode = nullptr;
	}
}