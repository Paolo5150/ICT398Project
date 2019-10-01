#pragma once

#include "..\Core\GameObject.h"
#include "..\Components\BoxCollider.h"
#include <vector>

/**
* @class PathNode
* @brief Class defining a node used for pathfinding
*
*
* @author Paolo Ferri
* @version 01
* @date 16/05/2019
* @bug No known bugs.
*/
class PathNode : public GameObject
{
public:
	/**
	* @brief		Constructor
	* @pre			The PathNode does not exist
	* @post			The PathNode is created
	*/
	PathNode();

	/**
	* @brief		Destructor
	* @pre			The PathNode must exist
	* @post			The PathNode is destroyed
	*/
	~PathNode();

	/**
	* @brief		Callback invoked when collision occurs
	* @pre			The PathNode must exist
	* @param go		The game object collided against
	*/
	void OnCollisionEnter(Collider* g, Collision& collision) override;

	/**
	* @brief		Initialize node
	* @pre			The PathNode must exist
	*/
	void Start() override;


	/**
	* @brief		Overridable method for engine update
	* @pre			The PathNode must exist
	*/
	void EngineUpdate() override;

	/**
	* @brief		Overridable method for late update
	* @pre			The PathNode must exist
	*/
	void LateUpdate() override;

	/**
	* @brief		The node collider
	*/
	BoxCollider* bc;

	/**
	* @brief		The list of nodes neighbors
	*/
	std::vector<PathNode*> neighbors;

	/**
	* @brief		Parent node used for pathfinding
	*/
	PathNode* parentNode;

	/**
	* @brief		The distance from the previous closest node
	*/
	double distanceFromPrevious;

	/**
	* @brief		The distance from the destination
	*/
	double distanceFromTarget;

	/**
	* @brief		The sum of distanceFromPrevious, distanceFromTarget, and cost
	*/
	double totalCost;

	/**
	* @brief		Represents whether this node is currently used as the goal of a pathfinding component
	*/
	bool lock;

	/**
	* @brief		The traversal cost of the node
	*/
	double cost;

	/**
	* @brief		Whether the node has been checked
	*/
	bool checked;
};