#pragma once

#include <vector>
#include "Vertex.h"
#include "..\Core\Logger.h"
#include "..\Rendering\ArrayBuffer.h"
#include "..\Rendering\VertexArray.h"
#include "..\Core\Camera.h"



#define NUM_BONES_PER_VEREX 4


// Used for skeletal animation
struct VertexBoneData
{
	unsigned ids[NUM_BONES_PER_VEREX];   // we have 4 bone ids for EACH vertex & 4 weights for EACH vertex
	float weights[NUM_BONES_PER_VEREX];
	int added;
	VertexBoneData()
	{
		added = 0;
		memset(ids, 0, sizeof(ids));    // init all values in array = 0
		memset(weights, 0, sizeof(weights));
	}

	void addBoneData(unsigned bone_id, float weight);
};


/**
* @class Mesh
* @brief Describe a mesh object by vertices and indices
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class Mesh : public Asset
{
public:
	/**
	* @brief		Creates the mesh object
	* @post			The mesh is created
	*/
	Mesh() {}

	/**
	* @brief		Creates the mesh object
	* @post			The mesh is created
	* @param vs		The mesh vertices
	* @param indices		The mesh indices
	* @param calculateNormals		Whether the mesh should calculate the normal of its vertices
	*/
	Mesh(std::vector<Vertex> vs, std::vector<unsigned> indices, bool calculateNormals = false);

	/**
	* @brief		Destroy the mesh object
	* @pre			The mesh object exist
	* @post			The mesh is destroyed
	*/
	virtual ~Mesh();

	/**
	* @brief		The mesh vertices
	*/
	std::vector<Vertex> vertices;

	/**
	* @brief		The mesh indices
	*/
	std::vector<unsigned> indices;

	/**
	* @brief		Get the center of the mesh
	* @pre			The mesh object exists
	* @post			The mesh center is reteurned
	* @return		The center of the mesh
	*/
	glm::vec3 GetCenter();
	//std::vector<VertexBoneData> bones_id_weights_for_each_vertex;

	/**
	* @brief		Calculate the normal vector for each vertex
	* @pre			The mesh object exists
	* @post			The vertices normals are calculated
	*/
	void CalculateNormals();

	ArrayBuffer<Vertex>& GetVertexBuffer() { return *vertexBuffer; };


	void Render(Camera& cam);
	void Render();


	void RefreshVertexBuffer() { vertexBuffer->AddData(vertices); };
	void InitializeVertexArray();

	std::vector<VertexBoneData> bones_id_weights_for_each_vertex;
private:
	/**
	* @brief		The vertex buffer for the GPU
	*/
	std::unique_ptr<ArrayBuffer<Vertex>> vertexBuffer;


	/**
	* @brief		The indices buffer for the GPU
	*/
	std::unique_ptr<ArrayBuffer<unsigned>> indexBuffer;


	/**
	* @brief		The vertex array of array buffers
	*/
	std::unique_ptr<VertexArray> vertexArray;

	unsigned VBO_bones;

};
