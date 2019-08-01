#pragma once

#include "GL/glew.h"
#include "..\Utils\Asset.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.inl>
#include "..\Core\Logger.h"


/**
* @class Shader
* @brief Generic shader class
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class Shader  : public Asset
{
public:

	/**
	* @brief		Return the current active shader
	*/
	static Shader& GetCurrentShader()
	{
		return *m_currentShader;
	}

	/**
	* @brief		Destroy the shader obhect
	* @post			The shader object is destroyed
	*/
	virtual ~Shader(){

	};

	/**
	* @brief		ACtivate the shader 
	* @pre			The shader must exist
	* @post			The shader object is destroyed
	*/
	virtual void Bind() = 0;

	/**
	* @brief		Send boolean value to shader
	* @pre			The shader must exist
	* @post			The value is sent to the shader on the GPU
	* @param name	The uniform varialble name
	* @param value	The value to be sent
	*/
	virtual void SetBool(const std::string &name, bool value) const = 0;

	/**
	* @brief		Send int value to shader
	* @pre			The shader must exist
	* @post			The value is sent to the shader on the GPU
	* @param name	The uniform varialble name
	* @param value	The value to be sent
	*/
	virtual void SetInt(const std::string &name, int value) const = 0;

	/**
	* @brief		Send float value to shader
	* @pre			The shader must exist
	* @post			The value is sent to the shader on the GPU
	* @param name	The uniform varialble name
	* @param value	The value to be sent
	*/
	virtual void SetFloat(const std::string &name, float value) const = 0;

	/**
	* @brief		Send matrix 4x4 value to shader
	* @pre			The shader must exist
	* @post			The value is sent to the shader on the GPU
	* @param name	The uniform varialble name
	* @param value	The value to be sent
	*/
	virtual void SetMat4(const std::string &name, glm::mat4 value) const = 0;

	/**
	* @brief		Send vector3 value to shader
	* @pre			The shader must exist
	* @post			The value is sent to the shader on the GPU
	* @param name	The uniform varialble name
	* @param value	The value to be sent
	*/
	virtual void SetVec3(const std::string &name, glm::vec3 value) const = 0;

	/**
	* @brief		Send vector4 value to shader
	* @pre			The shader must exist
	* @post			The value is sent to the shader on the GPU
	* @param name	The uniform varialble name
	* @param value	The value to be sent
	*/
	virtual void SetVec4(const std::string &name, glm::vec4 value) const = 0;

	unsigned GetID() { return shaderID; }

protected :
	/**
	* @brief		Create a new shader
	*
	* @pre			The graphics API object must exist
	* @post			A new shader is created
	*/
	Shader(){}
	/**
	* @brief		Create a new shader
	*
	* @pre			The graphics API object must exist
	* @post			A new shader is created
	* @param vertexSource	The vertex shader source code
	* @param fragmentSource	The fragment shader source code
	*/
	Shader(std::string vertexSource, std::string fragSource){};

	/**
	* @brief The shader id
	*/
	unsigned shaderID;

	/**
	* @brief		Helper method used to compile shaders
	* @pre			The shader source is successfully loaded
	* @post			The shader is compiled
	* @param sid	The shader id
	* @param source	The shader source code
	* @param type	The shader type (vertex or fragment)
	*/
	bool CompileShader(unsigned int& sid, const char* source, GLenum type);

	/**
	*@brief The current active shader
	*/
	static Shader* m_currentShader;





};

