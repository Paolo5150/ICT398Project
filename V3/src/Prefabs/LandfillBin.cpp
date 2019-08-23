#include "pch.h"
#include "LandfillBin.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Rigidbody.h"

LandfillBin::LandfillBin() : GameObject("LandfillBin")
{
	//SetIsStatic(false);
	ContentManager::Instance().GetAsset<Model>("LandfillBin")->PopulateGameObject(this);
	transform.SetScale(2);

	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("PBR"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("LB_Frame"), "albedoMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_normal"), "normalMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_roughness"), "roughnessMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_metallic"), "metallicMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_ao"), "aoMap");
	m.LoadCubemap(ContentManager::Instance().GetAsset<CubeMap>("SunSet"), "cubemap0");

	Material m2;
	m2.SetShader(ContentManager::Instance().GetAsset<Shader>("PBR"));
	m2.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("LB_Sides"), "albedoMap");
	m2.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_normal"), "normalMap");
	m2.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_roughness"), "roughnessMap");
	m2.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_metallic"), "metallicMap");
	m2.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_ao"), "aoMap");
	m2.LoadCubemap(ContentManager::Instance().GetAsset<CubeMap>("SunSet"), "cubemap0");
	
	GetChild(0)->ApplyMaterial(m);
	GetChild(1)->ApplyMaterial(m2);



	PrintHierarchy();

}

LandfillBin::~LandfillBin()
{

}

void LandfillBin::Update()
{
	GameObject::Update();
}

void LandfillBin::Start()
{

	LoadCollidersFromFile("Assets\\Colliders\\LandfillBin.txt");

	GameObject::Start(); //This will call start on all the object components, so it's better to leave it as last call when the collider
						 // has been added.
}

void LandfillBin::OnCollision(GameObject* g)
{
	//Logger::LogInfo("Collided against", g->GetName());
}