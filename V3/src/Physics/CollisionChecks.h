#pragma once

class BoxCollider;
class SphereCollider;
class Collider;

/**
* @class CollisionChecks
* @briefCollections of methods for collision detection
*
*
* @author Paolo Ferri
* @version 01
* @date 21/04/2019
*
*
* @bug No known bugs.
*/
class CollisionChecks
{
public:
	/**
	* @brief Generic method for collision between 2 colliders
	* @pre  The colliders must exists
	* @post Collision is checked between colliders
	* @param s	The first collider
	* @param b	The second collider
	* @return true if there's collision between the 2 colliders
	*/
	static bool Collision(Collider* s, Collider* b);

	/**
	* @brief Generic method for collision between sphere and box colliders
	* @pre  The colliders must exists
	* @post Collision is checked between colliders
	* @param s	The sphere collider
	* @param b	The box collider
	* @return true if there's collision between the 2 colliders
	*/
	static bool Collision(SphereCollider* s, BoxCollider* b);

	/**
	* @brief Generic method for collision between sphere and sphere colliders
	* @pre  The colliders must exists
	* @post Collision is checked between colliders
	* @param s	The sphere collider
	* @param b	The sphere collider
	* @return true if there's collision between the 2 colliders
	*/
	static bool Collision(SphereCollider* s, SphereCollider* b);


	/**
	* @brief Generic method for collision between box and box colliders
	* @pre  The colliders must exists
	* @post Collision is checked between colliders
	* @param s	The box collider
	* @param b	The box collider
	* @return true if there's collision between the 2 colliders
	*/
	static bool Collision(BoxCollider* s, BoxCollider* b);

	/**
	* @brief Helpler method to detect OBB collision
	* @pre  The colliders must exists
	* @post Collision is checked between colliders
	* @param pos	The plane position
	* @param Plane The plane normal
	* @param box1 The first box collider
	* @param box2 The second box collider
	*/
	static bool getSeparatingPlane(glm::vec3 pos, glm::vec3 Plane, BoxCollider* box1, BoxCollider* box2);


	/**
	* @brief Helpler method to detect OBB collision
	* @pre  The colliders must exists
	* @post Collision is checked between colliders
	* @param box1 The first box collider
	* @param box2 The second box collider
	*/
	static bool getCollision(BoxCollider* box1, BoxCollider* box2);


};