#pragma once
#include "..\Core\Logger.h"
#include "..\Rendering\Mesh.h"
#include "..\Rendering\Texture2D.h"
#include "..\Rendering\Model.h"
//#include "..\Rendering\AnimatedModel.h"
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"

#include <vector>
#include <string>
#include <map>

class AssimpWrapper
{
public:
	Model* LoadModel(const std::string& folderAndFilename, bool LoadTextures,bool preserve);
	void ProcessNode(aiNode* node, const aiScene* scene, ModelNode* parentNode, Model* model, bool isAnimated);
	void ProcessMesh(aiMesh* mesh, const aiScene* scene, Model* model, bool isAnimated);

private:
	//void LoadBones(aiMesh* mesh, AnimatedModel* model, std::vector<VertexBoneData>& bones_id_weights_for_each_vertex);
	void LoadMesh(aiMesh* mesh, Model* model, bool isanimated);

	//void LoadAnimations(const aiScene* scene, AnimatedModel* model);
	void LoadTextureIntoMaterial(aiTextureType type, aiMaterial* material, Material* mymaterial, std::string textureFolder, Model* model);
	bool preserveTextures;
};
