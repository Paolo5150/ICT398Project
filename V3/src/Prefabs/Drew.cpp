#include "pch.h"
#include "Drew.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Rigidbody.h"

Drew::Drew() : GameObject("Drew")
{
	SetIsStatic(false);
	ContentManager::Instance().GetAsset<Model>("Drew")->PopulateGameObject(this);
	transform.SetScale(2);

	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStatic"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("drew"));
	m.LoadFloat("shininess", 400.0f);

	Material m1NoLight;
	m1NoLight.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStaticNoLight"));
	m1NoLight.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("drew"), "diffuse0");

	ApplyMaterial(m);
	ApplyMaterial(m1NoLight, NOLIGHT);

	transform.SetRotation(-90, 0, 0);



}

Drew::~Drew()
{

}

void Drew::Update()
{
	GameObject::Update();
}



