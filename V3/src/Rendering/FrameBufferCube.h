#pragma once
#include "FrameBuffer.h"
#include "CubeMapGL.h"
#include "..\Core\Window.h"

/**
* @class FrameBufferCube
* @brief Specialized class for a custom frame buffer for Opengl
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class FrameBufferCube : public FrameBufferBase
{
public:
	/**
	* @brief				Create a new frame buffer
	*
	* @pre					The graphics API object must exist
	* @post					A new frame buffer object is created
	* @param w				The width of the buffer texture
	* @param h				The height of the buffer texture
	* @param hasColorAttachment		Whether the frame buffer has a color attachment
	*/
	FrameBufferCube(std::string name, int w, int h, bool hasColorAttachment);

	/**
	* @brief				Destroy the frame buffer
	*
	* @pre					The frame buffer must exist
	* @post					The frame buffer is destroyed

	*/
	~FrameBufferCube();

	/**
	* @brief				Bind the frame buffer
	*
	* @pre					The frame buffer must exist
	* @post					The frame buffer is ready to be used
	*/
	void Bind() override;


	/**
	* @brief				Unbind the frame buffer and bind the default frame buffer (screen)
	*						Reset the viewport to screen size
	* @pre					The frame buffer must exist
	* @post					The frame buffer is disabled
	*/
	void Unbind() override;

	/**
	* @brief				Resize the texture
	* @pre					The frame buffer must exist
	* @post					The texture of the frame buffer is resizedd
	* @param w				The width of the texture
	* @param h				The height of the texture

	*/
	void ResizeTexture(int w, int h) override;
	bool hasColorAttachment;

	std::unique_ptr<CubeMap> colorCubemap;
	std::unique_ptr<CubeMap> depthCubemap;


};
