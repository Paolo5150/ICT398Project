#pragma once
#include "..\pch.h"
#include "VertexArray.h"

/**
* @class VertexArrayGL
* @brief Specialized class for a vertex array for Opengl
* Used to point the GPU to the right array buffer
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class VertexArrayGL : public VertexArray
{
public:
	/**
	* @brief		Creates a new vertex array
	*
	* @post			The vertex array is created
	*/
	VertexArrayGL(){
		glGenVertexArrays(1, &m_id);
	};
	/**
	* @brief		Destroy the vertex array
	* @pre			The vertex array must exist
	* @post			The vertex array is created
	*/
	~VertexArrayGL()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	/**
	* @brief		Activate the vertex array
	* @pre			The vertex array must exist
	* @post			The vertex array is activated
	*/
	void Bind()
	{
		glBindVertexArray(m_id);

	}
	/**
	* @brief		Deactivate the vertex array
	* @pre			The vertex array must exist
	* @post			The vertex array is deactivated
	*/
	void Unbind()
	{
		glBindVertexArray(0);
	}
	/**
	* @brief					Specify layout for a vertex buffer
	* @pre						The vertex array must exist, the vertex buffer exists and it's active
	* @param id					The layout id
	* @param numOfElements		The number of elements in the layout element
	* @param normalized			Whether the data should be normalized
	* @param size				The total size of the buffer
	* @param data				The data from the array buffer
	*/
	void AddLayoutf(unsigned id, unsigned numOfElements, bool normalized, unsigned size, void* data)
	{
		glEnableVertexAttribArray(id);
		glVertexAttribPointer(id, numOfElements, GL_FLOAT, normalized, size, data);
	}
	/**
	* @brief					Render the vertex array in triangles
	* @pre						The vertex array must exist and activated
	* @post						The vertices in the array are rendered
	* @param size				The numbr of triangles
	*/
	void RenderArrayTriangles(unsigned size)
	{
		glBindVertexArray(m_id);
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
	}
	/**
	* @brief					Render the vertex array as points in a line
	* @pre						The vertex array must exist and activated
	* @post						The vertices in the array are rendered
	* @param size				The numbr of triangles
	*/
	virtual void RenderArrayLines(unsigned size)
	{
		glBindVertexArray(m_id);
		glDrawArrays(GL_LINE_STRIP, 0,size );
	}


protected:
	unsigned m_id;

};