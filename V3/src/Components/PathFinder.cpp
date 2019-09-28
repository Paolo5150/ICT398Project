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
		std::vector<PathNode*> open; //List of possible nodes for pathfinding
		std::vector<PathNode*> closed; //List of selected nodes

		open.push_back(startNode);
		startNode->totalCost = 0.0;

		while (open.size() > 0)// && closed.size() < 10)
		{
			double bestCost = 999999999;
			unsigned currentIndex = 0;

			for (unsigned i = 0; i < open.size(); i++) //Search through all open nodes
			{
				if (open.at(i)->totalCost < bestCost) //If this node is a better value than the current node, update the currentnode
				{
					bestCost = open.at(i)->totalCost;
					currentNode = open.at(i);
					currentIndex = i;
				}
			}

			closed.push_back(currentNode); //Move this node into the closed list
			open.erase(open.begin() + currentIndex); //Remove this node from the open list

			if (currentNode == endNode) //If this node is the end node, stop looking for more nodes
			{
				break;
			}

			for (unsigned i = 0; i < currentNode->neighbors.size(); i++) //For the nodes around the current node
			{
				if (std::find(closed.begin(), closed.end(), currentNode->neighbors[i]) == closed.end()) //Check that the neighbor is not in the closed list
				{
					currentNode->neighbors[i]->parentNode = currentNode; //Set this neighbor's parent to this node
					currentNode->neighbors[i]->distanceFromPrevious = currentNode->distanceFromPrevious + glm::length(currentNode->transform.GetPosition() - currentNode->neighbors[i]->transform.GetPosition()); //Calculate the distance from this node to the start node
					currentNode->neighbors[i]->distanceFromTarget = glm::length(endNode->transform.GetPosition() - currentNode->neighbors[i]->transform.GetPosition()); //Calculate the distance from this node to the end node
					currentNode->neighbors[i]->totalCost = currentNode->neighbors[i]->distanceFromPrevious + currentNode->neighbors[i]->distanceFromTarget + currentNode->neighbors[i]->cost; //Calculate the total cost of this node

					if (std::find(open.begin(), open.end(), currentNode->neighbors[i]) == open.end()) //Check that the neighbor is not in the open list
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

		if (closed.size() > 0) //If a path was found
		{
			endNode->lock = true; //Lock the end node so no one else will use it while we are
			lockedNode = endNode; //Assign the locked node so we can unlock it later when we're done with it

			std::vector<PathNode*> nodes;
			PathNode* currentNode = closed.back(); //The end node
			nodes.push_back(currentNode); //Push the end node to the start of the vector

			std::reverse(closed.begin(), closed.end()); //Reverse the order of the closed list so it starts at the end node

			for (unsigned i = 0; i < closed.size(); i++)
			{
				if (currentNode->parentNode != nullptr)
				{
					nodes.push_back(currentNode->parentNode); //Push the parent of this node to the vector
					currentNode = currentNode->parentNode; //Move to the parent
				}
			}

			nodePath = nodes; //Save parent-based path
		}
		else
		{
			//No path found
		}
	}
}

std::vector<PathNode*> PathFinder::GetNodes() const
{
	return nodePath;
}

std::vector<glm::vec3> PathFinder::GetPath() const
{
	std::vector<glm::vec3> path;
	for (unsigned i = 0; i < nodePath.size(); i++)
	{
		path.push_back(nodePath.at(i)->transform.GetGlobalPosition());
	}
	return path;
}

glm::vec3 PathFinder::GetNextNode() const
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