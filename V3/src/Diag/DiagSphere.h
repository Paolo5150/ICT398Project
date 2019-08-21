#pragma once
#include "DiagPrefab.h"


class DiagSphere : public DiagPrefab
{
public:
	DiagSphere(glm::vec3 pos, float scale , glm::vec3 color)
	{
		Mesh* m = ContentManager::Instance().GetAsset<Model>("Sphere")->GetMeshes()[0]; //This is some seriously bad code!
		Material mat;
		material.SetShader(ContentManager::Instance().GetAsset<Shader>("ColorOnlyStatic"));
		meshRenderer = std::unique_ptr<MeshRenderer>(new MeshRenderer(m, material));
	}
};