#pragma once
#include "SOIL/SOIL.h"
#include "SOIL/stb_image_aug.h"
#include "..\Core\Logger.h"
#include "..\Utils\Asset.h"
#include "GL/glew.h"

/**
* @class Texture2DGL
* @brief Specialized texture class for Opengl
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class EquirectangularMap : public Asset
{
public:
	friend class API_Opengl;

	/**
* @brief				Default constructor
*
* @pre					The graphics API object must exist
* @post					A new Texture2D is created with no data

*/
	EquirectangularMap() {}

	unsigned GetID() { return id; }

	/**
	* @brief		Activate texture
	* @pre			The texture objecct must exist
	* @post			The texture is activated
	*/
	void Bind();

	/**
	* @brief		Destroy texture, unload from GPU
	* @pre			The texture objecct must exist
	* @post			The texture is destroyed
	*/
	~EquirectangularMap();


	/**
	* @brief		Create a new Texture2D
	*
	* @pre					The graphics API object must exist
	* @post					A new Texture2D is created
	* @param textureName	The texture name used when stored
	* @param width			The texture width
	* @param height			The texture height
	* @param channels		The texture channels number
	* @param data			The texture byte data
	*/
	EquirectangularMap(std::string textureName, int width, int height, float* data);

private:
	unsigned id;

	int width;
	int height;



};
