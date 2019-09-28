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

std::vector<glm::vec3> PathFinder::GeneratePathV1(glm::vec3 start, glm::vec3 end)
{
	double bestCost = 999999999;

	PathNode* startNode = PathFindingManager::Instance().ClosestNodeAt(start.x, start.y, start.z);
	PathNode* endNode = PathFindingManager::Instance().ClosestNodeAt(end.x, end.y, end.z);

	PathNode* currentNode = startNode;

	std::vector<PathNode*> open;
	std::vector<PathNode*> closed;
	open.push_back(startNode);

	startNode->fvalue = 0.0;
	int loopCounter = 1;
	while (open.size() > 0 && closed.size() < 10)
	{
		//Logger::LogInfo("Loop ", loopCounter);
		loopCounter++;
		bestCost = 999999999;
		unsigned currentIndex = 0;
		for (unsigned i = 0; i < open.size(); i++)
		{
			if (open.at(i)->fvalue < bestCost)
			{
				bestCost = open.at(i)->fvalue;
				currentNode = open.at(i);
				currentIndex = i;
				Logger::LogInfo("Adding node to closed list");
			}
		}

		closed.push_back(currentNode);
		open.erase(std::begin(open) + currentIndex);


		if (currentNode == endNode)
		{
			Logger::LogInfo("Found end node!");
			break;
		}

		for (unsigned i = 0; i < currentNode->neighbors.size(); i++)
		{
			if (std::find(std::begin(closed), std::end(closed), currentNode->neighbors[i]) == std::end(closed)) //Check that the neighbor is not in the closed list
			{
				Logger::LogInfo("Checking a node");
				currentNode->neighbors[i]->parentNode = currentNode;
				currentNode->neighbors[i]->distanceFromPrevious = currentNode->distanceFromPrevious + glm::length(currentNode->transform.GetPosition() - currentNode->neighbors[i]->transform.GetPosition());
				currentNode->neighbors[i]->distanceFromTarget = glm::length(endNode->transform.GetPosition() - currentNode->neighbors[i]->transform.GetPosition());
				currentNode->neighbors[i]->fvalue = currentNode->neighbors[i]->distanceFromPrevious + currentNode->neighbors[i]->distanceFromTarget + currentNode->neighbors[i]->cost;

				if (std::find(std::begin(open), std::end(open), currentNode->neighbors[i]) == std::end(open)) //Check that the neighbor is not in the open list
				{
					Logger::LogInfo("Adding node to open list");
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
		path.push_back(closed.at(i)->transform.GetGlobalPosition());
	}
	return path;
}

std::vector<glm::vec3> PathFinder::GeneratePathV2(glm::vec3 start, glm::vec3 end)
{
	PathNode* startNode = PathFindingManager::Instance().ClosestNodeAt(start.x, start.y, start.z);
	PathNode* endNode = PathFindingManager::Instance().ClosestNodeAt(end.x, end.y, end.z);
	startNode->distanceFromPrevious = startNode->distanceFromTarget = startNode->fvalue = 0;
	endNode->distanceFromPrevious = endNode->distanceFromTarget = endNode->fvalue = 0;

	// Initialize both open and closed list
	std::vector<PathNode*> open;
	std::vector<PathNode*> closed;

	// Add the start node
	open.push_back(startNode);

	// Loop until you find the end
	while (open.size() > 0)
	{
		// Get the current node
		PathNode* currentNode = open.at(0);
		unsigned currentIndex = 0;

		for (unsigned i = 0; i < open.size(); i++)
		{
			if (open.at(i)->fvalue < currentNode->fvalue)
			{
				currentNode = open.at(i);
				currentIndex = i;
			}
		}
		// Pop current off open list, add to closed list
		open.erase(std::begin(open) + currentIndex);
		closed.push_back(currentNode);

		// Found the goal
		if (currentNode == endNode)
		{
			std::vector<glm::vec3> path;
			PathNode* current = currentNode;
			while (current != nullptr)
			{
				path.push_back(current->transform.GetPosition());
				current = current->parentNode;
				std::reverse(std::begin(path), std::end(path));
				return path;
			}
		}

		// Loop through children
		for (unsigned i = 0; i < currentNode->neighbors.size(); i++)
		{

			// Child is on the closed list
			for (unsigned j = 0; j < closed.size(); j++)
			{
				if (currentNode->neighbors[i] == closed.at(j))
					continue;
			}

			// Create the f, g, and h values
			currentNode->neighbors[i]->distanceFromPrevious = currentNode->distanceFromPrevious + glm::length(currentNode->transform.GetPosition() - currentNode->neighbors[i]->transform.GetPosition());
			currentNode->neighbors[i]->distanceFromTarget = glm::length(endNode->transform.GetPosition() - currentNode->neighbors[i]->transform.GetPosition());
			currentNode->neighbors[i]->fvalue = currentNode->neighbors[i]->distanceFromPrevious + currentNode->neighbors[i]->distanceFromTarget + currentNode->neighbors[i]->cost;

			// Child is already in the open list
			for (unsigned j = 0; j < open.size(); j++)
			{
				if (currentNode->neighbors[i] == open.at(j) && currentNode->neighbors[i]->distanceFromPrevious > open.at(j)->distanceFromPrevious)
					continue;
			}

			// Add the child to the open list
			open.push_back(currentNode->neighbors[i]);
		}
	}
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
