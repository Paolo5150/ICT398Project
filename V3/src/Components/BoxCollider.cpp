#include "pch.h"
#include "BoxCollider.h"
#include "..\Utils\ContentManager.h"

void BoxCollider::InitializeMeshRenderer()
{
	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("ColorOnlyStatic"));
	m.SetColor(0, 1, 0);

	Mesh* mesh = ContentManager::Instance().GetAsset<Model>("Cube")->GetMeshes()[0];

	meshRenderer = std::unique_ptr<MeshRenderer>(new MeshRenderer(mesh, m));
}

void BoxCollider::Update()
{
	Collider::Update();
}


glm::vec3 BoxCollider::GetMinPoint()
{

	glm::vec3 p = transform.GetGlobalPosition() - (transform.GetLocalRight() * transform.GetGlobalScale().x)
		- (transform.GetLocalUp() * transform.GetGlobalScale().y)
		- (transform.GetLocalFront() * transform.GetGlobalScale().z);

	return p;
}

glm::vec3 BoxCollider::GetMaxPoint()
{

	glm::vec3 p = transform.GetGlobalPosition() + (transform.GetLocalRight() * transform.GetGlobalScale().x)
		+ (transform.GetLocalUp() * transform.GetGlobalScale().y)
		+ (transform.GetLocalFront() * transform.GetGlobalScale().z);

	return p;
}


