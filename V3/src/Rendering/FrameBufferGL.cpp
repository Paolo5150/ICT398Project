#include "pch.h"
#include "FrameBufferGL.h"
#include "..\Core\Core.h"
#include "Texture2DGL.h"
#include <GL/glew.h>

FrameBufferGL::FrameBufferGL(std::string name, int w, int h, int numColorAttachment, bool isHDR) : FrameBuffer(name,w, h, numColorAttachment, false)
{
	width = w;
	height = h;
	glGenFramebuffers(1, &bufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, bufferID);
	this->numColorAttachments = numColorAttachment;
	this->name = name;

	if (numColorAttachment != 0)
	{
		attachments = new unsigned[numColorAttachments];
		for (int i = 0; i < numColorAttachment; i++)
		{
			std::stringstream ss;
			ss << name;
			ss << "_colorAttach";
			ss << i;
			if (!isHDR)
			{
				std::unique_ptr<Texture2D> t = Core::Instance().GetGraphicsAPI().CreateTexture2D(ss.str(), w, h);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, t->GetID(), 0);
				attachments[i] = t->GetID();
				colorAttachments.push_back(std::move(t));
			}
			else
			{
				std::unique_ptr<Texture2D> t = std::unique_ptr<Texture2D>(new Texture2DGL(ss.str(), w, h,Texture2D::X_16));
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, t->GetID(), 0);
				attachments[i] = t->GetID();
				colorAttachments.push_back(std::move(t));
			}

		}		

		glDrawBuffers(numColorAttachments, attachments);
	}
	else
	{
		
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}

	std::stringstream ss;
	ss << name;
	ss << "_depthAttach";

	depthTexture = Core::Instance().GetGraphicsAPI().CreateTexture2D(ss.str(), w, h,true);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture->GetID(), 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		Logger::LogError("Error while creating the FRAME BUFFER");
	}
	Unbind();




}

void FrameBufferGL::ResizeTexture(int w, int h)
{
	
	this->width = w;
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

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void FrameBufferGL::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, bufferID);
	glDrawBuffers(numColorAttachments, attachments);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
}
void FrameBufferGL::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	int w, h;
	Window::Instance().GetWindowSize(w, h);
	glViewport(0, 0, w,h);
}

FrameBufferGL::~FrameBufferGL()
{
	//Logger::LogError("Frame buffer destroyed");
	glDeleteFramebuffers(1, &bufferID);
}