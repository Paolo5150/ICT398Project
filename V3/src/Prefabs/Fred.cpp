#include "pch.h"
#include "Fred.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Rigidbody.h"
#include "..\Components\AffordanceAgent.h"
#include "..\Components\PathFinder.h"
#include "..\Affordances\RestAffordance.h"
#include "Dylan.h"
#include "..\Components\AIEmotion.h"
#include "..\Scene\SceneManager.h"

namespace
{
	AffordanceAgent* aa;
	AIEmotion* aiE;
	GameObject* player;
	PathFinder* pf;
	Rigidbody* rb;
	glm::vec3 nextPos;
}

void Fred::Test(AffordanceObject* obj)
{
	Logger::LogInfo("I'm sitting on", obj->gameObject->GetName());

}

Fred::Fred() : GameObject("Fred"), AffordanceObject(this)
{
	SetIsStatic(0);

	ContentManager::Instance().GetAsset<Model>("Fred")->PopulateGameObject(this);
	transform.SetScale(0.02);
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

	aa->AddAffordanceEngageCallback("SitAffordance", [&](AffordanceObject*obj) {
		Logger::LogInfo("SitAffordance engaged");
		transform.SetPosition(obj->gameObject->transform.GetPosition() + glm::vec3(0, 1, 0));
	});

	aa->AddAffordanceUpdateCallback("SitAffordance", [&]() {
	});

	aa->AddAffordanceDisengageCallback("SitAffordance", [&]() {
		Logger::LogInfo("SitAffordance disengaged");

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
		billquad->SetTexture(ContentManager::Instance().GetAsset<Texture2D>("happy"));
		billquad->RenderForSeconds(2);
	});

	aa->AddAffordanceEngageCallback("ThirstAffordance", [&](AffordanceObject*obj) {});
	aa->AddAffordanceUpdateCallback("ThirstAffordance", [&]() {});
	aa->AddAffordanceDisengageCallback("ThirstAffordance", [&]() {});

	aa->AddAffordanceEngageCallback("SocialAffordance", [&](AffordanceObject*obj) {});
	aa->AddAffordanceUpdateCallback("SocialAffordance", [&]() {});
	aa->AddAffordanceDisengageCallback("SocialAffordance", [&]() {});

	AddComponent(aa);


	LoadAffordancesFromFile("Assets\\Affordances\\people_affordances.txt");
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
				billquad->RenderForSeconds(2, 2);

			}
		}
	}

	if (aa->GetSelectedAffordanceName() != "" && aa->selectedObj != nullptr)
	{
		glm::vec3 targetPos = aa->selectedObj->gameObject->transform.GetGlobalPosition();

		if (!pf->HasPath() || !pf->IsLastNode(PathFindingManager::Instance().ClosestNodeAt(targetPos.x, targetPos.y, targetPos.z))) //If a path hasn't been generated yet, or the path does not lead to the target
		{
			pf->GeneratePath(transform.GetGlobalPosition(), targetPos);
			nextPos = pf->GetNextNodePos();
			nextPos.y = 0;
		}

		// Walk towards the affordance object
		if (glm::length(nextPos - transform.GetGlobalPosition()) > 3.0) //Travel to node
		{
			transform.RotateYTowards(nextPos);
			glm::vec3 move = glm::normalize(nextPos - transform.GetGlobalPosition()) * 4.0f;
			rb->SetRelativeVelocity(2.5, 0, 0);

		}
		else if (!pf->IsLastPos(nextPos)) //If this node is not the final node, get the next one
		{
			nextPos = pf->GetNextNodePos();
			nextPos.y = 0;
		}
		else
		{
			aa->ExecuteAffordanceEngageCallback(aa->GetSelectedAffordanceName(), aiE);
			rb->SetVelocity(0, 0, 0);
		}
	}
	else
	{
		if (aa->HasInUseObject())
		{
			aa->ExecuteAffordanceUpdateCallback(aa->GetSelectedAffordanceName(), aiE);
			pf->ClearPath();
		}
		else
		{
			if (!pf->HasPath())
			{
				bool success; //True when the path is generated successfully

				do //Get a random free node
				{
					glm::vec3 pos = PathFindingManager::Instance().GetRandomFreeNode();
					success = pf->GeneratePath(transform.GetGlobalPosition(), pos);
				} while (success == false);

				nextPos = pf->GetNextNodePos();
				nextPos.y = 0;
			}

			//Walk towards the wandering node
			if (glm::length(nextPos - transform.GetGlobalPosition()) > 3.0) //Travel to node
			{
				transform.RotateYTowards(nextPos);
				glm::vec3 move = glm::normalize(nextPos - transform.GetGlobalPosition()) * 4.0f;
				rb->SetRelativeVelocity(2.5, 0, 0);

			}
			else if (!pf->IsLastPos(nextPos)) //If this node is not the final node, get the next one
			{
				nextPos = pf->GetNextNodePos();
				nextPos.y = 0;
			}
			else
			{
				pf->ClearPath();
				rb->SetVelocity(0, 0, 0);
			}
		}
	}

	//NPCs GUI
	if (glm::length2(player->transform.GetPosition() - transform.GetPosition()) < 100)
		aiE->EnableRenderStats();
	else
		aiE->DisableRenderStats();
}

void Fred::Start()
{
	player = SceneManager::Instance().GetCurrentScene().GetGameobjectsByName("Main Camera")[0];
	LoadCollidersFromFile("Assets\\Colliders\\Fred.txt");

	rb = new Rigidbody();
	rb->UseGravity(0);
	rb->SetUseDynamicPhysics(1);
	rb->SetIgnoreRotation(1);

	AddComponent(rb);

	pf = new PathFinder();
	AddComponent(pf);

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
		AIEmotionManager::Instance().GenerateStimuli(Need::NeedType::Anger, Stimuli::StimuliType::Threat, 1.0, 1, 5.0, aiE);

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

