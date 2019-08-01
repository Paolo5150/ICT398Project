#pragma once
#include "Shader.h"
#include "GL/glew.h"


/**
* @class ShaderGL
* @brief Specialized shader class for Opengl
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class ShaderGL : public Shader
{
public: 
	friend class API_Opengl;

	/**
	* @brief		Destroy the shader obhect
	* @post			The shader object is destroyed
	*/
	~ShaderGL();
	/**
	* @brief		ACtivate the shader
	* @pre			The shader must exist
	* @post			The shader object is destroyed
	*/
	void Bind();
	/**
	* @brief		Send boolean value to shader
	* @pre			The shader must exist
	* @post			The value is sent to the shader on the GPU
	* @param name	The uniform varialble name
	* @param value	The value to be sent
	*/
	virtual void SetBool(const std::string &name, bool value) const override;

	/**
	* @brief		Send int value to shader
	* @pre			The shader must exist
	* @post			The value is sent to the shader on the GPU
	* @param name	The uniform varialble name
	* @param value	The value to be sent
	*/
	virtual void SetInt(const std::string &name, int value) const override;

	/**
	* @brief		Send float value to shader
	* @pre			The shader must exist
	* @post			The value is sent to the shader on the GPU
	* @param name	The uniform varialble name
	* @param value	The value to be sent
	*/
	virtual void SetFloat(const std::string &name, float value) const override;

	/**
	* @brief		Send matrix 4x4 value to shader
	* @pre			The shader must exist
	* @post			The value is sent to the shader on the GPU
	* @param name	The uniform varialble name
	* @param value	The value to be sent
	*/
	virtual void SetMat4(const std::string &name, glm::mat4 value) const override;

	/**
	* @brief		Send vector3 value to shader
	* @pre			The shader must exist
	* @post			The value is sent to the shader on the GPU
	* @param name	The uniform varialble name
	* @param value	The value to be sent
	*/
	virtual void SetVec3(const std::string &name, glm::vec3 value) const override;

	/**
	* @brief		Send vector4 value to shader
	* @pre			The shader must exist
	* @post			The value is sent to the shader on the GPU
	* @param name	The uniform varialble name
	* @param value	The value to be sent
	*/
	virtual void SetVec4(const std::string &name, glm::vec4 value) const override;

private:
	/**
	* @brief		Create a new shader
	*
	* @pre			The graphics API object must exist
	* @post			A new shader is created
	* @param name	The name of the shader in storage
	* @param vertexSource	The vertex shader source code
	* @param fragmentSource	The fragment shader source code
	*/
	ShaderGL(std::string name, std::string vSource, std::string fSource);
	/**
	* @brief		Default constructor
	*
	* @pre			The graphics API object must exist
	* @post			A new shader is created
	*/
	ShaderGL(){}

	/**
	* @brief		Helper method used to compile shaders
	* @pre			The shader source is successfully loaded
	* @post			The shader is compiled
	* @param sid	The shader id
	* @param source	The shader source code
	* @param type	The shader type (vertex or fragment)
	*/
	bool CompileShader(unsigned int& sid, const char* source, GLenum type);





};

