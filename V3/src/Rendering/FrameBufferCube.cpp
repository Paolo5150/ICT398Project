#include "pch.h"
#include "FrameBufferCube.h"
#include "..\Core\Core.h"
#include "Texture2DGL.h"
#include <GL/glew.h>

FrameBufferCube::FrameBufferCube(std::string name, int w, int h, bool hasColorAttachment)
{
	width = w;
	height = h;
	this->hasColorAttachment = hasColorAttachment;
	this->name = name;
	glGenFramebuffers(1, &bufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, bufferID);

	if (hasColorAttachment)
	{
		std::stringstream ss;
		ss << name;
		ss << "_colorAttach";
		colorCubemap = std::unique_ptr<CubeMapGL>(new CubeMapGL(ss.str(), w, h));
		for (int i = 0; i < 6; i++)
		{		
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, colorCubemap->GetID(), 0);
		}
	}
	else
	{

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}

	std::stringstream ss;
	ss << name;
	ss << "_depthAttach";

	//Depth
	depthCubemap = std::unique_ptr<CubeMapGL>(new CubeMapGL(ss.str(), w, h,true));
	for (int i = 0; i < 6; i++)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, depthCubemap->GetID(), 0);
	}

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		Logger::LogError("Error while creating the FRAME BUFFER");
	}
	Unbind();
}

void FrameBufferCube::ResizeTexture(int w, int h)
{

/*	this->width = w;
	this->height = h;

	for (int i = 0; i < colorAttachments.size(); i++)
	{
		if (colorAttachments[i] != NULL)
		{

			colorAttachments[i]->Bind();
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		}
	}
	if (depthTexture != NULL)
	{

		depthTexture->Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);*/

}

void FrameBufferCube::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, bufferID);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
}
void FrameBufferCube::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	int w, h;
	Window::Instance().GetWindowSize(w, h);
	glViewport(0, 0, w, h);
}

FrameBufferCube::~FrameBufferCube()
{
	//Logger::LogError("Frame buffer destroyed");
	glDeleteFramebuffers(1, &bufferID);
}