#pragma once
#include <string>
#include "ArrayBuffer.h"
#include "..\Core\Logger.h"


/**
* @class ArrayBufferGL
* @brief Template class used to create buffers for the GPU, specialized for Opengl 
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
template <class T>
class ArrayBufferGL : public ArrayBuffer<T>
{
public:

	/**
	* @brief		Creates a new array buffer
	*
	* @post			The graphics array buffer is created
	*/
	ArrayBufferGL();

	/**
	* @brief		Destroy a new array buffer, clear GPU memory
	*
	* @pre			The array buffer exists
	* @post			The graphics array buffer is destroyed
	*/
	~ArrayBufferGL();

	/**
	* @brief		Bind the current array buffer
	*
	* @pre			The array buffer exists
	* @post			The array buffer is ready to be used
	*/
	void Bind() override;

	/**
	* @brief		Add  data to the buffer
	*
	* @pre			The array buffer exists
	* @post			The data is added to the buffer
	* @param data	The data
	*/
	void AddData(std::vector<T>& data) override;

private:
	/**
	* @brief The buffer type
	*/
	unsigned bufferType;
	
	unsigned m_id;
};

template <class T>
ArrayBufferGL<T>::ArrayBufferGL()
{
	glGenBuffers(1, &m_id);
	//Ugly, but necessary
	std::string typeName = typeid(T).name();

	if (typeName == "unsigned int")
	{
		bufferType = GL_ELEMENT_ARRAY_BUFFER;
	}
	else
		bufferType = GL_ARRAY_BUFFER;
}

template <class T>
ArrayBufferGL<T>::~ArrayBufferGL()
{
	glDeleteBuffers(1, &m_id);
}

template <class T>
void ArrayBufferGL<T>::Bind()
{	
	glBindBuffer(bufferType, m_id);
}



template <class T>
void ArrayBufferGL<T>::AddData(std::vector<T>& data)
{
	Bind();
	glBufferData(bufferType, data.size() * sizeof(data[0]), &data[0], GL_STATIC_DRAW);
}