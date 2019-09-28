#include "pch.h"
#include "PathFindingManager.h"
#include "..\Prefabs\Terrain.h"
#include "..\Events\EventDispatcher.h"
#include "..\Events\ApplicationEvents.h"
#include <ctime>
#include <list>
#include <limits>
#include <float.h>
#include <thread>
#include <future>

PathFindingManager& PathFindingManager::Instance()
{
	static PathFindingManager instance;
	return instance;

}

PathFindingManager::PathFindingManager()
{
	nodesQT = nullptr;
	srand((unsigned)time(0));
	EventDispatcher::Instance().SubscribeCallback<SceneChangedEvent>([this](Event* e) {

		if (nodesQT != nullptr)
			nodesQT->ClearNodes();
		nodeMap.clear();
		pathNodes.clear();

		return 0;
	});
}

PathFindingManager::~PathFindingManager()
{

}

void PathFindingManager::DeleteNodes()
{
	pathNodes.clear();
}


PathNode* PathFindingManager::ClosestNodeAt(int x, int y, int z)
{
	std::unordered_set<PathNode*>& nodes = nodesQT->GameObjectsAt(x, z);

	double dist = 99999999999999999;
	PathNode* closest = nullptr;
	for (auto it = nodes.begin(); it != nodes.end(); it++)
	{
		double length = glm::length2((*it)->bc->transform.GetGlobalPosition() - glm::vec3(x, y, z));

		if (length < dist)
		{
			dist = length;
			closest = (*it);
		}

	}

	if (closest == nullptr)
		Logger::LogError("Cannot find closest");

	// Uncomment this to see the returned node
	//closest->bc->enableRender = 1;
	for (int i = 0; i < closest->neighbors.size(); i++)
	{
		//closest->neighbors[i]->bc->enableRender = 1;
		closest->neighbors[i]->bc->meshRenderer->GetMaterial().SetColor(1, 0, 1);

	}

	return closest;
}



void PathFindingManager::Generate(int centerX, int centerY, int sizeX, int sizeY, int heightt)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->centerX = centerX;
	this->centerY = centerY;

	int minX = centerX - sizeX / 2;
	int minY = centerY - sizeY / 2;

	int maxX = centerX + sizeX / 2;
	int maxY = centerY + sizeY / 2;

	int counterx = 0;
	for (int x = minX ; x < maxX ; x +=5)
	{
		std::vector<PathNode*> v;
		nodeMap.push_back(v);
		for (int z = minY ; z < maxY ; z += 5)
		{
			PathNode* pn = new PathNode();
			pn->transform.SetPosition(x, heightt, z);
			pathNodes.push_back(std::unique_ptr<PathNode>(pn));
			nodeMap[counterx].push_back(pn);

		}
		counterx++;

	}

	if (nodesQT == nullptr)
		nodesQT = std::unique_ptr<QuadTree<PathNode*>>(new QuadTree<PathNode*>(centerX, centerY, sizeX, sizeY, 20));

}
// Comment this out when releasing, not needed (used for rendering the nodes)
void PathFindingManager::EngineUpdate()
{
	for (unsigned i = 0; i < pathNodes.size(); i++)
	{
		pathNodes[i]->EngineUpdate();
	}
}
// Comment this out when releasing, not needed (used for rendering the nodes)
void PathFindingManager::Update()
{
	for (unsigned i = 0; i < pathNodes.size(); i++)
	{
		pathNodes[i]->Update();
	}
}


void PathFindingManager::Start()
{

	for (unsigned i = 0; i < pathNodes.size(); i++)
	{

		pathNodes[i]->Start();
		pathNodes[i]->bc->enableRender = 0;
		nodesQT->AddElement(pathNodes[i].get(), pathNodes[i]->bc->transform.GetGlobalPosition().x, pathNodes[i]->bc->transform.GetGlobalPosition().z, pathNodes[i]->bc->transform.GetGlobalScale().x, pathNodes[i]->bc->transform.GetGlobalScale().z);
	}

	int mapWidth = nodeMap.size();
	int mapHeight = nodeMap[0].size();

	for (int x = 0; x < nodeMap.size(); x++) {
		for (int y = 0; y < nodeMap[0].size(); y++) {


			if (x > 0) {
				nodeMap[x][y]->neighbors.push_back(nodeMap[x - 1][y]);

				//Diagonals

				if (y < mapHeight - 1) {
					nodeMap[x][y]->neighbors.push_back(nodeMap[x - 1][y + 1]);
				}

				if (y > 0) {
					nodeMap[x][y]->neighbors.push_back(nodeMap[x - 1][y - 1]);
				}
			}
			if (x < mapWidth - 1) {
				nodeMap[x][y]->neighbors.push_back(nodeMap[x + 1][y]);

				//Diagonals

				if (y < mapHeight - 1) {
					nodeMap[x][y]->neighbors.push_back(nodeMap[x + 1][y + 1]);
				}
				if (y > 0) {
					nodeMap[x][y]->neighbors.push_back(nodeMap[x + 1][y - 1]);
				}
			}
			if (y > 0) {
				nodeMap[x][y]->neighbors.push_back(nodeMap[x][y - 1]);
			}
			if (y < mapHeight - 1) {
				nodeMap[x][y]->neighbors.push_back(nodeMap[x][y + 1]);
			}
		}
	}

}


