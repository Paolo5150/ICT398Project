#include "pch.h"
#include "Table.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Diag\DiagRenderer.h"

Table::Table() : GameObject("Table")
{
	SetIsStatic(1);
	ContentManager::Instance().GetAsset<Model>("Table")->PopulateGameObject(this);
	transform.SetScale(0.1);
	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("PBR"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("bamboo_normal"), "normalMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("bamboo_albedo"), "albedoMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("bamboo_roughness"), "roughnessMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("bamboo_ao"), "aoMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("bamboo_metallic"), "metallicMap");


	m.LoadCubemap(ContentManager::Instance().GetAsset<CubeMap>("SunSet"), "cubemap0");
	ApplyMaterial(m);

	Material m2NoLight;
	m2NoLight.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStaticNoLight"));
	m2NoLight.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("bamboo_albedo"), "diffuse0");
	ApplyMaterial(m2NoLight, NOLIGHT);

}

Table::~Table()
{

}

void Table::Update()
{
	GameObject::Update();
}

void Table::Start()
{

	LoadCollidersFromFile("Assets\\Colliders\\Table.txt");


	GameObject::Start(); //This will call start on all the object components, so it's better to leave it as last call when the collider
						 // has been added.
}

void Table::OnCollisionEnter(Collider* g, Collision& collision)
{}
void Table::OnCollisionStay(Collider* g, Collision& collision)
{}
