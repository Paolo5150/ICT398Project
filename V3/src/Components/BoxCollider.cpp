#include "pch.h"
#include "BoxCollider.h"
#include "..\Utils\ContentManager.h"
#include "..\Diag\DiagRenderer.h"

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

	CalculateCubicDimensions(); // For dynamic objet, it should be recalculated every frame

	// Debug
	/*glm::vec3 min;
	glm::vec3 max;
	GetWorldCubicMinMaxPoint(min, max);
	DiagRenderer::Instance().RenderSphere(min, 0.5,glm::vec3(0));
	DiagRenderer::Instance().RenderSphere(max, 0.5);*/

}

void BoxCollider::GetWorldCubicMinMaxPoint(glm::vec3& min, glm::vec3& max)
{

	std::vector<glm::vec3> points = GetBoxPoints();	
	min = max = points[0];

	for (int i = 0; i < points.size(); i++)
	{
		if (points[i].x < min.x)
			min.x = glm::vec3(points[i]).x;
		if (points[i].y < min.y)
			min.y = glm::vec3(points[i]).y;
		if (points[i].z< min.z)
			min.z = glm::vec3(points[i]).z;

		if (points[i].x > max.x)
			max.x = glm::vec3(points[i]).x;
		if (points[i].y > max.y)
			max.y = glm::vec3(points[i]).y;
		if (points[i].z > max.z)
			max.z = glm::vec3(points[i]).z;
	}
}


void BoxCollider::CalculateCubicDimensions()
{
	//transform.UpdateHierarchy();
	glm::vec3 min;
	glm::vec3 max;
	GetWorldCubicMinMaxPoint(min, max);

	this->cubicDimension.x = abs(max.x - min.x);
	this->cubicDimension.y = abs(max.y - min.y);
	this->cubicDimension.z = abs(max.z - min.z);
}

std::vector<glm::vec3> BoxCollider::GetBoxPoints()
{
	std::vector<glm::vec3> result;
	glm::vec3 right = transform.GetLocalRight() * transform.GetGlobalScale().x;
	glm::vec3 front = transform.GetLocalFront() * transform.GetGlobalScale().z;
	glm::vec3 up = transform.GetLocalUp() * transform.GetGlobalScale().y;


	result.push_back(transform.GetGlobalPosition() - right - up - front);
	result.push_back(transform.GetGlobalPosition() + right - up - front);
	result.push_back(transform.GetGlobalPosition() - right + up - front);
	result.push_back(transform.GetGlobalPosition() + right + up - front);
	result.push_back(transform.GetGlobalPosition() - right - up + front);
	result.push_back(transform.GetGlobalPosition() + right - up + front);
	result.push_back(transform.GetGlobalPosition() - right + up + front);
	result.push_back(transform.GetGlobalPosition() + right + up + front);

	/*for (int i = 0; i < result.size(); i++)
		DiagRenderer::Instance().RenderSphere(result[i], 0.5);*/

	return result;

}



glm::vec3 BoxCollider::GetMinPointWorldSpace()
{

	glm::vec3 p = transform.GetGlobalPosition() - (transform.GetLocalRight() * transform.GetGlobalScale().x)
		- (transform.GetLocalUp() * transform.GetGlobalScale().y)
		- (transform.GetLocalFront() * transform.GetGlobalScale().z);

	//DiagRenderer::Instance().RenderSphere(p, 0.5,glm::vec3(0,0,0));


	return p;
}

glm::vec3 BoxCollider::GetMaxPointWorldSpace()
{

	glm::vec3 p = transform.GetGlobalPosition() + (transform.GetLocalRight() * transform.GetGlobalScale().x)
		+ (transform.GetLocalUp() * transform.GetGlobalScale().y)
		+ (transform.GetLocalFront() * transform.GetGlobalScale().z);
	//DiagRenderer::Instance().RenderSphere(p, 0.5);

	return p;
}


void BoxCollider::CalculateMomentOfIntertia()
{

	glm::vec3 min = GetMinPointWorldSpace();
	glm::vec3 max = GetMaxPointWorldSpace();

	float a = abs(max.y - min.y);
	float b = abs(max.x - min.x);
	float l = abs(max.z - min.z);
	
	momentOfIntertia.x = (1 / 12.0f) * mass * (a * a + l * l);
	momentOfIntertia.y = (1 / 12.0f) * mass * (b * b + l * l);
	momentOfIntertia.z = (1 / 12.0f) * mass * (a * a + b * b);

	//Logger::LogInfo("Intertia:", Maths::Vec3ToString(momentOfIntertia));

}
