#include "pch.h"
#include "API_Opengl.h"
#include "Texture2DGL.h"
#include "VertexArrayGL.h"
#include "ArrayBufferGL.h"
#include "UniformBufferGL.h"
#include "FrameBufferGL.h"
#include "CubeMapGL.h"

API_Opengl::API_Opengl()
{
	apiName = OPENGL;
}
API_Opengl::~API_Opengl()
{
}

void API_Opengl::Initialize()
{
	glewExperimental = true;
	//Initialize glew
	if (glewInit() != GLEW_OK)
	{
		Logger::LogError("GLEW failed to initialize");
	}

	//OpengGL initialization
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glClear(GL_COLOR_BUFFER_BIT);	
}

void API_Opengl::SetClearColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0);
}


void API_Opengl::ClearColorBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
void API_Opengl::ClearDepthBuffer()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void API_Opengl::SetViewPort(int w, int h)
{
	glViewport(0, 0, w, h);
}

std::unique_ptr<Shader> API_Opengl::CreateShader(std::string name, std::string vertexSource, std::string fragmentSource)
{
	return std::unique_ptr<Shader>(new ShaderGL(name,vertexSource, fragmentSource));
}

std::unique_ptr<Texture2D> API_Opengl::CreateTexture2D(std::string textureName, int width, int height, int channels, unsigned char* data)
{
	return std::unique_ptr<Texture2D>(new Texture2DGL(textureName, width, height, channels, data));
}
std::unique_ptr<Texture2D> API_Opengl::CreateTexture2D(std::string name, unsigned width, unsigned height, bool isDepth )
{
	return std::unique_ptr<Texture2D>(new Texture2DGL(name, width, height, isDepth));
}

void API_Opengl::Shutdown()
{

}

void API_Opengl::ResetTextures()
{
	//Reset active textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

ArrayBuffer<Vertex>* API_Opengl::CreateVertexBuffer()
{
	return new ArrayBufferGL<Vertex>();
}
ArrayBuffer<unsigned>* API_Opengl::CreateIndexBuffer()
{
	return new ArrayBufferGL<unsigned>();
}

VertexArray* API_Opengl::CreateVertexArray()
{
	return new VertexArrayGL();
}

std::unique_ptr<UniformBuffer> API_Opengl::CreateUniformBuffer(unsigned totalSize, unsigned binding)
{
	return std::unique_ptr<UniformBuffer>(new UniformBufferGL(totalSize, binding));
}

std::unique_ptr<FrameBuffer> API_Opengl::CreateFrameBuffer(std::string name, int w, int h, int numAttachments, bool isHDR)
{
	return std::unique_ptr<FrameBuffer>(new FrameBufferGL(name,w, h, numAttachments, isHDR));
}

void  API_Opengl::SetClipPlaneActive(bool ac)
{
	if (ac)
		glEnable(GL_CLIP_DISTANCE0);
	else
		glDisable(GL_CLIP_DISTANCE0);
}


std::unique_ptr<CubeMap> API_Opengl::CreateCubeMap(std::string name, unsigned char* data[6], int width[6], int height[6])
{
	return std::unique_ptr<CubeMap>(new CubeMapGL(name, data,width,height));
}


