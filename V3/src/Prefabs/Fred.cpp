#include "pch.h"
#include "Fred.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Rigidbody.h"
#include "..\Components\AffordanceAgent.h"
#include "..\Components\PathFinder.h"
#include "..\Affordances\RestAffordance.h"
#include "Dylan.h"

namespace
{
	AffordanceAgent* aa;
	float timer = 0;
	bool needToSit = 1;
	PathFinder* pf;
	glm::vec3 nextPos;
}

void Fred::Test(AffordanceObject* obj)
{
	Logger::LogInfo("I'm sitting on", obj->gameObject->GetName());

}

Fred::Fred() : GameObject("Fred")
{
	SetIsStatic(0);

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

	Dylan* d = new Dylan();
	AddChild(d);
	d->transform.SetScale(2.8);
	d->transform.SetRotation(-90, 0, 0);
	d->transform.SetPosition(0, 160, 20);

	aa = new AffordanceAgent();

	aa->AddAffordanceEngageCallback("SitAffordance", [&](AffordanceObject*obj) {
		Logger::LogInfo("SitAffordance engaged");
		transform.SetPosition(obj->gameObject->transform.GetPosition() + glm::vec3(0, 1, 0));
	});

	aa->AddAffordanceDisengageCallback("SitAffordance", [&]() {
		Logger::LogInfo("SitAffordance disengaged");

		transform.SetPosition(aa->selectedObj->gameObject->transform.GetPosition() - glm::vec3(0, 1, 0));
	});

	aa->AddAffordanceEngageCallback("LaydownAffordance", [&](AffordanceObject*obj) {
		Logger::LogInfo("LaydownAffordance engaged");
		transform.RotateBy(90, transform.GetLocalRight());
	});

	aa->AddAffordanceDisengageCallback("LaydownAffordance", [&]() {
		Logger::LogInfo("LaydownAffordance disengaged");

		transform.RotateBy(-90, transform.GetLocalRight());

	});

	AddComponent(aa);
	timer = 0;
	needToSit = 1;
}

Fred::~Fred()
{

}

void Fred::Update()
{
	GameObject::Update();


	timer += Timer::GetDeltaS();

	if (timer > 7 && needToSit)
	{
		if (aa->LookForBestScoreAffordanceObjectByAffordanceTypeInRange(Affordance::AffordanceTypes::REST, 100))
		{
			// If the method is true, we have found an affordance object in the specified range
			// That would be pointed by "selectedObj" in the Affordance Agent

			if (!pf->HasPath())
			{
				pf->GeneratePath(transform.GetGlobalPosition(), aa->selectedObj->gameObject->transform.GetGlobalPosition());
				nextPos = pf->GetNextNodePos();
			}

			glm::vec3 toObj = aa->selectedObj->gameObject->transform.GetGlobalPosition() - transform.GetGlobalPosition();

			double dist = sqrt(pow(nextPos.x - transform.GetPosition().x, 2) + pow(nextPos.y - transform.GetPosition().y, 2) + pow(nextPos.z - transform.GetPosition().z, 2));

			// Walk towards the affordance object
			if (dist > 2.5)
			{

				glm::vec3 toTarget = nextPos - transform.GetGlobalPosition();
				float angle = glm::degrees(glm::angle(transform.GetLocalFront(), toTarget));
				int cross = glm::sign(glm::cross(transform.GetLocalFront(), toTarget)).y;
				transform.RotateBy(angle * cross, 0, 1, 0);

				glm::vec3 move = glm::normalize(nextPos - transform.GetGlobalPosition()) * Timer::GetDeltaS() * 4.0f;
				transform.Translate(move);

			}
			else if (!pf->IsLastPos(nextPos))
			{
				nextPos = pf->GetNextNodePos();
			}
			else
			{
				// When close enough enage it
				aa->ExecuteAffordanceEngageCallback(aa->GetSelectedAffordanceName());
			}
		}
	}
	if (timer > 40)
	{
		// After a while, just disengage the affordance object (this would trigger when the need to sit is no longer active)
		aa->ExecuteAffordanceDisengageCallback(aa->GetSelectedAffordanceName());
		needToSit = 0;

		Logger::LogInfo("Should disengage");
	}

}

void Fred::Start()
{

	//LoadCollidersFromFile("Assets\\Colliders\\Fred.txt");

	/*Rigidbody* rb = new Rigidbody();
	rb->UseGravity(true);

	AddComponent(rb);*/

	pf = new PathFinder();
	AddComponent(pf);

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

