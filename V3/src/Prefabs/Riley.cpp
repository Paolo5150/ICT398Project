#include "pch.h"
#include "Riley.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Rigidbody.h"
#include "..\Components\AffordanceAgent.h"
#include "..\Affordances\RestAffordance.h"

namespace
{
	AffordanceAgent* aa;
	float timer = 0;
	bool needToSit = 1;
}

void Riley::Test(AffordanceObject* obj)
{
	Logger::LogInfo("I'm sitting on", obj->gameObject->GetName());

}

Riley::Riley() : GameObject("Riley")
{
	SetIsStatic(0);
	ContentManager::Instance().GetAsset<Model>("Riley")->PopulateGameObject(this);
	transform.SetScale(0.03);
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
		Logger::LogInfo("LaydownAffordance engaged");
		transform.RotateBy(90, transform.GetLocalRight());
	});

	aa->AddAffordanceUpdateCallback("LaydownAffordance", [&]() {
	});

	aa->AddAffordanceDisengageCallback("LaydownAffordance", [&]() {
		Logger::LogInfo("LaydownAffordance disengaged"); 
		transform.RotateBy(-90, transform.GetLocalRight());
	});
		

	AddComponent(aa);
	timer = 0;
	needToSit = 1;

}

Riley::~Riley()
{

}

void Riley::Update()
{
	GameObject::Update();

	/*
	timer += Timer::GetDeltaS();
	
	if (timer > 7 && needToSit)
	{
		if (aa->LookForBestScoreAffordanceObjectInRange("SitAffordance",40))
		{
			glm::vec3 toObj = aa->selectedObj->gameObject->transform.GetGlobalPosition() - transform.GetGlobalPosition();

			if (glm::length2(toObj) > 0.1)
			{
				transform.Translate(glm::normalize(toObj) * Timer::GetDeltaS() * 4.0f);
				transform.RotateYTowards(aa->selectedObj->gameObject->transform.GetGlobalPosition());
			}
			else
			{
				aa->ExecuteAffordanceEngageCallback("SitAffordance", ai);
			}
		}
	}
	if (timer > 50)
	{
		aa->ExecuteAffordanceDisengageCallback("SitAffordance");
		needToSit = 0;
	}
	*/
}

void Riley::Start()
{

	//LoadCollidersFromFile("Assets\\Colliders\\Riley.txt");

	/*Rigidbody* rb = new Rigidbody();
	rb->UseGravity(true);

	AddComponent(rb);*/

	AIEmotion* aiE = new AIEmotion();
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

