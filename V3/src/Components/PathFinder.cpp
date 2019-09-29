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

	if (endNode->lock == false)
	{
		std::vector<PathNode*> open; //List of possible nodes for pathfinding
		std::vector<PathNode*> closed; //List of selected nodes

		open.push_back(startNode);
		startNode->totalCost = 0.0;
		startNode->parentNode = nullptr; //This is required, otherwise the parent node is set somewhere else for some reason

		for (unsigned i = 0; i < startNode->neighbors.size(); i++) //For the nodes around the current node
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

		//Logger::LogInfo("Start node removed: ", std::find(open.begin(), open.end(), startNode) == open.end());

		while (open.size() > 0)// && closed.size() < 10)
		{
			double bestCost = 999999999;
			unsigned currentIndex = 0;

			for (unsigned i = 0; i < open.size(); i++) //Search through all open nodes
			{
				if (open.at(i) == startNode)
				{
					Logger::LogError("E1: Start node found!");
				}

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
						if (neighbor == startNode)
						{
							Logger::LogError("E2: Start node found!");
						}

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
							if (currentNode->parentNode != neighbor)
							{
								if (neighbor == startNode)
								{
									Logger::LogError("E3: Start node found!");
								}

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

			PathNode* currentNode = closed.back(); //The end node
			nodePath.clear(); //Empty old path if there is one
			//nodePath.push_back(currentNode); //Push the end node to the start of the vector

			Logger::LogInfo("StartNode: ", startNode, ", Parent: ", startNode->parentNode);
			unsigned i = 0;
			while (currentNode->parentNode != nullptr) //While we haven't reached the start node
			{
				Logger::LogInfo("----------------------------------------");
				Logger::LogInfo("(", i, "), Node: ", currentNode, ", Parent: ", currentNode->parentNode);
				Logger::LogInfo("X: ", currentNode->transform.GetGlobalPosition().x, ", Y: ", currentNode->transform.GetGlobalPosition().y, ", Z: ", currentNode->transform.GetGlobalPosition().z);
				Logger::LogInfo("----------------------------------------");
				nodePath.push_back(currentNode->parentNode); //Push the parent of this node to the vector
				currentNode = currentNode->parentNode; //Move to the parent
				i++;
				if (i > 25)
					break;
			}

			nodePath.push_back(currentNode); //Add the start node to the path

			std::reverse(nodePath.begin(), nodePath.end()); //Save parent-based path in the correct order (start node first)

			path.clear(); //Empty old path if there is one
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

//--------------------
//To be finished, erase not working for some reason
//--------------------
/*glm::vec3 PathFinder::GetNextNodePos() const
{
	glm::vec3 pos = nodePath.at(0)->transform.GetGlobalPosition();
	nodePath.erase(nodePath.begin(), nodePath.end());
	return pos;
}*/

void PathFinder::UnlockEndNode()
{
	if (lockedNode != nullptr)
	{
		lockedNode->lock = false;
		lockedNode = nullptr;
	}
}