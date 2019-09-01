#pragma once
#include "..\Core\Component.h"
#include "..\Utils\Maths.h"
#include "..\Core\Timer.h"
#include "..\Physics\PhysicsWorld.h"

/**
* @class Rigidbody
* @brief Rigidbody component for managing velocity of a GameObject
*
*
* Contains a vector for global velocity and a vector for angular velocity
*
* @author Dylan Green
* @version 01
* @date 09/08/2019
*
*
* @bug No known bugs.
*/
class Rigidbody : public Component
{
public:
//---- Public Member Functions ----//
	//-- Constructors --//
	/**
	* @brief		Creates a Rigidbody object which contains a velocity and angular velocity vector
	*
	* @pre			The Rigidbody object does not exist
	* @post			The Rigidbody object is created with the specified parameters
	*/
	Rigidbody();

	/**
	* @brief		Creates a Rigidbody object which contains a velocity and angular velocity vector
	*
	* @pre			The Rigidbody object does not exist
	* @post			The Rigidbody object is created with the specified parameters
	*
	* @param		x		inital x velocity of the rigidbody
	* @param		y		inital y velocity of the rigidbody
	* @param		z		inital z velocity of the rigidbody
	* @param		relative	if true the inital velocity is relative to the rotation of the gameobject, false by default
	*/
	Rigidbody(float x, float y, float z, bool relative = false);

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-- Deconstructors --//
	/**
	* @brief		Destroys a Rigidbody object.
	*
	* @pre			At least one Rigidbody object must exist
	* @post			The Rigidbody object will no longer exist
	*/
	~Rigidbody();

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-- Velocity --//
	/**
	* @brief		Sets the velocity of the Rigidbody to the specified values.
	*
	* @pre			The Rigidbody must exist
	* @post			The Rigidbody object's velocity is set to the parameter values
	*
	* @param		x		velocity to set the rigidbody to along the x axis
	* @param		y		velocity to set the rigidbody to along the y axis
	* @param		z		velocity to set the rigidbody to along the z axis
	*/
	void SetVelocity(float x, float y, float z);

	/**
	* @brief		Sets the velocity of the Rigidbody to the specified vector.
	*
	* @pre			The Rigidbody must exist
	* @post			The Rigidbody object's velocity is set to the parameter value
	*
	* @param		velocityVector		velocity to set the rigidbody to
	*/
	void SetVelocity(glm::vec3 velocityVector);

	/**
	* @brief		Adds the specified velocity to the velocity of the Rigidbody.
	*
	* @pre			The Rigidbody must exist
	* @post			The parameter values are added to the Rigidbody object's velocity
	*
	* @param		x		velocity to add to the rigidbody along the x axis
	* @param		y		velocity to add to the rigidbody along the y axis
	* @param		z		velocity to add to the rigidbody along the z axis
	*/
	void AddVelocity(float x, float y, float z);

	/**
	* @brief		Adds the specified velocity to the velocity of the Rigidbody.
	*
	* @pre			The Rigidbody must exist
	* @post			The parameter value is added to the Rigidbody object's velocity
	*
	* @param		velocityVector		velocity to add to the rigidbody
	*/
	void AddVelocity(glm::vec3 velocityVector);

	/**
	* @brief		Adds the specified velocity to the velocity of the Rigidbody, relative to the direction of the gameobject.
	*
	* @pre			The Rigidbody must exist
	* @post			The parameter values are added to the Rigidbody object's velocity, relative to the direction of the gameobject
	*
	* @param		x		velocity to add to the rigidbody along the x axis, relative to the direction of the gameobject
	* @param		y		velocity to add to the rigidbody along the y axis, relative to the direction of the gameobject
	* @param		z		velocity to add to the rigidbody along the z axis, relative to the direction of the gameobject
	*/
	void AddRelativeVelocity(float x, float y, float z);

	/**
	* @brief		Adds the specified velocity to the velocity of the Rigidbody, relative to the direction of the gameobject.
	*
	* @pre			The Rigidbody must exist
	* @post			The parameter value is added to the Rigidbody object's velocity, relative to the direction of the gameobject
	*
	* @param		velocityVector		velocity to add to the rigidbody, relative to the direction of the gameobject
	*/
	void AddRelativeVelocity(glm::vec3 velocityVector);

	/**
	* @brief		Retrieves the velocity of the Rigidbody.
	*
	* @pre			The Rigidbody must exist.
	* @post			The velocity of the Rigidbody will be retrieved.
	*
	* @return		The velocity of the Rigidbody.
	*/
	glm::vec3 GetVelocity() const;

	/**
	* @brief		Enables/Disables the gameobject being affected by gravity, gravity value is stored in the PhysicsWorld file
	*
	* @pre			The Rigidbody must exist.
	* @post			Whether the Rigidbody is affected by gravity will be set.
	*
	* @param		useGravity		whether the Rigidbody should be affected by gravity
	*/
	void UseGravity(bool gravityEnabled);
	bool GetUseGravity();

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-- Angular Velocity --//
	/**
	* @brief		Sets the angular velocity of the Rigidbody to the specified values.
	*
	* @pre			The Rigidbody must exist
	* @post			The Rigidbody object's angular velocity is set to the parameter values
	*
	* @param		x		angular velocity to set the rigidbody to along the x axis
	* @param		y		angular velocity to set the rigidbody to along the y axis
	* @param		z		angular velocity to set the rigidbody to along the z axis
	*/
	void SetAngularVelocity(float x, float y, float z);

	/**
	* @brief		Sets the angular velocity of the Rigidbody to the specified vector.
	*
	* @pre			The Rigidbody must exist
	* @post			The Rigidbody object's angular velocity is set to the parameter value
	*
	* @param		angularVelocityVector		angular velocity to set the rigidbody to
	*/
	void SetAngularVelocity(glm::vec3 angularVelocityVector);

	/**
	* @brief		Adds the specified angular velocity to the angular velocity of the Rigidbody.
	*
	* @pre			The Rigidbody must exist
	* @post			The parameter values are added to the Rigidbody object's angular velocity
	*
	* @param		x		angular velocity to add to the rigidbody along the x axis
	* @param		y		angular velocity to add to the rigidbody along the y axis
	* @param		z		angular velocity to add to the rigidbody along the z axis
	*/
	void AddAngularVelocity(float angX, float angY, float angZ);

	/**
	* @brief		Adds the specified angular velocity to the angular velocity of the Rigidbody.
	*
	* @pre			The Rigidbody must exist
	* @post			The parameter value is added to the Rigidbody object's angular velocity
	*
	* @param		angularVelocityVector		angular velocity to add to the rigidbody
	*/
	void AddAngularVelocity(glm::vec3 angularVelocityVector);

	/**
	* @brief		Adds the specified angular velocity to the angular velocity of the Rigidbody, relative to the direction of the gameobject.
	*
	* @pre			The Rigidbody must exist
	* @post			The parameter values are added to the Rigidbody object's angular velocity, relative to the direction of the gameobject
	*
	* @param		x		angular velocity to add to the rigidbody along the x axis, relative to the direction of the gameobject
	* @param		y		angular velocity to add to the rigidbody along the y axis, relative to the direction of the gameobject
	* @param		z		angular velocity to add to the rigidbody along the z axis, relative to the direction of the gameobject
	*/
	void AddRelativeAngularVelocity(float angX, float angY, float angZ);

	/**
	* @brief		Adds the specified angular velocity to the angular velocity of the Rigidbody, relative to the direction of the gameobject.
	*
	* @pre			The Rigidbody must exist
	* @post			The parameter value is added to the Rigidbody object's angular velocity, relative to the direction of the gameobject
	*
	* @param		angularVelocityVector		angular velocity to add to the rigidbody, relative to the direction of the gameobject
	*/
	void AddRelativeAngularVelocity(glm::vec3 angularVelocityVector);

	/**
	* @brief		Retrieves the angular velocity of the Rigidbody.
	*
	* @pre			The Rigidbody must exist.
	* @post			The angular velocity of the Rigidbody will be retrieved.
	*
	* @return		The angular velocity of the Rigidbody.
	*/
	glm::vec3 GetAngularVelocity() const;

	/**
	* @brief		Overridden method for logic update
	*/
	void Update() override;

private:
	glm::vec3 velocity; //Velocity vector
	glm::vec3 angVelocity; //Angular velocity vector
	bool useGravity; //Whether to be affected by gravity
};