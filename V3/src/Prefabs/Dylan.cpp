#include "pch.h"
#include "Dylan.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Rigidbody.h"

Dylan::Dylan() : GameObject("Dylan")
{
	SetIsStatic(false);
	ContentManager::Instance().GetAsset<Model>("Sonic")->PopulateGameObject(this);
	transform.SetScale(20);

	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStatic"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("paolo"));
	m.LoadFloat("shininess", 500);

	Material m1NoLight;
	m1NoLight.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStaticNoLight"));
	m1NoLight.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("paolo"), "diffuse0");

	ApplyMaterial(m);
	ApplyMaterial(m1NoLight, NOLIGHT);

	//transform.SetRotation(-90, 0, 0);



}

Dylan::~Dylan()
{

}

void Dylan::Update()
{
	GameObject::Update();
}



