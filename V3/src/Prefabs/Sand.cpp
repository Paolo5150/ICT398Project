#include "pch.h"
#include "Sand.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"

Sand::Sand() : GameObject("Sand")
{
	SetIsStatic(true);
	ContentManager::Instance().GetAsset<Model>("Sand")->PopulateGameObject(this);

	SetCullable(false);
	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStatic"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("Sand"));
	m.LoadFloat("shininess", 400.0f);
	m.SetColor(0.5, 0.5, 0.5);
	ApplyMaterial(m);

	Material m2NoLight;
	m2NoLight.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStaticNoLight"));
	m2NoLight.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("Sand"), "diffuse0");
	ApplyMaterial(m2NoLight, NOLIGHT);

}

Sand::~Sand()
{

}

void Sand::Update()
{
	GameObject::Update();
}

void Sand::Start()
{
	GameObject::Start(); //This will call start on all the object components, so it's better to leave it as last call when the collider
						 // has been added.
}
