#include "pch.h"
#include "Joey.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Rigidbody.h"
#include "..\Components\AffordanceAgent.h"
#include "..\Affordances\RestAffordance.h"
#include "Dylan.h"

namespace
{
	AffordanceAgent* aa;
	float timer = 0;
	bool needToSit = 1;
}

void Joey::Test(AffordanceObject* obj)
{
	Logger::LogInfo("I'm sitting on", obj->gameObject->GetName());

}

Joey::Joey() : GameObject("Joey")
{
	SetIsStatic(0);

	ContentManager::Instance().GetAsset<Model>("Joey")->PopulateGameObject(this);
	transform.SetScale(0.03);
	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStatic"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("Joey_Base_Color"), "diffuse0");
	m.SetColor(0.5, 0.5, 0.5);
	ApplyMaterial(m);

	Material m2NoLight;
	m2NoLight.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStaticNoLight"));
	m2NoLight.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("Joey_Base_Color"), "diffuse0");
	m2NoLight.SetColor(0.5, 0.5, 0.5);

	ApplyMaterial(m2NoLight, NOLIGHT);

}

Joey::~Joey()
{

}

void Joey::Update()
{
	GameObject::Update();
}

void Joey::Start()
{

	//LoadCollidersFromFile("Assets\\Colliders\\Joey.txt");

	/*Rigidbody* rb = new Rigidbody();
	rb->UseGravity(true);

	AddComponent(rb);*/
	GameObject::Start(); //This will call start on all the object components, so it's better to leave it as last call when the collider
						 // has been added.
}

void Joey::OnCollisionEnter(Collider* g, Collision& collision)
{
	Logger::LogInfo("Joey Collided ENTER against", g->GetName());

}

void Joey::OnCollisionExit(Collider* g)
{
	Logger::LogInfo("Joey Collided EXIT against", g->GetName());

}
void Joey::OnCollisionStay(Collider* g, Collision& collision)
{
	//Logger::LogInfo("Joey Collided STAY against", g->GetName());

}

