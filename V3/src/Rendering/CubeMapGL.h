#pragma once
#include "SOIL/SOIL.h"
#include "SOIL/stb_image_aug.h"
#include "..\Core\Logger.h"
#include "CubeMap.h"
#include <vector>


/**
* @class CubeMapGL
* @brief Cubemap specialized for OpenGL API
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class CubeMapGL : public CubeMap
{

public:
	/**
	* @brief				Create a new Cubemap texture
	*
	* @pre					The graphics API object must exist
	* @post					A new Cubemap is created
	* @param name			The cubemap name used when stored
	* @param width			The textures width
	* @param height			The textures height
	* @param data			The byte data of the 6 textures
	* @return				The new cubemap
	*/
	CubeMapGL(std::string name, unsigned char* data[6], int width[6], int height[6]);

	/**
* @brief				Create a new Cubemap texture
*
* @pre					The graphics API object must exist
* @post					A new Cubemap is created
* @param name			The cubemap name used when stored
* @param width			The textures width
* @param height			The textures height
* @param data			The byte data of the 6 textures
* @return				The new cubemap
*/
	CubeMapGL(std::string name,  int width, int height, bool isDepth = false);


	/**
	* @brief				Destroy the Cubemap texture
	*
	* @pre					The Cubemap must exist
	* @post					The cubemap is destroyed
	*/
	~CubeMapGL();

	/**
	* @brief				Bind the cubemap
	*
	* @pre					The Cubemap must exist
	* @post					The cubemap is ready to be used
	*/
	virtual void Bind() override;
};

