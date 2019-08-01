#pragma once
#include "FrameBufferBase.h"
#include "Texture2D.h"

/**
* @class FrameBuffer
* @brief Generic class for a custom frame buffer 
*
* Allows to render to a texture
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class FrameBuffer : public FrameBufferBase
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
	FrameBuffer(std::string name,int w, int h,bool hasColorAttachment = true, bool isHDR = false){};

	/**
	* @brief				Destroy the frame buffer
	*
	* @pre					The frame buffer must exist
	* @post					The frame buffer is destroyed

	*/
	virtual ~FrameBuffer(){};

	/**
	* @brief				Bind the frame buffer
	*
	* @pre					The frame buffer must exist
	* @post					The frame buffer is ready to be used
	*/
	virtual void Bind() override {};

	/**
	* @brief				Unbind the frame buffer and bind the default frame buffer (screen)
	*						Reset the viewport to screen size
	* @pre					The frame buffer must exist
	* @post					The frame buffer is disabled
	*/
	virtual void Unbind() override {};

	/**
	* @brief				Get the color texture
	* @pre					The frame buffer must exist
	* @post					The color texture is returned
	* @return				The color texture
	*/
	Texture2D* GetColorTexture(int index = 0){ return (colorAttachments[index]).get(); };

	/**
	* @brief				Get the depth texture
	* @pre					The frame buffer must exist
	* @post					The depth texture is returned
	* @return				The depth texture
	*/
	Texture2D* GetDepthTexture(){ return depthTexture.get(); };

	/**
	* @brief				Resize the texture
	* @pre					The frame buffer must exist
	* @post					The texture of the frame buffer is resizedd
	* @param w				The width of the texture
	* @param h				The height of the texture

	*/
	virtual void ResizeTexture(int w, int h) override {};

protected:
	   	  
	std::vector<std::unique_ptr<Texture2D>> colorAttachments;

	/**
	* @brief The depth texture
	*/
	std::unique_ptr<Texture2D> depthTexture;


};
