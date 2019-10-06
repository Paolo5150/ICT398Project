#pragma once

#include "..\Utils\Quadtree.h"
#include <list>
#include <map>

class Collider;
class Rigidbody;
/**
* @class PhysicsWorld
* @brief Singleto class that manages collisions
*
*
* @author Paolo Ferri, Drew Paridaens
* @version 01
* @version 02
* -Added Physics implementation methods
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

	/**
	* @brief						Gravity for physics
	*/
	static glm::vec3 gravity;
private:
	/**
	* @brief						Recurdive method that performs collision detection in a quadtree node
	* @param node					The current quadtree node
	*/
	void PerformCollisions(QuadNode<Collider*>* node);

	void CheckCollision(Collider* it, Collider* it2, Rigidbody* rb1, Rigidbody* rb2);

	/**
	* @brief						Applies dynamic physics formula to participating objects
	* @param col1					The first collider involved in the calculation
	* @param col2					The second collider involved in the calculation
	* @param collision				A reference to the collision that occurred
	*/
	void PhysicsCalculation(Collider* col1, Collider* col2, const Collision& collision, bool onlyRotation = 0);
	/**
	* @brief						Moves the transform by the given vel and angVel across time (for separating collided objects)
	* @param tf						The transform to move
	* @param vel					The velocity to move the object by
	* @param angVel					The angular velocity to move the object by
	*/
	void MoveTransform(Transform& tf, const glm::vec3& vel, const glm::vec3& angVel);
	/**
	* @brief						Zeros the objects velocity (for the objects that continue to collided after a physics update)
	* @param rb						A reference to the rigidbody to zero the velocity on
	* @param vel					The velocity to move the object by
	* @param angVel					The angular velocity to move the object by
	* @pre							The given rigidbody pointer is not nullptr
	*/
	void ZeroOutVelocity(Rigidbody* rb);

	std::map<GameObject*, std::map<GameObject*, std::list<Collider*>>> gameObjectCollisionMap;
	std::map<Collider*, std::list<Collider*>> collidersCollisionMap;

	std::map<Collider*, std::list<Collider*>> collidersCollisionMapPerFrame;

	bool WereGameObjectsColliding(GameObject* obj1, GameObject* obj2);
	bool WereCollidersColliding(Collider* obj1, Collider* obj2);
	bool WereCollidingThisFrame(Collider* c1, Collider* c2);


};