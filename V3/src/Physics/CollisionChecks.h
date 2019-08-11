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
* @author Drew Paridaens
* @version 02
* -Modified to calculate collision point
* @date 11/08/2019
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

	/**
	* @brief Generic method for getting the point of collision between 2 colliders
	* @pre  The colliders must exists
	* @pre A collision must have occurred
	* @post Collision point is calculated
	* @param s	The first collider
	* @param b	The second collider
	* @return The world space point of collision, or as close as possible
	*/
	static glm::vec3 getCollisionPoint(Collider* s, Collider* b);

	/**
	* @brief Generic method for getting the point of collision between box and box colliders
	* @pre  The colliders must exists
	* @pre A collision must have occurred
	* @post Collision point is calculated
	* @param s	The box collider
	* @param b	The box collider
	* @return The world space point of collision, or as close as possible
	*/
	static glm::vec3 getCollisionPoint(BoxCollider* s, BoxCollider* b);

	/**
	* @brief Generic method for getting the point of collision between sphere and box colliders
	* @pre  The colliders must exists
	* @pre A collision must have occurred
	* @post Collision point is calculated
	* @param s	The sphere collider
	* @param b	The box collider
	* @return The world space point of collision, or as close as possible
	*/
	static glm::vec3 getCollisionPoint(SphereCollider* s, BoxCollider* b);

	/**
	* @brief Generic method for getting the point of collision between sphere and sphere colliders
	* @pre  The colliders must exists
	* @pre A collision must have occurred
	* @post Collision point is calculated
	* @param s	The sphere collider
	* @param b	The sphere collider
	* @return The world space point of collision, or as close as possible
	*/
	static glm::vec3 getCollisionPoint(SphereCollider* s, SphereCollider* b);

private:
	/**
	* @brief Helper method for determining if the given point exists within the bounds of the box collider
	* @pre  The collider must exists
	* @post Whether the point exists within the boxes bounds is evaluated
	* @param point The point to check
	* @param box The box collider
	* @return true if the point does exist within the boxes bounding space
	*/
	static bool isPointInBox(glm::vec3 point, BoxCollider* box);

	/**
	* @brief Helper method for getting the closest point that exists in the boxes bound to the given point
	* @pre  The collider must exists
	* @post Closest single vector 3 point within box space to given point is calculated
	* @param point The point to check against
	* @param box The box collider
	* @return The position of the closest point in box space to the given point
	*/
	static glm::vec3 getClosestPointToBox(glm::vec3 point, BoxCollider* box);
};