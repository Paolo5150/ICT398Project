#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
* @class Vertex
* @brief Defines a vertex in a mesh
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class Vertex
{
public:

	/**
	* @brief				Create a new vertex
	*
	* @post					The vertex is created
	*/
	Vertex() {}

	/**
	* @brief				Create a new vertex and initialize position	*
	* @post					The vertex is created, the position is set
	* @param x				The x value of the position
	* @param y				The y value of the position
	* @param z				The z value of the position
	*/
	Vertex(float x, float y, float z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
	}

	/**
	* @brief				The vertex position
	*/
	glm::vec3 position;
	/**
	* @brief				The vertex normal vector
	*/
	glm::vec3 normal;
	/**
	* @brief				The vertex texture coordinates
	*/
	glm::vec2 UV;
	/**
	* @brief				The vertex color
	*/
	glm::vec3 color;
	/**
	* @brief				The vertex tangent vector
	*/
	glm::vec3 tangent;
	/**
	* @brief				The vertex binormal vector
	*/
	glm::vec3 binormal;

};