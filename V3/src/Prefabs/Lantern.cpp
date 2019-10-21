#include "pch.h"
#include "Lantern.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Rigidbody.h"
#include "..\Lighting\PointLight.h"

Lantern::Lantern() : GameObject("Lantern"), AffordanceObject(this)
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
	pl->transform.SetPosition(0, 3, 0);
	pl->SetIntensity(10);

	AddChild(pl);

	LoadAffordancesFromFile("Assets\\Affordances\\lantern_affordances.txt");
	GetPerceivedAffordances()[0]->setMaxUsers(100);

}


void Lantern::Start()
{
	LoadCollidersFromFile("Assets\\Colliders\\Lantern.txt");


	 rb = new Rigidbody();
	rb = new Rigidbody();
	rb->UseGravity(0);
	AddComponent(rb);
}

void Lantern::Update()
{
	GameObject::Update();
	static float min = 5000;

	min = glm::length(rb->GetVelocity()) < min ? glm::length(rb->GetVelocity()) : min;

	//Logger::LogInfo("Min Vel",glm::length(rb->GetVelocity()));


}


Lantern::~Lantern()
{

}




