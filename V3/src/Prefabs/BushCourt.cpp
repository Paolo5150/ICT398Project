#include "pch.h"
#include "BushCourt.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"

BushCourt::BushCourt() : GameObject("BushCourt")
{
	SetIsStatic(true);
	ContentManager::Instance().GetAsset<Model>("BushCourt")->PopulateGameObject(this);
	//transform.SetScale(1.5);
	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStatic"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("BushCourt"), "diffuse0");
	m.LoadFloat("shininess", 300.0f);

	m.LoadCubemap(ContentManager::Instance().GetAsset<CubeMap>("SunSet"), "cubemap0");
	ApplyMaterial(m);

	Material m2NoLight;
	m2NoLight.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStaticNoLight"));
	m2NoLight.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("BushCourt"), "diffuse0");
	ApplyMaterial(m2NoLight, NOLIGHT);

}

BushCourt::~BushCourt()
{

}

void BushCourt::Update()
{
	GameObject::Update();
}

void BushCourt::Start()
{

	LoadCollidersFromFile("Assets\\Colliders\\BushCourt.txt");

	GameObject::Start(); //This will call start on all the object components, so it's better to leave it as last call when the collider
						 // has been added.
}

void BushCourt::OnCollisionEnter(Collider* g)
{}
void BushCourt::OnCollisionStay(Collider* g)
{}