#pragma once
#include "..\Utils\Maths.h"
#include <sstream>

class GameObject;

/**
* @class Transform
* @brief Manages movement, rotation and scaling of game objects in 3D space
*
* @author Paolo Ferri
* @version 01
* @date 11/03/2019
*
*
*
* @bug No known bugs.
*/
class Transform
{
public:

	/**
	* @brief The parent transform
	*/
	Transform* parent;


	std::list<Transform*> transformChildren;

	/**
	* @brief		Create the transform object
	*
	* @pre			The game object owning the transform exists
	* @post			The transform object is created
	*
	*/
	Transform();

	~Transform();

	/**
	* @brief		Return the position relative to parent
	*
	* @pre			The game object owning the transform exists
	* @post			The position of the game object is return and left unchanged
	*
	*/
	glm::vec3& GetPosition();

	/**
	* @brief		Return the scale relative to parent
	*
	* @pre			The game object owning the transform exists
	* @post			The scale of the game object is return and left unchanged
	*
	*/
	glm::vec3& GetScale();

	/**
	* @brief		Return the rotation relative to parent in euler angles
	*
	* @pre			The game object owning the transform exists
	* @post			The rotation of the game object is return and left unchanged
	*
	*/
	glm::vec3& GetRotation();

	/**
	* @brief		Return the object position in world space
	* @pre			The game object owning the transform exists
	* @post			The world position of the game object is return and left unchanged
	*
	*/
	glm::vec3& GetGlobalPosition();

	/**
	* @brief		Return the object scale in world space (used by child transform)
	*
	* @pre			The game object owning the transform exists
	* @post			The world scale of the game object is return and left unchanged
	*
	*/
	glm::vec3& GetGlobalScale();



	/**
	* @brief		Return the rotation position in world space
	* @pre			The game object owning the transform exists
	* @post			The world rotation of the game object is return and left unchanged
	*
	*/
	glm::mat4& GetGlobalRotation();



	/**
	* @brief		Return the rotation quaternion
	* @pre			The game object owning the transform exists
	* @post			The direction the object is facing of the game object is return and left unchanged
	*
	*/
	glm::quat& GetRotationQuat() { return rotationQuat; };

	/**
	* @brief		Return the direction the object is facing
	* @pre			The game object owning the transform exists
	* @post			The direction the object is facing of the game object is return and left unchanged
	*
	*/
	glm::vec3& GetLocalFront() { return localFront; };

	/**
	* @brief		Return the direction vector to the right of the object
	* @pre			The game object owning the transform exists
	* @post			The direction vector to the right of the object is return and left unchanged
	*
	*/
	glm::vec3& GetLocalRight() { return localRight; };

	/**
	* @brief		Return the upward vector of the object
	* @pre			The game object owning the transform exists
	* @post			The the upward vector of the game object is return and left unchanged
	*
	*/
	glm::vec3& GetLocalUp() { return localUp; };

	/**
	* @brief		Return the local to world matrix
	* @pre			The game object owning the transform exists
	* @post			The model matrix is returned and left unchanged
	*
	*/
	glm::mat4& GetMatrix();

	/**
	* @brief		Rotate object by certain angle in deg on a single axis
	* @pre			The game object owning the transform exists
	* @post			The object is rotated
	*
	* @param angle The angle in deg
	* @param axis	The axis the object will rotate on
	*/
	void RotateBy(float angle, glm::vec3 axis);

	/**
	* @brief		Rotate object by certain angle in deg on a single axis
	* @pre			The game object owning the transform exists
	* @post			The object is rotated
	*
	* @param angle The angle in deg
	* @param x	The x value of the axis the object will rotate on
	* @param y	The x value of the axis the object will rotate on
	* @param z	The x value of the axis the object will rotate on
	*/
	void RotateBy(float angle, int x, int y, int z);

	/**
	* @brief		Set the position of the object in world space
	* @pre			The game object owning the transform exists
	* @post			The object is positioned in the new location
	*
	* @param r		The position in world space
	*/
	void SetPosition(glm::vec3 r);

	/**
	* @brief		Set the scale of the object
	* @pre			The game object owning the transform exists
	* @post			The object is scaled
	*
	* @param r		The scale 
	*/
	void SetScale(glm::vec3 r);

	/**
* @brief		Set the scale of the object for all axis
* @pre			The game object owning the transform exists
* @post			The object is scaled
*
* @param r		The scale
*/
	void SetScale(float r);


	/**
	* @brief		Rotate the object to look at a point
	* @pre			The game object owning the transform exists
	* @post			The object is rotated
	*
	* @param target		The target point
	*/
	void LookAt(glm::vec3 target);

	/**
	* @brief		Set the rotation of the object
	* @pre			The game object owning the transform exists
	* @post			The object is rotated
	*
	* @param x		The x value of the rotation
	* @param y		The y value of the rotation
	* @param z		The z value of the rotation
	*/
	void SetRotation(float x, float y, float z);

	/**
* @brief		Set the rotation of the object
* @pre			The game object owning the transform exists
* @post			The object is rotated
*
* @param x		The x value of the rotation
* @param y		The y value of the rotation
* @param z		The z value of the rotation
*/
	void SetRotation(glm::vec3& rot);

	/**
	* @brief		Set the rotation of the object
	* @pre			The game object owning the transform exists
	* @post			The object is rotated
	*
	* @param x		The x value of the rotation
	* @param y		The y value of the rotation
	* @param z		The z value of the rotation
	*/
	void SetRotation(float x, float y, float z, float w);

	/**
	* @brief		Set the position of the object
	* @pre			The game object owning the transform exists
	* @post			The object is positioned at the new location
	*
	* @param x		The x value of the position
	* @param y		The y value of the position
	* @param z		The z value of the position
	*/
	void SetPosition(float x, float y, float z);

	/**
	* @brief		Set the scale of the object
	* @pre			The game object owning the transform exists
	* @post			The object is scaled 
	*
	* @param x		The x value of the scale
	* @param y		The y value of the scale
	* @param z		The z value of the scale
	*/
	void SetScale(float x, float y, float z);

	/**
	* @brief		Rotate the object to look at a point
	* @pre			The game object owning the transform exists
	* @post			The object is rotated
	*
	* @param x		The x value of the target position
	* @param y		The y value of the target position
	* @param z		The z value of the target position
	*/
	void LookAt(float x, float y, float z);

	/**
	* @brief		Translate the object by a ceertain amount
	* @pre			The game object owning the transform exists
	* @post			The object is translated
	*
	* @param x		The x value of the translation
	* @param y		The y value of the translation
	* @param z		The z value of the translation
	*/
	void Translate(float x, float y, float z);

	/**
* @brief		Translate the object by a ceertain amount
* @pre			The game object owning the transform exists
* @post			The object is translated
*
* @param x		The x value of the translation
* @param y		The y value of the translation
* @param z		The z value of the translation
*/
	void Translate(glm::vec3 v);

	void UpdateHierarchy(bool forceParent = 0);

	/**
	* @brief		Print position, scale and rotation
	* @pre			The game object owning the transform exists
	*/
	std::string ToString();

	/**
	* @brief		Print front vector, right vector and up vector
	* @pre			The game object owning the transform exists
	*/
	std::string VectorsToString();

	/**
	* @brief		Print front vector, right vector and up vector
	* @pre			The game object owning the transform exists
	*/
	std::string RotationQuatToString();

	void UpdateVectors();

	
	void SetIgnoreParentRotation(bool i) { ignoreParentRotation = i; }

private:
	/**
	* @brief		The position of the object
	*/
	glm::vec3 position;

	/**
	* @brief		The scale of the object
	*/
	glm::vec3 scale;

	/**
	* @brief		The rotation in euler angles of the object
	*/
	glm::vec3 rotation;

	/**
	* @brief		The rotation quaternion of the object
	*/
	glm::quat rotationQuat;

	/**
	* @brief		The front vector of the object
	*/
	glm::vec3 localFront;

	/**
	* @brief		The right vector of the object
	*/
	glm::vec3 localRight;

	/**
	* @brief		The up vector of the object
	*/
	glm::vec3 localUp;

	/**
	* @brief		The local to world matrix
	*/
	glm::mat4 modelMatrix;

	/**
	* @brief		The position in global space
	*/
	glm::vec3 globalPosition;

	/**
	* @brief		The scale in global space
	*/
	glm::vec3 globalScale;

	/**
	* @brief		The rotation matrix in global space
	*/
	glm::mat4 globalRotationMatrix;

	/**
	* @brief		The rotation matrix
	*/
	glm::mat4 rotationMatrix;

	/**
	* @brief		Create and return the translation matrix
	*/
	glm::mat4 GetTranslateMatrix();

	/**
	* @brief		Create and return the scale matrix
	*/
	glm::mat4 GetScaleMatrix();

	/**
	* @brief		Create and return the rotation matrix
	*/
	glm::mat4 GetRotationMatrix();

	bool ignoreParentRotation;
};