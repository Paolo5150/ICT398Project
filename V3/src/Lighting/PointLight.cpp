#include "pch.h"

#include "PointLight.h"
#include "..\Components\MeshRenderer.h"
#include "..\Utils\ContentManager.h"
#include "..\Rendering\Material.h"

PointLight::PointLight() : Light("PointLight",POINT)
{

	intensity = 20.0f;
	lightType = POINT;

	GameObject* sphere = new GameObject("pointLight sphere");
	ContentManager::Instance().GetAsset<Model>("Sphere")->PopulateGameObject(sphere);

	Material mat;
	mat.SetShader(ContentManager::Instance().GetAsset<Shader>("ColorOnlyStatic"));
	mat.SetColor(diffuseColor.x, diffuseColor.y, diffuseColor.z);

	sphere->ApplyMaterial(mat);
	sphere->ApplyMaterial(mat,NOLIGHT);
	sphere->ApplyMaterial(mat,COLORONLY);
	AddChild(sphere);

}
PointLight::~PointLight()
{

}

