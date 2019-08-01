#include "pch.h"
#include "SphereCollider.h"
#include "..\Utils\ContentManager.h"

void SphereCollider::InitializeMeshRenderer()
{
	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("ColorOnlyStatic"));
	m.SetColor(0, 1, 0);

	Mesh* mesh = ContentManager::Instance().GetAsset<Model>("Sphere")->GetMeshes()[0];

	meshRenderer = std::unique_ptr<MeshRenderer>(new MeshRenderer(mesh, m));

}

void SphereCollider::Update()
{
	Collider::Update();
}


