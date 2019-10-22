#include "pch.h"
#include "TestRamp.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"

TestRamp::TestRamp() : GameObject("TestRamp")
{
	SetIsStatic(1);
	ContentManager::Instance().GetAsset<Model>("TestRamp")->PopulateGameObject(this);
	transform.SetScale(0.55);
	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("PBR"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("TestRamp"), "albedoMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_normal"), "normalMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_roughness"), "roughnessMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_metallic"), "metallicMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("metal_ao"), "aoMap");
	m.LoadCubemap(ContentManager::Instance().GetAsset<CubeMap>("SunSet"), "cubemap0");

	Material mNoLight;
	mNoLight.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStaticNoLight"));
	mNoLight.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("TestRamp"), "diffuse0");

	ApplyMaterial(m);
	ApplyMaterial(mNoLight, NOLIGHT);
}

TestRamp::~TestRamp()
{

}

void TestRamp::Update()
{
	GameObject::Update();
}

void TestRamp::Start()
{

	LoadCollidersFromFile("Assets\\Colliders\\Fountain.txt");


	GameObject::Start(); //This will call start on all the object components, so it's better to leave it as last call when the collider
						 // has been added.
}

void TestRamp::OnCollisionEnter(Collider* g, Collision& collision)
{}
void TestRamp::OnCollisionStay(Collider* g, Collision& collision)
{}
