#pragma once
#include "..\Rendering\GridMesh.h"
#include "..\Core\GameObject.h"
#include "..\Components\MeshRenderer.h"

/**
* @class Terrain
* @brief Premade gameobject for a terrain
*
*
* @author Paolo Ferri
* @version 01
* @date 05/03/2019
*
*
* @bug No known bugs.
*/
class Terrain : public GameObject
{
public:

	/**
* @brief		Create a new terrain of specified size
*
* @post			The terrain object is created with the specified parameters
*
* @param		size		The size (width and depth) of the terrain
*/
	Terrain(int size);

	void Initialize(int size);
	/**
	* @brief		Destroy the terrain object
	* @pre			The terrain object must exist
	* @post			The terrain object is destroyed
	*/
	~Terrain() {};

	/**
	* @brief		Callback called right before the Render method
	*
	* @pre			The render method has not been called
	* @post			The method is called before Render
	*
	* @param cam	The camera used to render the object
	* @param currentShader	The shader used to render the object
	*/
	void OnPreRender(Camera& cam, Shader* s);

	/**
	* @brief		Callback called right after the Render method
	*
	* @pre			The render method has been called
	* @post			The method is called after Render
	*
	* @param cam	The camera used to render the object
	* @param currentShader	The shader used to render the object
	*/
	void OnPostRender(Camera& cam, Shader* s);

	/**
	* @brief		Get the center of the terrain in world space
	*
	* @pre			The terrain object must exist
	* @post			The center of the terrain is returned
	*
	* @param x		The x value of the center position
	* @param y		The y value of the center position
	* @param z		The z value of the center position
	*/
	void GetCenter(int& x, int& y, int& z);

	/**
	* @brief		Get the center of the terrain in world space
	*
	* @pre			The terrain object must exist
	* @post			The center of the terrain is returned
	*
	* @return vec3	A vec3 of the center position
	*/
	glm::vec3 GetCenter();

	/**
	* @brief		Returns the height of a point on a terrain in world space
	*
	* @pre			The terrain object must exist, the x and y provided are within the terrain boundaries
	* @post			The height of the terrain at point x z is returned
	*
	* @param x		The x value of the point position
	* @param z		The z value of the point position
	*/
	float GetHeightAt(int x, int z);


	float GetTerrainMaxX();
	float GetTerrainMinX();

	float GetTerrainMaxZ();
	float GetTerrainMinZ();



private:


	/**
	* @brief		Normaliz the terrain height
	*/
	void NormaliseTerrain(float* heightData, int dataWidth, int dataHeight);

	/**
	* @brief		Applies a filter to smooth the terrain out
	*/
	void AddFilter(float* heightData, float weight, int size);

	/**
	* @brief		Applies all filters to smooth the terrain out
	*/
	void FilterPass(float* dataP, int increment, float weight, int size);


	/**
	* @brief		The mesh renderer component
	*/
	MeshRenderer* meshRenderer;

	/**
	* @brief		The width and depth of the terrain
	*/
	int terrainSize;

	/**
	* @brief		Whether the wireframe will be rendererd
	*/
	bool isWireframe;

	std::unique_ptr<Mesh> gridMesh;

};
