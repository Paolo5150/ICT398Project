#include "pch.h"
#include "RecycleBin.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Rigidbody.h"

RecycleBin::RecycleBin() : GameObject("RecycleBin")
{
	SetIsStatic(1);
	ContentManager::Instance().GetAsset<Model>("RecycleBin")->PopulateGameObject(this);
	transform.SetScale(2);

	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("PBR"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("RB_Frame"), "albedoMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_normal"), "normalMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_roughness"), "roughnessMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_metallic"), "metallicMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_ao"), "aoMap");
	m.LoadCubemap(ContentManager::Instance().GetAsset<CubeMap>("SunSet"), "cubemap0");

	Material m2;
	m2.SetShader(ContentManager::Instance().GetAsset<Shader>("PBR"));
	m2.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("RB_Sides"), "albedoMap");
	m2.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_normal"), "normalMap");
	m2.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_roughness"), "roughnessMap");
	m2.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_metallic"), "metallicMap");
	m2.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_ao"), "aoMap");
	m2.LoadCubemap(ContentManager::Instance().GetAsset<CubeMap>("SunSet"), "cubemap0");

	GetChild(1)->ApplyMaterial(m);
	GetChild(0)->ApplyMaterial(m2);
}

RecycleBin::~RecycleBin()
{

}

void RecycleBin::Update()
{
	GameObject::Update();
}

void RecycleBin::Start()
{

	LoadCollidersFromFile("Assets\\Colliders\\RecycleBin.txt");

	GameObject::Start(); //This will call start on all the object components, so it's better to leave it as last call when the collider
						 // has been added.
}

void RecycleBin::OnCollisionEnter(Collider* g)
{
	Logger::LogInfo("Recycle bin ENTER collision with", g->GetParent()->name);
}
void RecycleBin::OnCollisionStay(Collider* g)
{
	//Logger::LogInfo("Recycle bin STAY collision with", g->GetParent()->name);
}

void RecycleBin::OnCollisionExit(Collider* g)
{
	Logger::LogError("Recycle bin EXIT collision with", g->GetParent()->name);
}