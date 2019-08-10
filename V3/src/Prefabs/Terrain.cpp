#include "pch.h"
#include "Terrain.h"
#include "..\Utils\ContentManager.h"
#include "..\Rendering\Layers.h"
#include "..\Utils\Maths.h"
#include "..\Lighting\LightingManager.h"
#include "..\Core\Input.h"

#include "..\Physics\PhysicsWorld.h"


Terrain::Terrain(int size) : GameObject("Terrain")
{
	Initialize(size);
}

void Terrain::Initialize(int size)
{
	this->terrainSize = size;

	Material material;
	material.SetShader(ContentManager::Instance().GetAsset<Shader>("PBRHeight"));
	material.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("moss_normal"), "normalMap");
	material.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("moss_albedo"), "albedoMap");
	material.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("moss_roughness"), "roughnessMap");
	material.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("limestone_height"), "heightMap");
	material.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("moss_ao"), "aoMap");
	material.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("moss_metallic"), "metallicMap");



	material.LoadFloat("UVScale", 2.0);
	material.LoadFloat("shininess", 18.0f);
	material.LoadFloat("height_scale", 0.02);



	SetLayer(0);
	SetLayer(RenderingLayers::TERRAIN);

	isWireframe = 0;

	gridMesh = std::unique_ptr<Mesh>(new GridMesh(size, size));
	meshRenderer = new MeshRenderer(gridMesh.get(), material);
	meshRenderer->SetMaterial(material);
	meshRenderer->SetIsCullable(false);
	meshRenderer->GetMaterial(MaterialType::NOLIGHT).SetShader(ContentManager::Instance().GetAsset<Shader>("TerrainNoLight"));
	meshRenderer->GetMaterial(MaterialType::NOLIGHT).LoadVec3("color", 0.7, 0.7, 0.7);

	meshRenderer->GetMaterial(MaterialType::COLORONLY).SetShader(ContentManager::Instance().GetAsset<Shader>("ColorOnlyStatic"));
	meshRenderer->GetMaterial(MaterialType::COLORONLY).LoadVec3("color", 0.7, 0.7, 0.7);

	meshRenderer->AddPreRenderCallback(std::bind(&Terrain::OnPreRender, this, std::placeholders::_1, std::placeholders::_2));
	meshRenderer->AddPostRenderCallback(std::bind(&Terrain::OnPostRender, this, std::placeholders::_1, std::placeholders::_2));

	meshRenderer->SetIsCullable(false);

	this->AddComponent(meshRenderer);	

	//transform.SetScale(20, 600, 20);
	transform.SetScale(1, 1, 1);
	transform.Translate(0, 0, 0);
	transform.SetRotation(0, 0, 0);
}

void Terrain::OnPreRender(Camera& cam, Shader* s)
{
	
	/*s->SetFloat("shadowMapCount", LightManager::Instance().GetShadowMapsCount());

	if (s->name == "Terrain")
		LightManager::Instance().SendShadowToShader(meshRenderer->GetMaterial().GetShader());*/

}

void Terrain::OnPostRender(Camera& cam, Shader* s)
{

}

float TriangleBaric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos)
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p3.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

float Terrain::GetHeightAt(int worldX, int worldZ)
{
	glm::vec3 local = glm::inverse(transform.GetMatrix()) * glm::vec4(worldZ, 0, worldX, 1.0);

	int index = local.z * terrainSize + local.x;
	glm::vec3 v = (meshRenderer->GetMesh().vertices[index].position);
	v = transform.GetMatrix() * glm::vec4(v.x, v.y, v.z, 1.0);

	int terrainZ = worldX / transform.GetScale().x - transform.GetPosition().x;
	int terrainX = worldZ / transform.GetScale().z - transform.GetPosition().z;

	float gridSuqareSize = terrainSize / (float)meshRenderer->GetMesh().vertices.size() - 1;

	int gridX = -glm::floor(terrainX / gridSuqareSize);
	int gridZ = -glm::floor(terrainZ / gridSuqareSize);


	float h1 = TriangleBaric(meshRenderer->GetMesh().vertices[gridZ * terrainSize + gridX].position,
		meshRenderer->GetMesh().vertices[gridZ * terrainSize + gridX + 1].position,
		meshRenderer->GetMesh().vertices[(gridZ + 1) * terrainSize + gridX].position,
		glm::vec2(worldX / transform.GetScale().x, worldZ / transform.GetScale().x));

	/*float h2 = TriangleBaric(meshRenderer->GetMesh().vertices[gridZ * terrainSize + gridX].position,
		meshRenderer->GetMesh().vertices[gridZ * terrainSize + gridX + 1].position,
		meshRenderer->GetMesh().vertices[(gridZ + 1) * terrainSize + gridX+1].position,
		glm::vec2(worldX / transform.GetScale().x, worldZ / transform.GetScale().x));*/

	return (h1)* transform.GetScale().y;

}


void Terrain::GetCenter(int& x, int& y, int& z)
{
	int xr = this->terrainSize / 2;
	int xz = terrainSize / 2;
	glm::vec3 v = (meshRenderer->GetMesh().vertices[((xz)*terrainSize) + xr].position);
	v = transform.GetMatrix() * glm::vec4(v.x, v.y, v.z, 1.0);

	x = v.x;
	y = v.y;
	z = v.z;
}


glm::vec3 Terrain::GetCenter()
{
	int xr = this->terrainSize / 2;
	int xz = terrainSize / 2;
	glm::vec3 v = (meshRenderer->GetMesh().vertices[((xz)*terrainSize) + xr].position);
	v = transform.GetMatrix() * glm::vec4(v.x, v.y, v.z, 1.0);

	return v;
}



void Terrain::NormaliseTerrain(float* heightData, int dataWidth, int dataHeight)
{
	float fMin, fMax;
	float fHeight;
	int i;
	fMin = heightData[0];
	fMax = heightData[0];
	//find the min/max values of the height terrainData
	for (i = 1; i < dataWidth*dataHeight; i++) {
		if (heightData[i] > fMax)
			fMax = heightData[i];
		else if (heightData[i] < fMin)
			fMin = heightData[i];
	}
	//find the range of the altitude
	if (fMax <= fMin)
		return;
	fHeight = fMax - fMin;
	//scale the values to a range of 0-255
	for (i = 0; i < dataWidth*dataHeight; i++)
		heightData[i] = ((heightData[i] - fMin) / fHeight);

}
void Terrain::AddFilter(float* heightData, float weight, int size)
{
	int i;
	//erode left to right, starting at the beginning of each row
	for (i = 0; i < size; i++)
		FilterPass(&heightData[size*i], 1, weight, size);
	//erode right to left, starting at the end of each row
	for (i = 0; i < size; i++)
		FilterPass(&heightData[size*i + size - 1], -1, weight, size);
	//erode top to bottom, starting at the beginning of each column
	for (i = 0; i < size; i++)
		FilterPass(&heightData[i], size, weight, size);
	//erode from bottom to top, starting from the end of each column
	for (i = 0; i < size; i++)
		FilterPass(&heightData[size*(size - 1) + i], -size, weight, size);

}
void Terrain::FilterPass(float* dataP, int increment, float weight, int size)
{

	float yprev = *dataP; // the starting point in the terrain array
	int j = increment; // +1, -1, +size, -size
	float k = weight;

	for (int i = 1; i < size; i++) {
		// yi = k yi-1 + (1-k) xi
		*(dataP + j) = k * yprev + (1 - k)*(*(dataP + j)); //
		yprev = *(dataP + j);
		j += increment;
	}

}
unsigned char* getColorAtPixel(unsigned char* image, size_t x, size_t y, size_t width, int elementsPerPixel = 3) { // 1 for R, 2 for RG, 3 for RGB, 4 for RBGA
	return (image + (y * width + x) * 1);
}

/*
void Terrain::ApplyHeightMap(std::string texturePath)
{

	int width, height;
	unsigned char* terrainData = SOIL_load_image(texturePath.c_str(), &width, &height, 0, SOIL_LOAD_L);

	//AssetLoader::Instance().ReadHeightmapData(texturePath, terrainData, width, height);

	if (terrainData)
	{
		Logger::LogInfo("Loading hm", width);
		float* heights = new float[width * height];;

		int index = 0;


		int count = 0;
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				int index = i * height + j;

				float rgb = *getColorAtPixel(terrainData, i, j, width, 3);
				heights[index] = rgb;
				//Logger::LogInfo("Height", rgb);

				count++;
			}
		}

		for (int i = 0; i < 20; i++)
			AddFilter(heights, 0.2f, width);

		NormaliseTerrain(heights, width, height);

		stbi_image_free(terrainData);

		float min = 50000;
		float max = -5000;
		for (int j = 0; j < terrainSize; j++)
		{
			for (int i = 0; i < terrainSize; i++)
			{

				meshRenderer->GetMesh().vertices[(j*terrainSize) + i].position.y = heights[(width * (width * j / terrainSize)) + (width * i / terrainSize)];


				min = meshRenderer->GetMesh().vertices[(j*terrainSize) + i].position.y < min ? meshRenderer->GetMesh().vertices[(j*terrainSize) + i].position.y : min;
				max = meshRenderer->GetMesh().vertices[(j*terrainSize) + i].position.y > max ? meshRenderer->GetMesh().vertices[(j*terrainSize) + i].position.y : max;

			}
		}
			   
		meshRenderer->GetMesh().CalculateNormals();
		meshRenderer->GetMesh().RefreshVertexBuffer();
		//transform.Translate(-meshRenderer->GetMesh().GetCenter().x, -meshRenderer->GetMesh().GetCenter().y, -meshRenderer->GetMesh().GetCenter().z);
		delete[] heights;
	}

}
*/
float Terrain::GetTerrainMaxX()
{
	return meshRenderer->GetMesh().vertices[((terrainSize - 1) * terrainSize) + (terrainSize - 1)].position.x * transform.GetScale().x;
}
float Terrain::GetTerrainMinX()
{
	return meshRenderer->GetMesh().vertices[(0 * terrainSize) + 0].position.x * transform.GetScale().x* transform.GetScale().x;
}

float Terrain::GetTerrainMaxZ()
{
	return meshRenderer->GetMesh().vertices[((terrainSize - 1) * terrainSize) + (terrainSize - 1)].position.z * transform.GetScale().z;
}
float Terrain::GetTerrainMinZ()
{
	return meshRenderer->GetMesh().vertices[(0 * terrainSize) + 0].position.x * transform.GetScale().z* transform.GetScale().z;
}

