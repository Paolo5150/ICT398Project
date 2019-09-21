#include "pch.h"
#include "Fred.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Rigidbody.h"
#include "..\Components\AffordanceAgent.h"
#include "..\Affordances\RestAffordance.h"

namespace
{
	AffordanceAgent* aa;
}

void Fred::Test(AffordanceObject* obj)
{
	Logger::LogInfo("I'm sitting on", obj->gameObject->GetName());

}

Fred::Fred() : GameObject("Fred")
{
	SetIsStatic(1);
	ContentManager::Instance().GetAsset<Model>("Fred")->PopulateGameObject(this);
	transform.SetScale(0.03);
	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStatic"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("Fred_Base_Color"), "diffuse0");
	m.SetColor(0.5, 0.5, 0.5);
	ApplyMaterial(m);

	Material m2NoLight;
	m2NoLight.SetShader(ContentManager::Instance().GetAsset<Shader>("DefaultStaticNoLight"));
	m2NoLight.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("Fred_Base_Color"), "diffuse0");
	m2NoLight.SetColor(0.5, 0.5, 0.5);

	ApplyMaterial(m2NoLight, NOLIGHT);

	aa = new AffordanceAgent();
	aa->AddAffordanceEngageCallback<SitAffordance>([&](AffordanceObject*obj) {
	
		transform.SetPosition(obj->gameObject->transform.GetPosition() + glm::vec3(0, 1, 0));
	});

	aa->AddAffordanceDisengageCallback<SitAffordance>([&]() {

		transform.SetPosition(aa->selectedObj->gameObject->transform.GetPosition() - glm::vec3(0, 1, 0));
	});

	AddComponent(aa);

}

Fred::~Fred()
{

}

void Fred::Update()
{
	GameObject::Update();

	static float timer = 0;
	static bool done = 0;
	timer += Timer::GetDeltaS();

	if (timer > 7 && !done)
	{
	
		if (aa->selectedObj == nullptr)
		{
		std::vector<AffordanceObject*> objs = AffordanceManager::Instance().GetObjectsOfTypeWithinRange<SitAffordance>(transform.GetGlobalPosition(),30);
		aa->selectedObj = objs[0];
		}
		else
		{
			glm::vec3 toObj = aa->selectedObj->gameObject->transform.GetGlobalPosition() - transform.GetGlobalPosition();

			if (glm::length2(toObj) < 1.0)
			{
				transform.Translate(glm::normalize(toObj) * Timer::GetDeltaS() * 2.0f);
			}
			else
			{
				aa->ExecuteAffordanceEngageCallback<SitAffordance>(aa->selectedObj);
				done = 1;
			}
		}
	}
	else if (timer > 20)
	{
		aa->ExecuteAffordanceDisengageCallback<SitAffordance>();
		Logger::LogInfo("Should disengage");
	}




}

void Fred::Start()
{

	//LoadCollidersFromFile("Assets\\Colliders\\Fred.txt");

	/*Rigidbody* rb = new Rigidbody();
	rb->UseGravity(true);

	AddComponent(rb);*/
	GameObject::Start(); //This will call start on all the object components, so it's better to leave it as last call when the collider
						 // has been added.
}

void Fred::OnCollisionEnter(Collider* g, Collision& collision)
{
	Logger::LogInfo("Fred Collided ENTER against", g->GetName());

}

void Fred::OnCollisionExit(Collider* g)
{
	Logger::LogInfo("Fred Collided EXIT against", g->GetName());

}
void Fred::OnCollisionStay(Collider* g, Collision& collision)
{
	//Logger::LogInfo("Fred Collided STAY against", g->GetName());

}

