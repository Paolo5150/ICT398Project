#include "pch.h"
#include "Bench.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"

Bench::Bench() : GameObject("Bench")
{
	//SetIsStatic(false);
	ContentManager::Instance().GetAsset<Model>("Bench")->PopulateGameObject(this);
	transform.SetScale(0.08);

	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("PBR"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("iron_normal"), "normalMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("iron_albedo"), "albedoMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("iron_roughness"), "roughnessMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("iron_metallic"), "metallicMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("bamboo_ao"), "aoMap");
	m.LoadCubemap(ContentManager::Instance().GetAsset<CubeMap>("SunSet"), "cubemap0");
	ApplyMaterial(m);

}

Bench::~Bench()
{

}

void Bench::Update()
{
	GameObject::Update();
}

void Bench::Start()
{

	LoadCollidersFromFile("Assets\\Colliders\\Bench.txt");

	GameObject::Start(); //This will call start on all the object components, so it's better to leave it as last call when the collider
						 // has been added.
}

void Bench::OnCollision(GameObject* g, glm::vec3 collPoint)
{
	Logger::LogInfo("Collided against", g->GetName());
}