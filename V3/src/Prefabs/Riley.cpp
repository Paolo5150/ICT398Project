#include "pch.h"
#include "Riley.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Rigidbody.h"
#include "..\Components\AffordanceAgent.h"
#include "..\Affordances\RestAffordance.h"
#include "..\Scene\SceneManager.h"

namespace
{
	AffordanceAgent* aa;
	GameObject* player;
	AIEmotion* aiE;

}

void Riley::Test(AffordanceObject* obj)
{
	Logger::LogInfo("I'm sitting on", obj->gameObject->GetName());

}

Riley::Riley() : GameObject("Riley"), AffordanceObject(this)
{
	SetIsStatic(0);
	ContentManager::Instance().GetAsset<Model>("Riley")->PopulateGameObject(this);
	transform.SetScale(0.02);
	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStatic"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("Riley_Base_Color"), "diffuse0");
	m.SetColor(0.5, 0.5, 0.5);
	ApplyMaterial(m);

	Material m2NoLight;
	m2NoLight.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStaticNoLight"));
	m2NoLight.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("Riley_Base_Color"), "diffuse0");
	m2NoLight.SetColor(0.5, 0.5, 0.5);

	ApplyMaterial(m2NoLight, NOLIGHT);

	billquad = new Billquad();

	//Adding the quad as a child is not a great idea, so I just add it as a separate GameObject and update in manually in the Update
	SceneManager::Instance().GetCurrentScene().AddGameObject(billquad);

	aa = new AffordanceAgent();
	aa->AddAffordanceEngageCallback("SitAffordance",[&](AffordanceObject*obj) {

		transform.SetPosition(obj->gameObject->transform.GetPosition() + glm::vec3(0, 1, 0));
	});

	aa->AddAffordanceUpdateCallback("SitAffordance", [&]() {
	});

	aa->AddAffordanceDisengageCallback("SitAffordance",[&]() {

		transform.SetPosition(aa->selectedObj->gameObject->transform.GetPosition() - glm::vec3(0, 1, 0));
	});

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


	aa->AddAffordanceEngageCallback("SocialAffordance", [&](AffordanceObject*obj) {});
	aa->AddAffordanceUpdateCallback("SocialAffordance", [&]() {});
	aa->AddAffordanceDisengageCallback("SocialAffordance", [&]() {});
		

	AddComponent(aa);


	LoadAffordancesFromFile("Assets\\Affordances\\people_affordances.txt");

}

Riley::~Riley()
{

}

void Riley::Update()
{
	GameObject::Update();
	billquad->transform.SetPosition(transform.GetPosition() + glm::vec3(0, 8, 0));

	billquad->CheckEmotions(aiE);

	//NPCs GUI
	if (glm::length2(player->transform.GetPosition() - transform.GetPosition()) < 100)
		aiE->EnableRenderStats();
	else
		aiE->DisableRenderStats();
}

void Riley::Start()
{
	player = SceneManager::Instance().GetCurrentScene().GetGameobjectsByName("Main Camera")[0];

	LoadCollidersFromFile("Assets\\Colliders\\Riley.txt");

	/*Rigidbody* rb = new Rigidbody();
	rb->UseGravity(true);

	AddComponent(rb);*/

	aiE = new AIEmotion("Riley", "depressive");
	AddComponent(aiE);

	GameObject::Start(); //This will call start on all the object components, so it's better to leave it as last call when the collider
						 // has been added.
}

void Riley::OnCollisionEnter(Collider* g, Collision& collision)
{
	Logger::LogInfo("Riley Collided ENTER against", g->GetName());

}

void Riley::OnCollisionExit(Collider* g)
{
	Logger::LogInfo("Riley Collided EXIT against", g->GetName());

}
void Riley::OnCollisionStay(Collider* g, Collision& collision)
{
	//Logger::LogInfo("Riley Collided STAY against", g->GetName());

}

