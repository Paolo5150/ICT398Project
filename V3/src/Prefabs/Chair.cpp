#include "pch.h"
#include "Chair.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Rigidbody.h"

Chair::Chair() : GameObject("Chair")
{
	SetIsStatic(1);
	ContentManager::Instance().GetAsset<Model>("Chair")->PopulateGameObject(this);
	transform.SetScale(1.5);
	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("PBR"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("wood_normal"), "normalMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("wood_albedo"), "albedoMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("wood_roughness"), "roughnessMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("wood_metallic"), "metallicMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("wood_ao"), "aoMap");
	m.LoadCubemap(ContentManager::Instance().GetAsset<CubeMap>("SunSet"), "cubemap0");
	ApplyMaterial(m);

}

Chair::~Chair()
{

}

void Chair::Update()
{
	GameObject::Update();
}

void Chair::Start()
{

	LoadCollidersFromFile("Assets\\Colliders\\Chair2.txt");

	/*Rigidbody* rb = new Rigidbody();
	rb->UseGravity(true);

	AddComponent(rb);*/
	GameObject::Start(); //This will call start on all the object components, so it's better to leave it as last call when the collider
						 // has been added.
}

void Chair::OnCollisionEnter(Collider* g)
{
	Logger::LogInfo("CHAIR Collided ENTER against", g->GetName());

}

void Chair::OnCollisionExit(Collider* g)
{
	Logger::LogInfo("CHAIR Collided EXIT against", g->GetName());

}
void Chair::OnCollisionStay(Collider* g)
{
	Logger::LogInfo("CHAIR Collided STAY against", g->GetName());

}

