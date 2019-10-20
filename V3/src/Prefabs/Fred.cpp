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
	GameObject* player;
	AIEmotion* aiE;
	PathFinder* pf;
	Rigidbody* rb;
	glm::vec3 nextPos; //Next position to navigate to
	float timer = 0; //Used to regenerate path every now and then
	AffordanceObject* pathAffordanceObject; //Which affordance the current path is made from
	bool waiting = false; //Waiting while wandering
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

	billquad = new Billquad();
	//Adding the quad as a child is not a great idea, so I just add it as a separate GameObject and update in manually in the Update
	SceneManager::Instance().GetCurrentScene().AddGameObject(billquad);

	aa = new AffordanceAgent();

	aa->AddAffordanceEngageCallback("SitAffordance", [&](AffordanceObject*obj) {
		//Logger::LogInfo("SitAffordance engaged");
		transform.SetPosition(obj->gameObject->transform.GetPosition() + glm::vec3(0, 1, 0));
	});

	aa->AddAffordanceUpdateCallback("SitAffordance", [&]() {
	});

	aa->AddAffordanceDisengageCallback("SitAffordance", [&]() {
		//Logger::LogInfo("Fred SitAffordance disengaged");

		transform.SetPosition(aa->selectedObj->gameObject->transform.GetPosition() - glm::vec3(2, 1, 0));
	});

	aa->AddAffordanceEngageCallback("LaydownAffordance", [&](AffordanceObject*obj) {
		//Logger::LogInfo("Fred LaydownAffordance engaged");
		transform.RotateBy(90, transform.GetLocalRight());
		glm::vec3 pos = obj->gameObject->transform.GetGlobalPosition();
		pos.y += 1;
		transform.SetPosition(pos);
	});

	aa->AddAffordanceUpdateCallback("LaydownAffordance", [&]() {
		//Logger::LogInfo("Fred LaydownAffordance update");

	});

	aa->AddAffordanceDisengageCallback("LaydownAffordance", [&]() {
		//Logger::LogInfo("Fred LaydownAffordance disengaged");
		transform.RotateBy(-90, transform.GetLocalRight());
		transform.SetPosition(aa->selectedObj->gameObject->transform.GetPosition()  + aa->selectedObj->gameObject->transform.GetLocalFront() * 8.0f);


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
	billquad->transform.SetPosition(transform.GetPosition() + glm::vec3(0, 8, 0));

	billquad->CheckEmotions(aiE);

	Move();

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

void Fred::Move()
{
	if (aa->GetSelectedAffordanceName() != "" && aa->selectedObj != nullptr && !aa->HasInUseObject()) //If there is an affordance to move to
	{
		glm::vec3 targetPos = aa->selectedObj->gameObject->transform.GetGlobalPosition();
		glm::vec3 toObj = aa->selectedObj->gameObject->transform.GetGlobalPosition() - aa->GetParent()->transform.GetGlobalPosition();

		if (!pf->HasPath() || !pf->IsLastNode(PathFindingManager::Instance().ClosestNodeAt(targetPos.x, targetPos.y, targetPos.z)) || (Timer::GetTimeS() - timer) > 5 || aa->selectedObj != pathAffordanceObject) //If a path hasn't been generated yet, or the path does not lead to the target, or the timer has 'elapsed'
		{
			waiting = false;
			rb->SetActive(true);
			pf->GeneratePath(transform.GetGlobalPosition(), targetPos, true);
			nextPos = pf->GetNextNodePos();
			timer = Timer::GetTimeS();
			pathAffordanceObject = aa->selectedObj;
		}

		if (glm::length2(toObj) > 50)
		{
			// Walk towards the affordance object
			if (glm::length(nextPos - transform.GetGlobalPosition()) > 2.5) //Travel to node
			{
				//Get direction to rotate toward, (similar code as RotateYToward)
				glm::vec3 toTarget = nextPos - transform.GetGlobalPosition();
				int cross = 0;
				float angle = glm::degrees(glm::angle(transform.GetLocalFront(), toTarget));
				if (!(fabs(angle) < 1.0)) //Tolerance
					cross = glm::sign(glm::cross(transform.GetLocalFront(), toTarget)).y;

				glm::vec3 move = glm::normalize(nextPos - transform.GetGlobalPosition()) * 4.0f;

				rb->SetVelocity(move);
				rb->SetAngularVelocity(0, (angle * cross) * 2, 0);
			}
			else if (!pf->IsLastPos(nextPos)) //If this node is not the final node, get the next one
			{
				nextPos = pf->GetNextNodePos();
			}
		}
		else
		{
			aa->ExecuteAffordanceEngageCallback(aa->GetSelectedAffordanceName(), aiE);
			rb->SetVelocity(0, 0, 0);
			rb->SetActive(false); //Turn off rigidbody so people can't push agent around
		}
	}
	else
	{
		if (aa->HasInUseObject())
		{
			//aa->ExecuteAffordanceUpdateCallback(aa->GetSelectedAffordanceName(), aiE);
		}
		else
		{
			if (!waiting)
			{
				if (!pf->HasPath() || (Timer::GetTimeS() - timer) > 20)
				{
					rb->SetActive(true);
					glm::vec3 pos = PathFindingManager::Instance().GetRandomFreeNode();
					pf->GeneratePath(transform.GetGlobalPosition(), pos);

					nextPos = pf->GetNextNodePos();

					timer = Timer::GetTimeS();
				}

				//Walk towards the wandering node
				if (glm::length(nextPos - transform.GetGlobalPosition()) > 2.5) //Travel to node
				{
					//Get direction to rotate toward, (similar code as RotateYToward)
					glm::vec3 toTarget = nextPos - transform.GetGlobalPosition();
					int cross = 0;
					float angle = glm::degrees(glm::angle(transform.GetLocalFront(), toTarget));
					if (!(fabs(angle) < 1.0)) //Tolerance
						cross = glm::sign(glm::cross(transform.GetLocalFront(), toTarget)).y;

					glm::vec3 move = glm::normalize(nextPos - transform.GetGlobalPosition()) * 4.0f;

					rb->SetVelocity(move);
					rb->SetAngularVelocity(0, (angle * cross) * 2, 0);
				}
				else if (!pf->IsLastPos(nextPos)) //If this node is not the final node, get the next one
				{
					nextPos = pf->GetNextNodePos();
				}
				else
				{
					waiting = true;
					timer = Timer::GetTimeS();
					pf->ClearPath();
					rb->SetVelocity(0, 0, 0);
				}
			}
			else if ((Timer::GetTimeS() - timer) > 5)
			{
				waiting = false;
			}
		}
	}
}