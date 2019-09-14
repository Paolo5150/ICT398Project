#include "pch.h"
#include "Lantern.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Rigidbody.h"
#include "..\Lighting\PointLight.h"

Lantern::Lantern() : GameObject("Lantern")
{
	SetIsStatic(false);
	ContentManager::Instance().GetAsset<Model>("Lantern")->PopulateGameObject(this);


	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStatic"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("Lantern"));
	m.LoadFloat("shininess", 400.0f);

	Material m1NoLight;
	m1NoLight.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStaticNoLight"));
	m1NoLight.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("Lantern"), "diffuse0");

	ApplyMaterial(m);
	ApplyMaterial(m1NoLight, NOLIGHT);
	//transform.SetRotation(-90, 0, 0);

	PointLight* pl = new PointLight();
	pl->transform.SetPosition(0, 1, 0);
	pl->SetIntensity(10);

	AddChild(pl);
}


void Lantern::Start()
{
	LoadCollidersFromFile("Assets\\Colliders\\Lantern.txt");


	Rigidbody* rb = new Rigidbody();
	rb = new Rigidbody();
	rb->UseGravity(true);
	rb->SetVelocity(1.0,0, 0);
	AddComponent(rb);
}


Lantern::~Lantern()
{

}




