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

std::vector<glm::vec3> PathFinder::GeneratePath(glm::vec3 start, glm::vec3 end)
{
	//double fromStartCost = 0;
	double bestCost = 999999999;
	//PathNode* bestNode = nullptr;

	PathNode* startNode = PathFindingManager::Instance().ClosestNodeAt(start.x, start.y, start.z);
	PathNode* endNode = PathFindingManager::Instance().ClosestNodeAt(end.x, end.y, end.z);

	PathNode* currentNode = startNode;

	//std::vector<std::vector<PathNode*>> closed;
	std::vector<PathNode*> open;
	std::vector<PathNode*> closed;
	open.push_back(startNode);

	startNode->fvalue = 0.0;
	//startNode->distanceFromTarget = glm::length(endNode->transform.GetPosition() - currentNode->transform.GetPosition());
	// = PathFindingManager::Instance().nodeMap;
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
	int loopCounter = 1;
	while (open.size() > 0 && closed.size() < 4)
	{
		Logger::LogInfo("Loop ", loopCounter);
		loopCounter++;
		bestCost = 999999999;
		Logger::LogInfo("Found end node!");
		for (unsigned i = 0; i < open.size(); i++)
		{
			if (open.at(i)->fvalue < bestCost)
			{
				bestCost = open.at(i)->fvalue;
				closed.push_back(open.at(i));
				currentNode = open.at(i);
				Logger::LogInfo(currentNode);
			}
		}

		if (currentNode == endNode)
		{
			Logger::LogInfo("Found end node!");
			break;
		}

		for (unsigned i = 0; i < currentNode->neighbors.size(); i++)
		{
			if (std::find(std::begin(closed), std::end(closed), currentNode->neighbors[i]) == std::end(closed)) //Check that the neighbor is not in the closed list
			{
				currentNode->neighbors[i]->parentNode = currentNode;
				currentNode->neighbors[i]->distanceFromPrevious = currentNode->distanceFromPrevious + glm::length(currentNode->transform.GetPosition() - currentNode->neighbors[i]->transform.GetPosition());
				currentNode->neighbors[i]->distanceFromTarget = glm::length(endNode->transform.GetPosition() - currentNode->neighbors[i]->transform.GetPosition());
				currentNode->neighbors[i]->fvalue = currentNode->neighbors[i]->distanceFromPrevious + currentNode->neighbors[i]->distanceFromTarget + currentNode->neighbors[i]->cost;

				if (std::find(std::begin(open), std::end(open), currentNode->neighbors[i]) != std::end(open)) //Check that the neighbor is not in the open list
				{
					open.push_back(currentNode->neighbors[i]);
				}
				else
				{
					//Check G and re-evaluate path
				}
			}
		}
	}

	std::vector<glm::vec3> path;
	for (unsigned i = 0; i < closed.size(); i++)
	{
		path.push_back(closed.at(0)->transform.GetGlobalPosition());
	}
	return path;

	/*while (bestNode != endNode)
	{

		for (unsigned int i = 0; currentNode->neighbors.size(); i++)
		{
			currentNode->neighbors[i]->checked = false;
		}

		for (unsigned int i = 0; currentNode->neighbors.size(); i++)
		{
			if (currentNode->neighbors[i] == endNode)
			{
				return;
			}
			else if (currentNode->neighbors[i]->checked == false)
			{
				currentNode->neighbors[i]->distanceFromPrevious = glm::length(startNode->transform.GetPosition() - currentNode->neighbors[i]->transform.GetPosition());
				currentNode->neighbors[i]->distanceFromTarget = glm::length(endNode->transform.GetPosition() - currentNode->neighbors[i]->transform.GetPosition());
				double heuristic = currentNode->neighbors[i]->distanceFromPrevious + currentNode->neighbors[i]->distanceFromTarget + currentNode->neighbors[i]->cost;
				currentNode->neighbors[i]->checked = true;
				if (total < bestDistance)
				{
					bestDistance = total;
					bestNode = currentNode->neighbors[i];
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
	}*/
}

std::vector<glm::vec3> PathFinder::GetPath()
{
	return path_;
}

glm::vec3 PathFinder::GetNextNode()
{
	glm::vec3 node = path_.at(0);
	//path_.erase(std::find(path_.begin(), path_.end(), node));
	return node;
}
