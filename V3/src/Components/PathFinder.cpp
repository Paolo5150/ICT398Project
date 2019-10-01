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

bool PathFinder::GeneratePath(glm::vec3 start, glm::vec3 end)
{
	PathNode* startNode = PathFindingManager::Instance().ClosestNodeAt(start.x, start.y, start.z);
	PathNode* currentNode = startNode;
	PathNode* endNode = PathFindingManager::Instance().ClosestNodeAt(end.x, end.y, end.z);

	UnlockEndNode(); //If there was a previous locked node, unlock it

	if (endNode->lock == false)
	{
		std::vector<PathNode*> open; //List of possible nodes for pathfinding
		std::vector<PathNode*> closed; //List of selected nodes

		open.push_back(startNode);
		startNode->totalCost = 0.0;
		startNode->parentNode = nullptr; //Make sure that the start node parent is empty, in case it has been previously set

		for (unsigned i = 0; i < startNode->neighbors.size(); i++) //Set up the nodes around the start node
		{
			PathNode* neighbor = startNode->neighbors[i];
			neighbor->parentNode = startNode; //Set this neighbor's parent to the start node
			neighbor->distanceFromPrevious = 1; //The distance from this node to the start node
			neighbor->distanceFromTarget = glm::length(endNode->transform.GetPosition() - neighbor->transform.GetPosition()); //Calculate the distance from this node to the end node
			neighbor->totalCost = neighbor->distanceFromPrevious + neighbor->distanceFromTarget + neighbor->cost; //Calculate the total cost of this node
			open.push_back(neighbor); //Add to open list
		}

		closed.push_back(startNode); //Move start node into the closed list
		open.erase(open.begin()); //Remove start node from the open list

		while (open.size() > 0)
		{
			double bestCost = 999999999; //Current best cost found in nodes
			unsigned currentIndex = 0; //Current index of node search, used to delete selected node from the open list

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
				PathNode* neighbor = currentNode->neighbors[i];

				if (std::find(closed.begin(), closed.end(), currentNode->neighbors[i]) == closed.end()) //Check that the neighbor is not in the closed list
				{
					if (std::find(open.begin(), open.end(), neighbor) == open.end()) //Check that the neighbor is not in the open list
					{
						neighbor->parentNode = currentNode; //Set this neighbor's parent to this node
						neighbor->distanceFromPrevious = currentNode->distanceFromPrevious + 1; //Calculate the distance from this node to the start node
						neighbor->distanceFromTarget = glm::length(endNode->transform.GetPosition() - neighbor->transform.GetPosition()); //Calculate the distance from this node to the end node
						neighbor->totalCost = neighbor->distanceFromPrevious + neighbor->distanceFromTarget + neighbor->cost; //Calculate the total cost of this node
						open.push_back(neighbor); //Add to open list
					}
					else
					{
						if (currentNode->distanceFromPrevious < neighbor->parentNode->distanceFromPrevious) //If this node path is shorter, update the node
						{
							if (currentNode->parentNode != neighbor) //Make sure we don't end up with an infinite loop when walking through the nodes later
							{
								neighbor->parentNode = currentNode;
							}

							neighbor->distanceFromPrevious = currentNode->distanceFromPrevious + 1; //calculate the distance from this node to the start node
							neighbor->totalCost = neighbor->distanceFromPrevious + neighbor->distanceFromTarget + neighbor->cost; //Calculate the total cost of this node
						}
					}
				}
			}
		}

		if (closed.size() > 0) //If a path was found
		{
			endNode->lock = true; //Lock the end node so no one else will use it while we are
			lockedNode = endNode; //Assign the locked node so we can unlock it later when we're done with it

			nodePath.clear(); //Empty old path if there is one
			path.clear(); //Empty old path if there is one
			PathNode* currentNode = closed.back(); //The end node

			nodePath.push_back(currentNode); //Add the end node (first node) to the path
			while (currentNode->parentNode != nullptr) //While we haven't reached the start node
			{
				nodePath.push_back(currentNode->parentNode); //Push the parent of this node to the vector
				currentNode = currentNode->parentNode; //Move to the parent
			}
			nodePath.push_back(currentNode); //Add the start node (last node) to the path

			std::reverse(nodePath.begin(), nodePath.end()); //Save parent-based path in the correct order (start node first)

			for (unsigned i = 0; i < nodePath.size(); i++) //Convert nodes into positions in the world
			{
				path.push_back(nodePath.at(i)->transform.GetGlobalPosition());
			}

			return true;

		}
		else //No path found
		{
			return false;
		}
	}
	else //End node is locked
	{
		return false;
	}
}

std::vector<PathNode*> PathFinder::GetNodes() const
{
	return nodePath;
}

std::vector<glm::vec3> PathFinder::GetPath() const
{
	return path;
}

glm::vec3 PathFinder::GetNextNodePos()
{
	glm::vec3 pos;

	if (nodePath.size() > 1) //Full path available
	{
		pos = (*nodePath.begin())->transform.GetGlobalPosition();
		(*nodePath.begin())->bc->enableRender = 0; //Temporary
		nodePath.erase(nodePath.begin());
	}
	else if (nodePath.size() == 1) //Last/only node in path available
	{
		pos = (*nodePath.begin())->transform.GetGlobalPosition(); //Return the last node in the nodepath if we run out of nodes
	}
	else
	{
		Logger::LogWarning("No generated nodes available!");
		pos = glm::vec3(0, 0, 0); //No node available
	}

	return pos;
}

void PathFinder::UnlockEndNode()
{
	if (lockedNode != nullptr)
	{
		lockedNode->lock = false;
		lockedNode = nullptr;
	}
}