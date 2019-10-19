#include "pch.h"
#include "Joey.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Rigidbody.h"
#include "..\Components\AffordanceAgent.h"
#include "..\Affordances\RestAffordance.h"
#include "Dylan.h"
#include "..\Scene\SceneManager.h"


namespace
{
	AffordanceAgent* aa;
	GameObject* player;
	AIEmotion* aiE;


}

void Joey::Test(AffordanceObject* obj)
{
	Logger::LogInfo("I'm sitting on", obj->gameObject->GetName());

}

Joey::Joey() : GameObject("Joey")
{
	SetIsStatic(0);

	ContentManager::Instance().GetAsset<Model>("Joey")->PopulateGameObject(this);
	transform.SetScale(0.02);
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

	billquad = new Billquad();

	//Adding the quad as a child is not a great idea, so I just add it as a separate GameObject and update in manually in the Update
	SceneManager::Instance().GetCurrentScene().AddGameObject(billquad);
	aa = new AffordanceAgent();
	AddComponent(aa);
	aa->AddAffordanceEngageCallback("LaydownAffordance", [&](AffordanceObject*obj) {
		//Logger::LogInfo("LaydownAffordance engaged");
		transform.RotateBy(90, transform.GetLocalRight());
	});

	aa->AddAffordanceUpdateCallback("LaydownAffordance", [&]() {
	});

	aa->AddAffordanceDisengageCallback("LaydownAffordance", [&]() {
		//Logger::LogInfo("LaydownAffordance disengaged"); 
		transform.RotateBy(-90, transform.GetLocalRight());
	});


}

Joey::~Joey()
{

}

void Joey::Update()
{
	GameObject::Update();
	billquad->transform.SetPosition(transform.GetPosition() + glm::vec3(0, 8, 0));

	billquad->CheckEmotions(aiE);

	//NPCs GUI
	if(glm::length2(player->transform.GetPosition() - transform.GetPosition()) < 50)
		aiE->EnableRenderStats();
	else
		aiE->DisableRenderStats();

}

void Joey::Start()
{
	player = SceneManager::Instance().GetCurrentScene().GetGameobjectsByName("Main Camera")[0];

	LoadCollidersFromFile("Assets\\Colliders\\Joey.txt");

	aiE = new AIEmotion();
	AddComponent(aiE);
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

