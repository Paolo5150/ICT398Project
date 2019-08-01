#pragma once
#include "Texture2D.h"
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
class Texture2DGL : public Texture2D
{
public:
	friend class API_Opengl;

	/**
* @brief				Default constructor
*
* @pre					The graphics API object must exist
* @post					A new Texture2D is created with no data

*/
	Texture2DGL() {}

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
	~Texture2DGL();




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
	Texture2DGL(std::string textureName, int width, int height, int channels, unsigned char* data);

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
	Texture2DGL(std::string name,unsigned width, unsigned height, bool isDepth = false);

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
	Texture2DGL(std::string name, unsigned width, unsigned height, BUFFER_SIZE size);



};
