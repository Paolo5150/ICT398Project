#pragma once
#include "SOIL/SOIL.h"
#include "SOIL/stb_image_aug.h"
#include "..\Core\Logger.h"
#include "..\Utils\Asset.h"

/**
* @class Texture2D
* @brief Generic texture class
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class Texture2D : public Asset
{
public:
	enum BUFFER_SIZE
	{
		X_8,
		X_16,
		X_32
	};
	/**
	* @brief		Return the texture id
	* @pre			The texture objecct must exist
	* @post			The texture id is returned
	* @return		The texture id
	*/
	unsigned GetID() { return id; }

	/**
	* @brief		Activate texture
	* @pre			The texture objecct must exist
	* @post			The texture is activated
	*/
	virtual void Bind() = 0;

	/**
	* @brief		Destroy texture, unload from GPU
	* @pre			The texture objecct must exist
	* @post			The texture is destroyed
	*/
	virtual ~Texture2D(){};

protected:
	/**
	* @brief				Default constructor
	*
	* @pre					The graphics API object must exist
	* @post					A new Texture2D is created with no data

	*/
	Texture2D(){}

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
	Texture2D(std::string textureName, int width, int height, int channels,unsigned char* data){};

	/**
	* @brief				Create a new empty Texture2D
	*
	* @pre					The graphics API object must exist
	* @post					A new Texture2D is created with no data
	* @param textureName	The texture name used when stored
	* @param width			The texture width
	* @param height			The texture height
	* @param isDepth		Whether the texture is a depth buffer texture
	*/
	Texture2D(unsigned width, unsigned height, bool isDepth = false){};

	Texture2D(std::string name, unsigned width, unsigned height, BUFFER_SIZE size) {};

	unsigned id;
	int width;
	int height;
	int channels;
	unsigned char* data;

	};


