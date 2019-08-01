#pragma once
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <string>
#include <vector>

/**
* @class ModelNode
* @brief Describe a joint in an animated model
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class ModelNode
{

public:
	std::string name;
	glm::mat4 transform;
	std::vector<ModelNode*> children;
};

/**
* @class TranslateKey
* @brief Describe an animation bone translation
*
* @author Paolo Ferri
* @version 01
* @date 28/04/2019
* @bug No known bugs.
*/
class TranslateKey
{
public:

	/**
	* @brief		Constructor
	* @ param t		The translation time (for interpolation)
	* @ param v		The translation position
	*/
	TranslateKey(double t, glm::vec3 v) : time(t), value(v) {}
	double time;
	glm::vec3 value;
};

/**
* @class ScaleKey
* @brief Describe an animation bone scale
*
* @author Paolo Ferri
* @version 01
* @date 28/04/2019
* @bug No known bugs.
*/
class ScaleKey
{
public:
	/**
	* @brief		Constructor
	* @ param t		The scale time (for interpolation)
	* @ param v		The scale position
	*/
	ScaleKey(double t, glm::vec3 v) : time(t), value(v) {}
	double time;
	glm::vec3 value;
};

/**
* @class RotationKey
* @brief Describe a rotation bone scale
*
* @author Paolo Ferri
* @version 01
* @date 28/04/2019
* @bug No known bugs.
*/
class RotationKey
{
public:
	/**
	* @brief		Constructor
	* @ param t		The rotation time (for interpolation)
	* @ param v		The rotation position
	*/
	RotationKey(double t, glm::quat v) : time(t), value(v) {}
	double time;
	glm::quat value;
};

/**
* @class ModelNodeAnimationInfo
* @brief Animation information(translation, scale, rotation) for a node.
*
* @author Paolo Ferri
* @version 01
* @date 28/04/2019
* @bug No known bugs.
*/
class ModelNodeAnimationInfo
{

public:
	/**
	* @brief Reference to the node.
	*/
	ModelNode* actualNode;

	/**
	* @brief All translations
	*/
	std::vector<TranslateKey> translateKeys;

	/**
	* @brief All scales
	*/
	std::vector<ScaleKey> scaleKeys;

	/**
	* @brief All rotations
	*/
	std::vector<RotationKey> rotationKey;
};


/**
* @class ModelBone
* @brief Animation bone
*
* @author Paolo Ferri
* @version 01
* @date 28/04/2019
* @bug No known bugs.
*/
class ModelBone {

public:
	glm::mat4 offsetMatrix;

	unsigned int index;
};

