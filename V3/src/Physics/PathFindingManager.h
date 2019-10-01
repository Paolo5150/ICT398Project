#pragma once

#include "PathNode.h"
#include "..\Utils\Quadtree.h"
#include <vector>

/**
* @class PathFinder
* @brief Manages path finding on the terrain
*
* @author Paolo Ferri
* @version 01
* @date 15/05/2019
*
*
* @bug No known bugs.
*/
class PathFindingManager
{
public:
	/**
	* @brief						Return the PathFinder instance
	*
	* @pre							The PathFinder must exist
	* @post							The PathFinder instance is returned
	*/
	static PathFindingManager& Instance();

	/**
	* @brief						Generate the grapsh of nodes based on terrain size
	*
	* @pre							The PathFinder must exist
	* @post							The grapsh is created
	* @param terrain				The terrain
	*/
	void Generate(int centerX, int centerY, int sizeX, int sizeY, int height);

	/**
	* @brief						Destroy the instance and nodes
	*
	* @pre							The PathFinder must exist
	* @post							The PathFinder is destroyed
	*/
	~PathFindingManager();

	/**
	* @brief						Returns the closest node to the give position
	*
	* @pre							The PathFinder must exist
	* @post							The closest node to the give position is returned
	* @param x						The x position
	* @param y						The y position
	* @param z						The z position
	*/
	PathNode* ClosestNodeAt(int x, int y, int z);

	/**
	* @brief						Initialize the nodes
	*
	* @pre							The PathFinder must exist
	* @post							The nodes are initialized
	*/
	void Start();

	void DeleteNodes();

	/**
	* @brief						2D map of nodes
	*/
	std::vector<std::unique_ptr<PathNode>> pathNodes;

	void EngineUpdate();
	void Update();
	
private:
	/**
	* @brief						Create PathFinder object
	*/
	PathFindingManager();

	/**
	* @brief						Quadtree of nodes
	*/
	std::unique_ptr<QuadTree<PathNode*>> nodesQT;

	/**
	* @brief						The 2D map of nodes
	*/
	std::vector<std::vector<PathNode*>> nodeMap;


	int sizeX;
	int sizeY;
	int centerX;
	int centerY;
	
};