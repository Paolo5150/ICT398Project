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


void BoxCollider::CalculateMomentOfIntertia()
{

	glm::vec3 min = GetMinPoint();
	glm::vec3 max = GetMaxPoint();

	float a = abs(max.y - min.y);
	float b = abs(max.x - min.x);
	float l = abs(max.z - min.z);
	
	momentOfIntertia.x = (1 / 12.0f) * mass * (a * a + l * l);
	momentOfIntertia.y = (1 / 12.0f) * mass * (b * b + l * l);
	momentOfIntertia.z = (1 / 12.0f) * mass * (a * a + b * b);

	Logger::LogInfo("Intertia:", Maths::Vec3ToString(momentOfIntertia));

}
