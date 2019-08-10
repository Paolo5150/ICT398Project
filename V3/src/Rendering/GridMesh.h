#pragma once
#include "Mesh.h"

/**
* @class GridMesh
* @brief Programmatically created grid mesh
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class GridMesh : public Mesh
{
public:
	/**
	* @brief					Create a new grid mesh of specified size
	*
	* @post						The grid mesh is created
	* @param widthVertes		The number of verties on the width
	* @param depthVerts			The number of verties on the depth
	*/
	GridMesh(int widthVertes, int depthVerts);

	/**
	* @brief					Destroy the grid mesh objects
	* @pre						The grid mesh must exist
	* @post						The grid mesh is destroyed
	*/
	~GridMesh();

	/**
	* @brief					Returns the width of the grid
	* @pre						The grid mesh must exist
	* @post						The width of the grid is returned
	* @return					The width of the grid
	*/
	int GetSizeX() { return sizeX; };

	/**
	* @brief					Returns the depth of the grid
	* @pre						The grid mesh must exist
	* @post						The depth of the grid is returned
	* @return					The depth of the grid
	*/
	int GetSizeZ() { return sizeZ; };

	/**
	* @brief					The width of the grid
	*/
	int sizeX;

	/**
	* @brief					The depth of the grid
	*/
	int sizeZ;

private:
	/**
	* @brief					Initialize the mesh load vertices to the GPU
	* @pre						The grid mesh must exist
	* @post						The mesh is loaded to the GPU
	*/
	void Initialize();

};
