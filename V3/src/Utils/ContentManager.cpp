#include "pch.h"

#include "ContentManager.h"
#include "FileUtils.h"
#include "SOIL/SOIL.h"
#include "SOIL/stb_image_aug.h"
#include "..\Rendering\Texture2D.h"
#include "..\Rendering\Shader.h"
#include "..\Rendering\CubeMapGL.h"
#include "..\Core\Core.h"

ContentManager* ContentManager::instance;

ContentManager::ContentManager()
{

}
ContentManager::~ContentManager()
{

}

ContentManager& ContentManager::Instance()
{
	static ContentManager instance;
	return instance;
}

Model* ContentManager::LoadModel(std::string path, bool loadTextures,bool preserve)
{
	Model* m = assimpWrapper.LoadModel(path, loadTextures,preserve);
	std::unique_ptr<Asset> m_unique = std::unique_ptr<Model>(m);
	containers[typeid(Model).name()].Load(m->name, m_unique, preserve);
	//Logger::LogError("Loaded model", m->name);


	return dynamic_cast<Model*>(m_unique.get());
	return nullptr;
}

EquirectangularMap* ContentManager::LoadEquirectangularMap(std::string path, bool preserve)
{
	int width;
	int height;
	int channels;
	std::unique_ptr<Asset> t;

	float* data = stbi_loadf(path.c_str(), &width, &height, &channels, 0);

	if (data)
	{
		std::string namerr = FileUtils::GetFileNameNoExtensionFromAbsolutePath(path);

		t = std::unique_ptr<EquirectangularMap>(new EquirectangularMap(namerr, width, height, data));
		EquirectangularMap* ret = dynamic_cast<EquirectangularMap*>(t.get());

		containers[typeid(EquirectangularMap).name()].Load(namerr, t, preserve);
		return ret;
	}
	else
	{
		Logger::LogError("Error while loading", path, "Error", SOIL_last_result());

	}

	return GetAsset<EquirectangularMap>("errorTexture");
}
Texture2D* ContentManager::LoadTexture(std::string path, bool preserve )
{
	int width;
	int height;
	int channels;
	std::unique_ptr<Asset> t;
	
	unsigned char* data = SOIL_load_image(path.c_str(), &width, &height, &channels, 0);

	if (data)
	{
		 std::string namerr = FileUtils::GetFileNameNoExtensionFromAbsolutePath(path);

		 t = Core::Instance().GetGraphicsAPI().CreateTexture2D(namerr, width, height, channels, data);
		 Texture2D* ret = dynamic_cast<Texture2D*>(t.get());

		 containers[typeid(Texture2D).name()].Load(namerr, t, preserve);
		 return ret;		
	}
	else
	{
		Logger::LogError("Error while loading", path, "Error", SOIL_last_result());

	}

	return GetAsset<Texture2D>("errorTexture");
}

Shader* ContentManager::LoadShader(std::string name, std::string vertexPath, std::string fragmentPath, bool preserve )
{
	std::string vertexFileContent = FileUtils::ReadFileToString(vertexPath);
	std::string fragFileContent = FileUtils::ReadFileToString(fragmentPath);

	std::unique_ptr<Asset> s = Core::Instance().GetGraphicsAPI().CreateShader(name, vertexFileContent, fragFileContent);
	containers[typeid(Shader).name()].Load(name, s, preserve);
	return dynamic_cast<Shader*>(s.get());
}


CubeMap* ContentManager::LoadCubeMap(std::string pathToFolder,bool preserve,std::string top, std::string bottom, std::string left, std::string right, std::string front, std::string back)
{

	//Push back order matters
	std::vector<std::string> faces;
	faces.push_back(right);
	faces.push_back(left);
	faces.push_back(top);
	faces.push_back(bottom);
	faces.push_back(back);
	faces.push_back(front);


	unsigned char* data[6];
	int width[6];
	int height[6];

	for (unsigned int i = 0; i < 6; i++)
	{
		std::string absolutePathToTexture = pathToFolder + "\\" + faces[i];
		data[i] = SOIL_load_image(absolutePathToTexture.c_str(),&width[i] ,&height[i], 0, 0);
		//Logger::LogInfo("Loaded cubemap texture",absolutePathToTexture);

		if (!data[i])
			Logger::LogError("Something went wrong while loading CUBEMAP TEXTURE: {}, {}", faces[i], SOIL_last_result());
	}

	std::string folderName = FileUtils::GetLastFolderNameFromAbsolutePath(pathToFolder + "\\");
	std::unique_ptr<Asset> c = Core::Instance().GetGraphicsAPI().CreateCubeMap(folderName, data,width,height);
	containers[typeid(CubeMap).name()].Load(folderName, c, preserve);

	return dynamic_cast<CubeMap*>( c.get());
}

Mesh* ContentManager::AddMesh(std::string name, Mesh* mesh, bool preserve)
{
	containers[typeid(Mesh).name()].LoadRaw(name, mesh , preserve);
	return mesh;

}



void ContentManager::ReadHeightmapData(std::string path, unsigned char* &dataOut, int& widthOut, int& heightOut)
{
	if (FileUtils::IsFileThere(path))
		dataOut = SOIL_load_image(path.c_str(), &widthOut, &heightOut, 0, SOIL_LOAD_L);
	else
	{
		Logger::LogError("ERROR: Heightmap not available at", path);
	}
}
