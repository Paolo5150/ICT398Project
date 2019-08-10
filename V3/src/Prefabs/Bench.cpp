#include "pch.h"
#include "Bench.h"
#include "..\Utils\ContentManager.h"

Bench::Bench() : GameObject("Bench")
{
	ContentManager::Instance().GetAsset<Model>("Bench")->PopulateGameObject(this);
	transform.SetScale(0.1);

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
	GameObject::Start();

}