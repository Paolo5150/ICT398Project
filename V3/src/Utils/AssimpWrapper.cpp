#include "pch.h"
#include "AssimpWrapper.h"
#include "ContentManager.h"
#include "FileUtils.h"
#include "Maths.h"
//#include "..\Graphics\AnimatedModel.h"

namespace
{

static std::string fileNameOnly;
static std::string modelFolderName;
static std::string pathToFolder;
static bool texturesAsWell = true;
}
Model* AssimpWrapper::LoadModel(const std::string& path, bool loadTextures, bool preserve)
{
	Assimp::Importer import;
	texturesAsWell = loadTextures;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_FixInfacingNormals |
		aiProcess_GenNormals | aiProcessPreset_TargetRealtime_Quality);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		Logger::LogError("Assimp error: {}", import.GetErrorString());
		return NULL;
	}
	
	modelFolderName = FileUtils::GetLastFolderNameFromAbsolutePath(path);

	pathToFolder = "Assets\\Models\\" + modelFolderName ;
	Model* model = NULL;
//	AnimatedModel* animatedModel = NULL;
	preserveTextures = preserve;
	/*if (scene->HasAnimations())
	{
		//Logger::LogInfo("This model", modelFolderName, "is animated");
		animatedModel = new AnimatedModel();
		animatedModel->m_global_inverse_transform = glm::inverse(Maths::aiMatrix4x4ToGlm(scene->mRootNode->mTransformation));
		ProcessNode(scene->mRootNode, scene, NULL, animatedModel, true);


		LoadAnimations(scene, animatedModel);
		animatedModel->name = modelFolderName;
	}*/
	
	{


		model = new Model();
		ProcessNode(scene->mRootNode, scene, NULL, model, false);
		model->name = modelFolderName;

	}

	import.FreeScene();

	if (model != NULL)
		return model;

}

void AssimpWrapper::ProcessNode(aiNode* node, const aiScene* scene, ModelNode* parentNode, Model* model, bool isAnimated)
{
	ModelNode* n = new ModelNode();
	n->name = node->mName.C_Str();
	n->transform = Maths::aiMatrix4x4ToGlm(node->mTransformation);
	/*if (isAnimated)
	{
	((AnimatedModel*)model)->allNodes[n->name] = n;
	if (((AnimatedModel*)model)->rootNode == NULL)
		((AnimatedModel*)model)->rootNode = n;

	if (parentNode != NULL)
		parentNode->children.push_back(n);

	}*/


	for (unsigned i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* ai_mesh = scene->mMeshes[node->mMeshes[i]];

		ProcessMesh(ai_mesh, scene, model, isAnimated);

	}

	for (int i = 0; i < node->mNumChildren; i++)
		ProcessNode(node->mChildren[i], scene, n, model, isAnimated);

}

void AssimpWrapper::ProcessMesh(aiMesh* mesh, const aiScene* scene, Model* model, bool isAnimated)
{
	LoadMesh(mesh, model, isAnimated);

	//Logger::LogInfo("Processing mesh {}", mesh->mName.C_Str());
	Material associatedMaterial ;
	//material
	if (texturesAsWell &&  mesh->mMaterialIndex >= 0 && scene->mNumMaterials != 0)
	{
		//all pointers created in assimp will be deleted automaticaly when we call import.FreeScene();
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::string textureFolder = pathToFolder + "\\Textures";
		associatedMaterial = Material(ContentManager::Instance().GetAsset<Shader>("DefaultStatic"));

		if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			//Logger::LogInfo("This mesh has {} diffuse", material->GetTextureCount(aiTextureType_DIFFUSE));
			LoadTextureIntoMaterial(aiTextureType_DIFFUSE, material, &associatedMaterial, textureFolder, model);
		}

		if (material->GetTextureCount(aiTextureType_NORMALS) > 0)
		{
			//Logger::LogInfo("This mesh has {} normal", material->GetTextureCount(aiTextureType_NORMALS));
			LoadTextureIntoMaterial(aiTextureType_NORMALS, material, &associatedMaterial, textureFolder, model);
		}

		if (material->GetTextureCount(aiTextureType_EMISSIVE) > 0)
		{
			//Logger::LogInfo("This mesh has {} normal", material->GetTextureCount(aiTextureType_NORMALS));
			LoadTextureIntoMaterial(aiTextureType_EMISSIVE, material, &associatedMaterial, textureFolder, model);
		}

		//Load material color
		aiColor4D diffuse;
		if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
		{
			associatedMaterial.LoadVec3("color", diffuse.r, diffuse.g, diffuse.b);
		}
		else
			associatedMaterial.LoadVec3("color", 1,1,1);

	}
	else
	{
		//Logger::LogInfo("No material, applying default one {}", mesh->mMaterialIndex);
		associatedMaterial = Material(ContentManager::Instance().GetAsset<Shader>("ColorOnlyStatic"));
		associatedMaterial.LoadVec3("color", 1,0,1);

	}


	//if (scene->HasAnimations())
	//	associatedMaterial.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultAnimated"));

	int index = model->allMaterials.size();

	model->allMaterials[index] = associatedMaterial;
}

void AssimpWrapper::LoadMesh(aiMesh* mesh, Model* model, bool isanimated)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture2D> textures;
	std::vector<VertexBoneData> bones_id_weights_for_each_vertex;

	vertices.reserve(mesh->mNumVertices);
	indices.reserve(mesh->mNumVertices);

	bones_id_weights_for_each_vertex.resize(mesh->mNumVertices);

	//vertices
	for (unsigned i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 v;
		v.x = mesh->mVertices[i].x;
		v.y = mesh->mVertices[i].y;
		v.z = mesh->mVertices[i].z;
		vertex.position = v;

		if (mesh->mNormals != NULL)
		{
			v.x = mesh->mNormals[i].x;
			v.y = mesh->mNormals[i].y;
			v.z = mesh->mNormals[i].z;
			vertex.normal = v;
		}
		else
		{
			vertex.normal = glm::vec3();
		}


		// in assimp model can have 8 different texture coordinates
		// we only care about the first set of texture coordinates
		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.UV = vec;
		}
		else
		{
			vertex.UV = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}

	//indices
	for (unsigned i = 0; i < mesh->mNumFaces; i++)
	{

		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);

	}

//	if (isanimated)
	//	LoadBones(mesh, dynamic_cast<AnimatedModel*>(model), bones_id_weights_for_each_vertex);


	int index = model->allMeshes.size();

	Mesh* myMesh = new Mesh();

	myMesh->vertices = vertices;
	myMesh->indices = indices;
	myMesh->CalculateNormals();
	myMesh->bones_id_weights_for_each_vertex = bones_id_weights_for_each_vertex;
	myMesh->name = mesh->mName.C_Str();
	myMesh->InitializeVertexArray();
	model->allMeshes[index] = ContentManager::Instance().AddMesh(mesh->mName.C_Str(), myMesh, preserveTextures);
	model->meshesNames[index] = mesh->mName.C_Str();
	
}

void AssimpWrapper::LoadTextureIntoMaterial(aiTextureType type, aiMaterial* material, Material* mymaterial, std::string textureFolder, Model* model)
{
	std::string myUniform;
	std::string typeInString;

	switch (type)
	{
	case aiTextureType_DIFFUSE:
		myUniform = "diffuse0";
		typeInString = "Diffuse";
		break;
	case aiTextureType_NORMALS:
		myUniform = "normal0";
		typeInString = "Normal";

		break;
	case aiTextureType_EMISSIVE:
		myUniform = "emissive0";
		typeInString = "Emissive";

		break;
	case aiTextureType_SPECULAR:
		myUniform = "specular0";
		typeInString = "Specular";

		break;
	}

	for (int i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString assimpPath;
		material->GetTexture(type, i, &assimpPath);
		std::string fileNameOnly = FileUtils::GetFileNameFromAbsolutePath(assimpPath.C_Str());
		std::string finalPath = textureFolder + "\\" + fileNameOnly;
		std::string namerr = FileUtils::GetFileNameNoExtensionFromAbsolutePath(finalPath);

		Texture2D* alreadyThere = ContentManager::Instance().GetAsset<Texture2D>(namerr);

		if (alreadyThere)
		{
			mymaterial->Loadtexture(alreadyThere, myUniform);
			//Logger::LogInfo("Loaded from model (already loaded)", alreadyThere->name);
		}
		else
		{
			ContentManager::Instance().LoadTexture(finalPath, preserveTextures);
			mymaterial->Loadtexture(ContentManager::Instance().GetAsset<Texture2D>(namerr), myUniform);
			//Logger::LogInfo("Loaded from model", namerr);
		}

	}
}
/*
void AssimpWrapper::LoadBones(aiMesh* mesh, AnimatedModel* model, std::vector<VertexBoneData>& bones_id_weights_for_each_vertex)
{

	//Load bones
	for (unsigned i = 0; i < mesh->mNumBones; i++)
	{
		unsigned index = 0;
		std::string boneName = mesh->mBones[i]->mName.C_Str();

		auto b = model->myBoneMapping.find(boneName);


		if (b == model->myBoneMapping.end())
		{
			ModelBone bone;
			bone.index = model->totalBones;
			index = bone.index;
			model->totalBones++;

			bone.offsetMatrix = Maths::aiMatrix4x4ToGlm(mesh->mBones[i]->mOffsetMatrix);
			model->myBoneMapping[boneName] = bone;
		}
		else
			index = b->second.index;

		for (unsigned j = 0; j < mesh->mBones[i]->mNumWeights; j++)
		{
			unsigned vertex_id = mesh->mBones[i]->mWeights[j].mVertexId;
			float weight = mesh->mBones[i]->mWeights[j].mWeight;
			bones_id_weights_for_each_vertex[vertex_id].addBoneData(index, weight);


		}
	}
}
*/

/*void AssimpWrapper::LoadAnimations(const aiScene* scene, AnimatedModel* model)
{


	for (int i = 0; i < scene->mNumAnimations; i++)
	{
		ModelAnimation a;
		a.SetDuration(scene->mAnimations[i]->mDuration);
		a.animationName = scene->mAnimations[i]->mName.C_Str();
		a.ticksPerSecond = scene->mAnimations[i]->mTicksPerSecond;
		if (a.ticksPerSecond == 0)
			a.ticksPerSecond = 25.0f;

		//Load node animation info
		for (int anim = 0; anim < scene->mAnimations[i]->mNumChannels; anim++)
		{
			ModelNodeAnimationInfo animInfo;
			std::string nodeName = scene->mAnimations[i]->mChannels[anim]->mNodeName.C_Str();
			animInfo.actualNode = model->allNodes[nodeName];

			//Translation keys
			for (unsigned int k = 0; k < scene->mAnimations[i]->mChannels[anim]->mNumPositionKeys; k++)
			{
				double time = scene->mAnimations[i]->mChannels[anim]->mPositionKeys[k].mTime;
				glm::vec3 value = Maths::aiVector3ToGlm(scene->mAnimations[i]->mChannels[anim]->mPositionKeys[k].mValue);
				animInfo.translateKeys.push_back(TranslateKey(time, value));

			}

			//Scale keys
			for (unsigned int k = 0; k < scene->mAnimations[i]->mChannels[anim]->mNumScalingKeys; k++)
			{
				double time = scene->mAnimations[i]->mChannels[anim]->mScalingKeys[k].mTime;
				glm::vec3 value = Maths::aiVector3ToGlm(scene->mAnimations[i]->mChannels[anim]->mScalingKeys[k].mValue);
				animInfo.scaleKeys.push_back(ScaleKey(time, value));

			}

			//Rotation keys
			for (unsigned int k = 0; k < scene->mAnimations[i]->mChannels[anim]->mNumRotationKeys; k++)
			{
				double time = scene->mAnimations[i]->mChannels[anim]->mRotationKeys[k].mTime;
				glm::quat value = Maths::aiQuaternionToGlm(scene->mAnimations[i]->mChannels[anim]->mRotationKeys[k].mValue);
				animInfo.rotationKey.push_back(RotationKey(time, value));

			}


			a.allNodeAnimations[nodeName] = animInfo;
		}

		model->allAnimations.push_back(a);
	}
	//This one will move from here
	model->currentAnimation = &(model->allAnimations[0]);
}*/

