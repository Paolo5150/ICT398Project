#pragma once
#include "CubeMap.h"
#include "EquirectangularMap.h"
#include "Material.h"
#include "Mesh.h"
#include "..\Components\MeshRenderer.h"
#include "Layers.h"

/**
* @class Skybox
* @brief Defines a skybox in a scene using cubemap
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class Skybox
{
public:
	/**
	* @brief		Create new skybox
	* @pre			The cubemap must be valid
	* @post			The skybix is created
	* @param cubemap	The cubemap of the skybox
	*/
	Skybox(CubeMap* cubemap);

	/**
* @brief		Create new skybox
* @pre			The cubemap must be valid
* @post			The skybix is created
* @param cubemap	The cubemap of the skybox
*/
	Skybox(EquirectangularMap* cubemap);

	/**
	* @brief		Destroy skybox
	* @pre			The skybox exists
	* @post			The skybox is destroyed
	*/
	~Skybox();

	/**
	* @brief		The skybox material
	*/
	Material material;

	/**
	* @brief		The skybox mesh renderer
	*/
	MeshRenderer* meshRenderer;

	std::unique_ptr<GameObject> dummy;
	/**
	* @brief		The skybox layer mask
	*/
	int layer;

	/**
	* @brief		The skybox engine update override
	*/
	void EngineUpdate();

	/**
	* @brief		Return the skybox cubemap
	* @pre		The skybox exists
	* @post The cubemap is returned
	* @return	The skybox cubemap
	*/
	CubeMap& GetCubeMap(){ return *cubemap; }

private:
	/**
	* @brief		The skybox cubemap
	*/
	CubeMap* cubemap;


	/**
	* @brief		Callback called right before the Render method
	*
	* @pre			The render mmethod has been called
	* @post			The method is called before Render
	*
	* @param cam	The camera used to render the object
	* @param currentShader	The shader used to render the object
	*/
	void OnPreRender(Camera& cam, Shader* s);

	/**
	* @brief		Callback called right after the Render method
	*
	* @pre			The render mmethod has been called
	* @post			The method is called after Render
	*
	* @param cam	The camera used to render the object
	* @param currentShader	The shader used to render the object
	*/
	void OnPostRender(Camera& cam, Shader* s);


};
