#include "pch.h"
#include "DrinkingFountain.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Diag\DiagRenderer.h"
#include "..\Affordances\RestAffordance.h"

DrinkingFountain::DrinkingFountain() : GameObject("DrinkingFountain"), AffordanceObject(this)
{
	SetIsStatic(1);
	ContentManager::Instance().GetAsset<Model>("Fountain")->PopulateGameObject(this);
	transform.SetScale(0.55);
	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("PBR"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("Fountain"), "albedoMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_normal"), "normalMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_roughness"), "roughnessMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_metallic"), "metallicMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_ao"), "aoMap");
	m.LoadCubemap(ContentManager::Instance().GetAsset<CubeMap>("SunSet"), "cubemap0");

	Material mNoLight;
	mNoLight.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStaticNoLight"));
	mNoLight.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("Fountain"), "diffuse0");

	ApplyMaterial(m);
	ApplyMaterial(mNoLight, NOLIGHT);

	LoadAffordancesFromFile("Assets\\Affordances\\fountain_affordances.txt");
}

DrinkingFountain::~DrinkingFountain()
{

}

void DrinkingFountain::Update()
{
	GameObject::Update();
}

void DrinkingFountain::Start()
{

	LoadCollidersFromFile("Assets\\Colliders\\Fountain.txt");


	GameObject::Start(); //This will call start on all the object components, so it's better to leave it as last call when the collider
						 // has been added.
}

void DrinkingFountain::OnCollisionEnter(Collider* g, Collision& collision)
{}
void DrinkingFountain::OnCollisionStay(Collider* g, Collision& collision)
{}
