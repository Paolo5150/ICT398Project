#pragma once
/**
* @class UniformBuffer
* @brief Generic uniform buffer object class
*
* Used to bind common data among different shaders
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class UniformBuffer
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
	UniformBuffer(unsigned totalSize, unsigned binding){};

	/**
	* @brief				Destroy uniform buffer object
	*
	* @pre					The uniform buffer object must exist
	* @post					The uniform buffer object is destroyed
	*/
	virtual ~UniformBuffer(){};

	/**
	* @brief				ACtivate the uniform buffer object
	*
	* @pre					The uniform buffer object must exist
	* @post					The uniform buffer object is activated
	*/
	virtual void Bind() = 0;

	/**
	* @brief				Deactivate the uniform buffer object
	*
	* @pre					The uniform buffer object must exist
	* @post					The uniform buffer object is Deactivated
	*/
	virtual void Unbind() = 0;

	/**
	* @brief				Add data to the buffer
	*
	* @pre					The uniform buffer object must exist
	* @post					The uniform buffer object is loaded with the data
	*/
	virtual void AddDataRange(unsigned stride, unsigned dataSize, const void* data) = 0;


protected:
	/**
	* @brief				The buffer id
	*/
	unsigned m_id;

	/**
	* @brief				The binding id, must be equal in the shadaer that uses this buffer
	*/
	unsigned m_bindingId;
};