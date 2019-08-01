#pragma once
#include <vector>

/**
* @class ArrayBuffer
* @brief Template class used to create buffers for the GPU
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
template <class T>
class ArrayBuffer
{
public:
	/**
	* @brief		Creates a new array buffer
	*
	* @post			The graphics array buffer is created
	*/
	ArrayBuffer(){};

	/**
	* @brief		Destroy a new array buffer, clear GPU memory
	*
	* @pre			The array buffer exists
	* @post			The graphics array buffer is destroyed
	*/
	virtual ~ArrayBuffer(){};

	/**
	* @brief		Bind the current array buffer
	*
	* @pre			The array buffer exists
	* @post			The array buffer is ready to be used
	*/
	virtual void Bind() = 0;
	/**
	* @brief		Add  data to the buffer
	*
	* @pre			The array buffer exists
	* @post			The data is added to the buffer
	* @param data	The data
	*/
	virtual void AddData(std::vector<T>& data) = 0;


	/**
	* @brief		The buffer id

	*/
	unsigned m_id;


};