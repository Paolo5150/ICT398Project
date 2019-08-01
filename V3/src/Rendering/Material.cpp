#include "pch.h"

#include "Material.h"
#include "..\Utils\ContentManager.h"


Material::Material()
{
	PreloadMaterial();

}

Material::Material(Shader* s)
{
	shader = s;
	textures.clear();
	PreloadMaterial();

}

Material::~Material()
{}



void Material::PreloadMaterial()
{
	LoadVec3("color", 1,1,1);
	LoadFloat("shininess", 10.0f);
	LoadFloat("UVScale", 1.0f);
	LoadFloat("reflectivness", 0.0f);

}

void Material::LoadVec4(std::string name, glm::vec4 v)
{
	vec4s["material." + name] = v;
}

void Material::LoadVec3(std::string name, float x, float y, float z)
{
	vec3s["material." + name] = glm::vec3(x,y,z);
}

//Temporary
void Material::LoadMat4(std::string name, glm::mat4 v)
{
	mat4s[name] = v;
}

void Material::LoadFloat(std::string name, float v)
{
	floats["material." + name] = v;
}

void Material::SetColor(float r, float g, float b)
{
	LoadVec3("color", r, g, b);
}

void Material::GetColor(float& r, float &g, float& b)
{
	glm::vec3 c = vec3s["material.color"];
	r = c.x;
	g = c.y;
	b = c.z;
}

void Material::LoadEquirectangularMap(EquirectangularMap* t, std::string uniformName)
{
	equirectMaps[uniformName] = t;

}

void Material::LoadCubemap(CubeMap* t, std::string uniformName)
{

	//Check if texture is already loaded
	/*auto it = cubemaps.begin();

	for (; it != cubemaps.end(); it++)
	{
		if (it->second == t)
		{
			return;
		}
	}*/

	cubemaps[uniformName] = t;
}



void Material::Loadtexture(Texture2D* t, std::string uniformName)
{

	//Check if texture is already loaded
/*	auto it = textures.begin();

	for (; it != textures.end(); it++)
	{
		if (it->first == uniformName)
		{
			return;
		}
	}*/

	textures[uniformName] = t;

}

void Material::BindMaterial()
{
	shader->Bind(); //This line is kind of vital
	auto it = textures.begin();

	int uniformCounter = 0;
	for (; it != textures.end(); it++)
	{
		if (it->second)
		{

		glActiveTexture(GL_TEXTURE0 + uniformCounter);
		glEnable(GL_TEXTURE_2D);
		it->second->Bind();
		shader->SetInt(it->first, uniformCounter);
		uniformCounter++;
		}
	}

	for (auto cit = cubemaps.begin(); cit != cubemaps.end(); cit++)
	{
		//Logger::LogInfo("Binding a cubemap");
		glActiveTexture(GL_TEXTURE0 + uniformCounter);
		cit->second->Bind();
		shader->SetInt(cit->first, uniformCounter);
		uniformCounter++;
	}

	for (auto cit = equirectMaps.begin(); cit != equirectMaps.end(); cit++)
	{
		//Logger::LogInfo("Binding a cubemap");
		glActiveTexture(GL_TEXTURE0 + uniformCounter);
		cit->second->Bind();
		shader->SetInt(cit->first, uniformCounter);
		uniformCounter++;
	}

	auto vit = vec3s.begin();

	for (; vit != vec3s.end(); vit++)
	{
		shader->SetVec3(vit->first, vit->second);
	}

	auto vit2 = vec4s.begin();

	for (; vit2 != vec4s.end(); vit2++)
	{
		shader->SetVec4(vit2->first, vit2->second);
	}

	auto vit3 = floats.begin();

	for (; vit3 != floats.end(); vit3++)
	{
		shader->SetFloat(vit3->first, vit3->second);
	}

	auto matit = mat4s.begin();

	for (; matit != mat4s.end(); matit++)
	{
		shader->SetMat4(matit->first, matit->second);
	}


}

void Material::UnbindMaterial()
{
	
	auto it = textures.begin();
	int uniformCounter = 0;
	for (; it != textures.end(); it++)
	{

		glActiveTexture(GL_TEXTURE0 + uniformCounter);
		glBindTexture(GL_TEXTURE_2D, 0);
	//	shader->SetInt(it->first, uniformCounter);

		glDisable(GL_TEXTURE);
		//shader->SetInt(textureUniforms[it->first], it->first);
		uniformCounter++;



	}

	for (auto cit = cubemaps.begin(); cit != cubemaps.end(); cit++)
	{
		glActiveTexture(GL_TEXTURE0 + uniformCounter);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	//	shader->SetInt(cit->first, uniformCounter);
		uniformCounter++;
	}

	glActiveTexture(GL_TEXTURE0);

}
