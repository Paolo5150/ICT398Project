#pragma once


#include "..\Utils\Quadtree.h"
#include <list>

class Collider;
/**
* @class PhysicsWorld
* @brief Singleto class that manages collisions
*
*
* @author Paolo Ferri
* @version 01
* @date 1/05/2019
*
*
* @bug No known bugs.
*/
class PhysicsWorld
{

public:
	/**
	* @brief						Return the PhysicsWorld instance
	*
	* @pre							The PhysicsWorld object must exist
	* @post							The PhysicsWorld instance is returned
	*/
	static PhysicsWorld& Instance();
	PhysicsWorld();

	/**
	* @brief						Destroy the object, clear all containers and quadtrees
	*
	* @pre							The PhysicsWorld object must exist
	*/
	~PhysicsWorld();

	/**
	* @brief						Update collisions
	*
	* @pre							The PhysicsWorld object must exist
	*/
	void Update();

	/**
	* @brief						Add collider to list
	*
	* @pre							The PhysicsWorld object must exist, the collider must exist
	* @post							The collider is added
	* @param c						The collider to be added
	*/
	void AddCollider(Collider* c);

	/**
	* @brief						Initialize quadtrees
	*
	* @post							The quadtrees are initialized according to dimensions gives
	* @param x						The x position
	* @param y						The y position
	* @param w						The width
	* @param z						The height
	*/
	void InitializeQuadtree(int x, int y, int w, int h);

	/**
	* @brief						Fill quadtrees with colliders
	* @pre							The quadtrees are initialized
	* @post							The qudtrees are filled in with colliders
	* @param staticToo				Whether the quadtrees of static colliders should be filled in
	*/
	void FillQuadtree(bool staticToo);
	
	/**
	* @brief						The non static colliders
	*/
	std::vector<Collider*> allNonStaticColliders;


	/**
	* @brief						The static colliders
	*/
	std::vector<Collider*> allStaticColliders;


	/**
	* @brief						The non static colliders quadtree
	*/
	std::unique_ptr<QuadTree<Collider*>> nonStaticQuadtree;

	/**
	* @brief						The static colliders quadtree
	*/
	std::unique_ptr<QuadTree<Collider*>> staticQuadtree;

	/**
	* @brief						Public method to initialize collision betection
	* @param staticToo				Whether collision detection should be performed betweem static objects
	*/
	void PerformCollisions(bool staticToo);
private:
	/**
	* @brief						Recurdive method that performs collision detection in a quadtree node
	* @param node					The current quadtree node
	*/
	void PerformCollisions(QuadNode<Collider*>* node);
};