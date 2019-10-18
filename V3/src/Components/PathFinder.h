#pragma once

#include "..\Core\Component.h"
#include "..\Physics\PathFindingManager.h"


/**
* @class PathFinder
* @brief PathFinder component for generating paths in the world
*
*
* Generates a path based on a start and end location,
* contains a vector of nodes in a path, once generated,
* and a locked end node to stop others generating a path to the same location
*
*
* @author Dylan Green
* @version 01
* @date 23/09/2019
*
*
* @bug No known bugs.
*/
class PathFinder : public Component
{
public:
//---- Public Member Functions ----//
	//-- Constructors --//
	/**
	* @brief		Creates a PathFinder object which contains a vector of PathNodes.
	*
	* @pre			The PathFinder object does not exist.
	* @post			The PathFinder object is created.
	*/
	PathFinder();

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-- Deconstructors --//
	/**
	* @brief		Destroys a PathFinder object.
	*
	* @pre			At least one PathFinder object must exist.
	* @post			The PathFinder object will no longer exist.
	*/
	~PathFinder();

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-- Pathfinding --//
	/**
	* @brief		Generates a path between the two given nodes, using A*, returns bool depending on success.
	*
	* @pre			The PathFinder must exist.
	* @post			A path is generated and stored.
	*
	* @param		start		location to start the pathfinding from
	* @param		end			location to end the pathfinding at
	*
	* @return		True if pathfinding was successful, false if no path could be found, or if the end node was locked.
	*/
	bool GeneratePath(glm::vec3 start, glm::vec3 end);

	/**
	* @brief		Returns the path as a vector of PathNodes.
	*
	* @pre			The PathFinder must exist.
	* @post			The Path will be returned as a vector of PathNodes.
	*
	* @return		A vector of PathNodes.
	*/
	std::vector<PathNode*> GetNodes() const;

	/**
	* @brief		Returns the path as a vector of 3d vectors.
	*
	* @pre			The PathFinder must exist.
	* @post			The Path will be returned as a vector of 3d vectors.
	*
	* @return		A vector of 3d vectors.
	*/
	std::vector<glm::vec3> GetPath() const;

	/**
	* @brief		Clears both the nodepath and the path
	*
	* @pre			The PathFinder must exist.
	* @post			The Path and NodePath will be empty.
	*/
	void ClearPath();

	/**
	* @brief		Returns true if nodePath.size() is greater than 0
	*
	* @pre			The PathFinder must exist.
	* @post			Whether the size of the nodePath is greater than 0.
	*
	* @return		True if nodePath.size() is greater than 0, false otherwise.
	*/
	bool HasPath();

	/**
	* @brief		Returns true if the parameter node is equal to the one at the end of the nodePath
	*
	* @pre			The PathFinder must exist.
	* @post			Whether the parameter node is the last node.
	*
	* @param		node		the node to check
	*
	* @return		True if the parameter node is the last node in the nodePath, false otherwise.
	*/
	bool IsLastNode(PathNode* node);

	/**
	* @brief		Returns true if the parameter position is equal to the one at the end of the path
	*
	* @pre			The PathFinder must exist.
	* @post			Whether the parameter node is the last node.
	*
	* @param		pos			the pos to check
	*
	* @return		True if the parameter node is the last node in the path, false otherwise.
	*/
	bool IsLastPos(glm::vec3 pos, bool includeY = false);

	/**
	* @brief		Returns the node position at index 0 in the path and optionally erases it from the nodePath, unless it is the last node left.
	*
	* @pre			The PathFinder must exist.
	* @post			A 3d vector will be returned with the next node's position.
	*
	* @param		erase		whether to erase the returned node from the nodePath and path, will not erase the final node
	*
	* @return		A 3d vector representing the next node postion.
	*/
	glm::vec3 GetNextNodePos(bool erase = true);

private:
	/**
	* @brief		Stores the path as a vector of nodes
	*/
	std::vector<PathNode*> nodePath;

	/**
	* @brief		Stores the path as a vector of 3d vectors
	*/
	std::vector<glm::vec3> path;

	/**
	* @brief		A locked end node, used to avoid multiple components pathfinding to the same place
	*/
	PathNode* lockedNode;

	/**
	* @brief		Unlocks and unassigns the currently locked node
	*
	* @pre			The PathFinder must exist.
	* @post			The Locked node will be unlocked if it is locked
	*/
	void UnlockEndNode();
};

