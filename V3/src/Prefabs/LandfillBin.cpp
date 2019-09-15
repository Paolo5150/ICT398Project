#include "pch.h"
#include "LandfillBin.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Rigidbody.h"

LandfillBin::LandfillBin() : GameObject("LandfillBin")
{
	SetIsStatic(false);
	ContentManager::Instance().GetAsset<Model>("LandfillBin")->PopulateGameObject(this);
	transform.SetScale(2);

	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("PBR"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("LB_Frame"), "albedoMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_normal"), "normalMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_roughness"), "roughnessMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_metallic"), "metallicMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_ao"), "aoMap");
	m.LoadCubemap(ContentManager::Instance().GetAsset<CubeMap>("SunSet"), "cubemap0");

	Material m1NoLight;
	m1NoLight.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStaticNoLight"));
	m1NoLight.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("LB_Frame"), "diffuse0");


	Material m2;
	m2.SetShader(ContentManager::Instance().GetAsset<Shader>("PBR"));
	m2.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("LB_Sides"), "albedoMap");
	m2.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_normal"), "normalMap");
	m2.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_roughness"), "roughnessMap");
	m2.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_metallic"), "metallicMap");
	m2.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_ao"), "aoMap");
	m2.LoadCubemap(ContentManager::Instance().GetAsset<CubeMap>("SunSet"), "cubemap0");

	Material m2NoLight;
	m2NoLight.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStaticNoLight"));
	m2NoLight.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("LB_Sides"), "diffuse0");
	
	GetChild(0)->ApplyMaterial(m);
	GetChild(0)->ApplyMaterial(m1NoLight,NOLIGHT);

	GetChild(1)->ApplyMaterial(m2);
	GetChild(1)->ApplyMaterial(m2NoLight, NOLIGHT);

}

LandfillBin::~LandfillBin()
{

}

void LandfillBin::Update()
{
	GameObject::Update();
}

void LandfillBin::Start()
{

	LoadCollidersFromFile("Assets\\Colliders\\LandfillBin.txt");

	rb = new Rigidbody();
	rb->UseGravity(false);
	rb->SetVelocity(1.0,0, 0);
	rb->SetUseDynamicPhysics(false);
	AddComponent(rb);

	GameObject::Start(); //This will call start on all the object components, so it's better to leave it as last call when the collider
						 // has been added.
}

void LandfillBin::OnCollisionEnter(Collider* g, Collision& col)
{
	//Logger::LogInfo("LandfillBin ENTER collision with", g->GetParent()->name);
	rb->AddVelocity(-rb->GetVelocity());
}
void LandfillBin::OnCollisionStay(Collider* g, Collision& col)
{
	//Logger::LogInfo("LandfillBin STAY collision with", g->GetParent()->name);
}

void LandfillBin::OnCollisionExit(Collider* g)
{
	//Logger::LogInfo("LandfillBin EXIT collision with", g->GetParent()->name);
}