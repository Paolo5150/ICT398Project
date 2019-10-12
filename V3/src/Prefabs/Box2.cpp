#include "pch.h"
#include "Box2.h"
#include "..\Utils\ContentManager.h"
#include "..\Diag\DiagRenderer.h"

Box2::Box2() : GameObject("Box"), AffordanceObject(this)
{
	SetIsStatic(false);
	ContentManager::Instance().GetAsset<Model>("Cube")->PopulateGameObject(this);

	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("PBR"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("wood_normal"), "normalMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("wood_albedo"), "albedoMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("wood_roughness"), "roughnessMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("wood_metallic"), "metallicMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("wood_ao"), "aoMap");
	m.LoadCubemap(ContentManager::Instance().GetAsset<CubeMap>("SunSet"), "cubemap0");
	ApplyMaterial(m);

	Material m2NoLight;
	m2NoLight.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStaticNoLight"));
	m2NoLight.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("wood_albedo"), "diffuse0");
	ApplyMaterial(m2NoLight, NOLIGHT);

	rb = new Rigidbody();
	AddComponent(rb);
	rb->UseGravity(1);
	rb->SetUseDynamicPhysics(1);


}

Box2::~Box2()
{

}

void Box2::Update()
{
	GameObject::Update();

	
}

void Box2::Start()
{
	//PrintHierarchy();
	LoadCollidersFromFile("Assets\\Colliders\\Box2.txt");
	LoadAffordancesFromFile("Assets\\Affordances\\box_affordances.txt");
	GameObject::Start(); //This will call start on all the object components, so it's better to leave it as last call when the collider
						 // has been added.
}

void Box2::OnCollisionEnter(Collider* g, Collision& col)
{
	//Logger::LogInfo("Box enter");

}

void Box2::OnCollisionExit(Collider* g)
{

}


void Box2::OnCollisionStay(Collider * g, Collision& col)
{
	//Logger::LogInfo("Stay:", rb->GetVelocity().y);
	/*if (rb->GetVelocity().y < 0 && col.Point().y <  GetCentreOfMass().y)
	{
		rb->SetVelocity(rb->GetVelocity().x, 0.0f, rb->GetVelocity().z);
		rb->awake = 0;
	}*/

}


