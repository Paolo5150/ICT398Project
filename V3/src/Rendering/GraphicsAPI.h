#pragma once
#include <iostream>

#include "..\Core\Logger.h"
#include "ArrayBuffer.h"
#include "VertexArray.h"
#include "Vertex.h"
#include "UniformBuffer.h"
#include "FrameBuffer.h"
#include "CubeMap.h"

class Shader;
class Texture2D;

/**
* @class GraphicsAPI
* @brief Generic class for graphics API
*
* Facade third party graphics API
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/

class GraphicsAPI
{
public:
	
	enum API_NAME
	{
		OPENGL,
		DIRECTX
	};
	/**
	* @brief		Creates the graphics API object
	*
	* @pre			The graphics API object does not exist
	* @post			The graphics API object is created
	*
	*/
	GraphicsAPI(){};
	/**
	* @brief		Destroy the graphics API object
	*
	* @pre			The graphics API object must exist
	* @post			The graphics API object is destroyed
	*/
	~GraphicsAPI(){};

	/**
	* @brief		Get the name of the current graphics API
	*
	* @pre			The graphics API object must exist
	* @post			The graphics API name is returned
	* @return		The name of the graphics API
	*/
	API_NAME GetApiName(){ return apiName; }

	/**
	* @brief		Initialize the graphics API object
	*
	* Initialize paramaters specific to this Graphics API
	* @pre			The graphics API object must exist
	* @post			The graphics API object is initialized
	*/
	virtual void Initialize() = 0;


	/**
	* @brief		Close the graphics API library
	*
	* @pre			The graphics API object must exist
	* @post			The graphics API library is closed
	*/
	virtual void Shutdown() = 0;

	/**
	* @brief		Clear the color buffer
	*
	* @pre			The graphics API object must exist
	* @post			The colo buffer is cleared with the set color
	*/
	virtual void ClearColorBuffer() = 0;

	/**
	* @brief		Clear the depth buffer
	*
	* @pre			The graphics API object must exist
	* @post			The depth buffer is cleared
	*/
	virtual void ClearDepthBuffer() = 0;

	/**
	* @brief		Set the view port
	*
	* @pre			The graphics API object must exist
	* @post			Theview port is set
	* @param w		The viewport width
	* @param h		The viewport height
	*/
	virtual void SetViewPort(int w, int h) = 0;

	/**
	* @brief		Set the clear color
	*
	* @pre			The graphics API object must exist
	* @post			The clear color is set
	* @param r		The red channel value
	* @param g		The green channel value
	* @param b		The blue channel value
	*/
	virtual void SetClearColor(float r, float g, float b) = 0;

	/**
	* @brief		Create a new shader
	*
	* @pre			The graphics API object must exist
	* @post			A new shader is created
	* @param name	The shader name used when stored
	* @param vertexSource	The vertex shader source code
	* @param fragmentSource	The fragment shader source code
	* @return				The new shader
	*/
	virtual std::unique_ptr<Shader> CreateShader(std::string name, std::string vertexSource, std::string fragmentSource) = 0;

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
	* @return				The new Texture2D
	*/
	virtual std::unique_ptr<Texture2D> CreateTexture2D(std::string textureName, int width, int height, int channels, unsigned char* data) = 0;

	/**
	* @brief				Create a new empty Texture2D
	*
	* @pre					The graphics API object must exist
	* @post					A new Texture2D is created with no data
	* @param textureName	The texture name used when stored
	* @param width			The texture width
	* @param height			The texture height
	* @param isDepth		Whether the texture is a depth buffer texture
	* @return				The newTexture2D
	*/
	virtual std::unique_ptr<Texture2D> CreateTexture2D(std::string name, unsigned width, unsigned height, bool isDepth = false) = 0;


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
	virtual std::unique_ptr<CubeMap> CreateCubeMap(std::string name, unsigned char* data[6], int width[6], int height[6]) = 0;
	/**
	* @brief				Reset the texture units
	*
	* @pre					The graphics API object must exist
	* @post					All texture units are unbinded
	*/
	virtual void ResetTextures()=0;
	/**
	* @brief				Create a new vertex buffer
	*
	* @pre					The graphics API object must exist
	* @post					A new vertex buffer is created
	* @return				The new vertex buffer
	*/
	virtual ArrayBuffer<Vertex>* CreateVertexBuffer() = 0;
	/**
	* @brief				Create a new index buffer
	*
	* @pre					The graphics API object must exist
	* @post					A new index buffer is created
	* @return				The new index buffer
	*/
	virtual ArrayBuffer<unsigned>* CreateIndexBuffer() = 0;


	/**
	* @brief				Create a new vertex array
	*
	* @pre					The graphics API object must exist
	* @post					A new veretx array is created
	* @return				The new vertex array
	*/
	virtual VertexArray* CreateVertexArray() = 0;
	/**
	* @brief				Create a new uniform buffer object
	*
	* @pre					The graphics API object must exist
	* @post					A new uniform buffer object is created
	* @param totalSize		The size of the buffer
	* @param binding		The bingind index
	* @return				The new uniform buffer object
	*/
	virtual std::unique_ptr<UniformBuffer> CreateUniformBuffer(unsigned totalSize, unsigned binding) = 0;

	/**
	* @brief				Create a new frame buffer
	*
	* @pre					The graphics API object must exist
	* @post					A new frame buffer object is created
	* @param w				The width of the buffer texture
	* @param h				The height of the buffer texture
	* @param hasColorAttachment		Whether the frame buffer has a color attachment
	* @return				The new uniform buffer object
	*/
	virtual std::unique_ptr<FrameBuffer> CreateFrameBuffer(std::string name,int w, int h, int numAttachments = 1, bool isHDR = false) = 0;

	/**
	* @brief				Enable/disable clipping plane
	*
	* @pre					The graphics API object must exist
	* @post					The clipping plane is enabled/disabled according to argument passed
	* @param cp				The boolean value that will enable/disable plane clipping

	*/
	virtual void SetClipPlaneActive(bool hasColorAttachment) = 0;

protected:
	/**
	@brief The graphics API name
	*/
	API_NAME apiName;
};