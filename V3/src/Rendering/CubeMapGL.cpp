#include "pch.h"

#include "CubemapGL.h"


CubeMapGL::CubeMapGL(std::string name, unsigned char* data[6], int width[6], int height[6]) : CubeMap(name,data,width,height)
{

	glGenTextures(1, &cubemapID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);

	int channels = 0;
	for (unsigned int i = 0; i < 6; i++)
	{
	
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width[i], height[i], 0, GL_RGB, GL_UNSIGNED_BYTE, data[i]);
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

CubeMapGL::CubeMapGL(std::string name, int width, int height, bool isDepth) : CubeMap(name,  width, height, isDepth)
{
	glGenTextures(1, &cubemapID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);

	int channels = 0;
	for (unsigned int i = 0; i < 6; i++)
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		if (!isDepth)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		}
		else
		{		
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

		}
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

CubeMapGL::~CubeMapGL()
{
	glDeleteTextures(1, &cubemapID);
}


void CubeMapGL::Bind()
{

	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);
}