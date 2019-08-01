#pragma once

/**
* @class VertexArray
* @brief Generic class for a vertex array
* Used to point the GPU to the right array buffer
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class VertexArray
{
public:
	/**
	* @brief		Creates a new vertex array
	*
	* @post			The vertex array is created
	*/
	VertexArray(){};

	/**
	* @brief		Destroy the vertex array
	* @pre			The vertex array must exist
	* @post			The vertex array is created
	*/
	virtual ~VertexArray(){};

	/**
	* @brief		Activate the vertex array
	* @pre			The vertex array must exist
	* @post			The vertex array is activated
	*/
	virtual void Bind() = 0;

	/**
	* @brief		Deactivate the vertex array
	* @pre			The vertex array must exist
	* @post			The vertex array is deactivated
	*/
	virtual void Unbind() = 0;

	/**
	* @brief					Specify layout for a vertex buffer
	* @pre						The vertex array must exist, the vertex buffer exists and it's active
	* @param id					The layout id
	* @param numOfElements		The number of elements in the layout element
	* @param normalized			Whether the data should be normalized
	* @param size				The total size of the buffer
	* @param data				The data from the array buffer
	*/
	virtual void AddLayoutf(unsigned id, unsigned numOfElements, bool normalized, unsigned size, void* data) = 0;

	/**
	* @brief					Render the vertex array in triangles
	* @pre						The vertex array must exist and activated
	* @post						The vertices in the array are rendered
	* @param size				The numbr of triangles
	*/
	virtual void RenderArrayTriangles(unsigned size) = 0;

	/**
	* @brief					Render the vertex array as points in a line
	* @pre						The vertex array must exist and activated
	* @post						The vertices in the array are rendered
	* @param size				The numbr of triangles
	*/
	virtual void RenderArrayLines(unsigned size) = 0;


protected:
	/**
	* @brief					The id of the verteex array
	*/
	unsigned m_id;

};