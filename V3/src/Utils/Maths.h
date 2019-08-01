#pragma once
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/projection.hpp>

#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "imgui.h"
//#include "..\GUI\imgui_impl_glfw.h"
//#include "..\GUI\imgui_impl_opengl3.h"

/**
* @class Maths
* @brief Helper class fo maths related functions
*
*
* @author Paolo Ferri
* @version 01
* @date 05/03/2019
*
*
* @bug No known bugs.
*/
class Maths
{

public:
	/**
	* @brief						Convert a vec3 to printable form
	* @pre							The vector 3 exist
	* @post							The string with values of the vector is returned, the vector is unchanged
	* @param v						The vector 3
	* @return						A string with the vec3 values
	*/
	static std::string Vec3ToString(glm::vec3& v);
	/**
	* @brief						Convert a vec2 to printable form
	* @pre							The vector 2 exist
	* @post							The string with values of the vector is returned, the vector is unchanged
	* @param v						The vector 2
	* @return						A string with the vec3 values
	*/
	static std::string Vec2ToString(glm::vec2& v);
	/**
	* @brief						Convert a assimp 3x3 matrix to a glm 3x3 matrix
	* @pre							The matrix exist
	* @post							The glm matrix is returned, the assimp matrix is unchanged
	* @param from					The assimp matrix
	* @return						A glm matrix type
	*/
	static glm::mat3 aiMatrix3x3ToGlm(const aiMatrix3x3 &from);
	/**
	* @brief						Convert a assimp 4x4 matrix to a glm 4x4 matrix
	* @pre							The matrix exist
	* @post							The glm matrix is returned, the assimp matrix is unchanged
	* @param from					The assimp matrix
	* @return						A glm matrix type
	*/
	static glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4 &from);
	/**
	* @brief						Convert a assimp vector3 to a glm vec3
	* @pre							The vector exist
	* @post							The glm vector is returned, the assimp vector is unchanged
	* @param from					The assimp vector
	* @return						A glm vector type
	*/
	static glm::vec3 aiVector3ToGlm(const aiVector3D &from);
	/**
	* @brief						Convert a assimp quaternion to a glm quaternion
	* @pre							The quaternion exist
	* @post							The glm quaternion is returned, the assimp quaternion is unchanged
	* @param from					The assimp quaternion
	* @return						A glm quaternion type
	*/
	static glm::quat aiQuaternionToGlm(const aiQuaternion &from);

	/**
	* @brief						Interpolation for glm quaternions
	* @pre							The quaternions exist
	* @post							The interpolated value is returned
	* @param a						The quaternion to interpolate from
	* @param b						The quaternion to interpolate to
	* @param blend					The interpolation amount
	* @return						The interpolated value between a and b
	*/
	static glm::quat nlerp(glm::quat a, glm::quat b, float blend);
	/**
	* @brief						Convert a glm vec2 to a ImGui vec2
	* @pre							The vector exist
	* @post							The ImGui vector is returned, the glm vector is unchanged
	* @param v						The glm vector
	* @return						A ImGui vector type
	*/
	//static ImVec2 vec2ToImVec2(const glm::vec2& v);

	/**
	* @brief						Convert a glm vec4 to a ImGui vec4
	* @pre							The vector exist
	* @post							The ImGui vector is returned, the glm vector is unchanged
	* @param v						The glm vector
	* @return						A ImGui vector type
	*/
	//static ImVec4 vec4ToImVec4(const glm::vec4& v);




};