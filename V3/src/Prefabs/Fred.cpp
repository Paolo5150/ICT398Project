#include "pch.h"
#include "Fred.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Rigidbody.h"
#include "..\Components\AffordanceAgent.h"
#include "..\Affordances\RestAffordance.h"
#include "Dylan.h"
#include "..\Components\AIEmotion.h"
#include "..\Scene\SceneManager.h"

namespace
{
	AffordanceAgent* aa;
	AIEmotion* aiE;
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

/*	Dylan* d = new Dylan();
	AddChild(d);
	d->transform.SetScale(2.8);
	d->transform.SetRotation(-90, 0, 0);
	d->transform.SetPosition(0, 160, 20);*/

	billquad = new Billquad();
	//Adding the quad as a child is not a great idea, so I just add it as a separate GameObject and update in manually in the Update
	SceneManager::Instance().GetCurrentScene().AddGameObject(billquad);

	aa = new AffordanceAgent();

	aa->AddAffordanceEngageCallback("SitAffordance",[&](AffordanceObject*obj) {
		Logger::LogInfo("SitAffordance engaged");
		transform.SetPosition(obj->gameObject->transform.GetPosition() + glm::vec3(0, 1, 0));
	});

	aa->AddAffordanceUpdateCallback("SitAffordance", [&]() {
	});

	aa->AddAffordanceDisengageCallback("SitAffordance",[&]() {
		Logger::LogInfo("SitAffordance disengaged");

		transform.SetPosition(aa->selectedObj->gameObject->transform.GetPosition() - glm::vec3(0, 1, 0));
	});

	aa->AddAffordanceEngageCallback("LaydownAffordance",[&](AffordanceObject*obj) {
		Logger::LogInfo("LaydownAffordance engaged");
		transform.RotateBy(90, transform.GetLocalRight());
	});

	aa->AddAffordanceUpdateCallback("LaydownAffordance", [&]() {
	});

	aa->AddAffordanceDisengageCallback("LaydownAffordance", [&]() {
		Logger::LogInfo("LaydownAffordance disengaged");
		transform.RotateBy(-90, transform.GetLocalRight());
		billquad->SetTexture(ContentManager::Instance().GetAsset<Texture2D>("happy"));
		billquad->RenderForSeconds(2);
	});

	AddComponent(aa);

}

Fred::~Fred()
{

}

void Fred::Update()
{
	GameObject::Update();
	billquad->transform.SetPosition(transform.GetPosition() + glm::vec3(0, 12, 0));

	auto it = aiE->GetNeeds().begin();

	// Check for needs that are below their threshold
	for (; it != aiE->GetNeeds().end(); it++)
	{
		if (aiE->GetNeedValue(it->first) < it->second->GetLowSeekThreshold() || aiE->GetNeedValue(it->first) > it->second->GetHighSeekThreshold())
		{
			// If found one, check if there's a texture with the need's name
			Texture2D* t = ContentManager::Instance().GetAsset<Texture2D>(it->second->GetName());
			if (t)
			{
				//If there is, display the emotion
				billquad->SetTexture(t);
				billquad->RenderForSeconds(2,2);

			}
		}
	}

}

void Fred::Start()
{

	LoadCollidersFromFile("Assets\\Colliders\\Fred.txt");

	/*Rigidbody* rb = new Rigidbody();
	rb->UseGravity(true);

	AddComponent(rb);*/

	aiE = new AIEmotion();
	AddComponent(aiE);

	GameObject::Start(); //This will call start on all the object components, so it's better to leave it as last call when the collider
						 // has been added.
}

void Fred::OnCollisionEnter(Collider* g, Collision& collision)
{
	//
	if (g->GetParent()->GetName() == "Box")
	{
		AIEmotionManager::Instance().GenerateStimuli(Need::NeedType::Anger, Stimuli::StimuliType::Threat, 5.0, 1, 5.0, aiE);

	}

}

void Fred::OnCollisionExit(Collider* g)
{
	//Logger::LogInfo("Fred Collided EXIT against", g->GetName());

}
void Fred::OnCollisionStay(Collider* g, Collision& collision)
{
	//Logger::LogInfo("Fred Collided STAY against", g->GetName());

}

