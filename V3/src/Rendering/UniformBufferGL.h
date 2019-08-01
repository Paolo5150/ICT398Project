#pragma once
#include "UniformBuffer.h"

/**
* @class UniformBufferGL
* @brief Specialized uniform buffer object class for Opengl
*
* Used to bind common data among different shaders
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class UniformBufferGL : public UniformBuffer
{
public:
	/**
	* @brief				Create a new uniform buffer object
	*
	* @pre					The graphics API object must exist
	* @post					A new uniform buffer object is created
	* @param totalSize		The size of the buffer
	* @param binding		The bingind index
	*/
	UniformBufferGL(unsigned totalSize, unsigned binding) ;

	/**
	* @brief				Destroy uniform buffer object
	*
	* @pre					The uniform buffer object must exist
	* @post					The uniform buffer object is destroyed
	*/
	~UniformBufferGL();

	/**
	* @brief				Add data to the buffer
	*
	* @pre					The uniform buffer object must exist
	* @post					The uniform buffer object is loaded with the data
	*/
	void AddDataRange(unsigned stride, unsigned dataSize, const void* datao) override;

	/**
	* @brief				ACtivate the uniform buffer object
	*
	* @pre					The uniform buffer object must exist
	* @post					The uniform buffer object is activated
	*/
	void Bind();

	/**
	* @brief				Deactivate the uniform buffer object
	*
	* @pre					The uniform buffer object must exist
	* @post					The uniform buffer object is Deactivated
	*/
	void Unbind();



};