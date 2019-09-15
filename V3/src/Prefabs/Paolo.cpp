#include "pch.h"
#include "Paolo.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Rigidbody.h"

Paolo::Paolo() : GameObject("Paolo")
{
	SetIsStatic(false);
	ContentManager::Instance().GetAsset<Model>("Paolo")->PopulateGameObject(this);
	transform.SetScale(2);

	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStatic"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("paolo"));
	m.LoadFloat("shininess", 400.0f);

	Material m1NoLight;
	m1NoLight.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStaticNoLight"));
	m1NoLight.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("paolo"), "diffuse0");

	ApplyMaterial(m);
	ApplyMaterial(m1NoLight,NOLIGHT);

	transform.SetRotation(-90, 0, 0);


}

Paolo::~Paolo()
{

}

void Paolo::Update()
{
	GameObject::Update();
}



