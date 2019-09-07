#include "pch.h"
#include "Dylan.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Rigidbody.h"

Dylan::Dylan() : GameObject("Dylan")
{
	SetIsStatic(false);
	ContentManager::Instance().GetAsset<Model>("Dylan")->PopulateGameObject(this);
	transform.SetScale(2);

	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStatic"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("Dylan"));
	m.LoadFloat("shininess", 500);

	Material m1NoLight;
	m1NoLight.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStaticNoLight"));
	m1NoLight.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("Dylan"), "diffuse0");

	ApplyMaterial(m);
	ApplyMaterial(m1NoLight, NOLIGHT);

}

Dylan::~Dylan()
{

}

void Dylan::Update()
{
	GameObject::Update();
}



