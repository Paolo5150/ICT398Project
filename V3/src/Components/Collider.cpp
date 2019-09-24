#include "pch.h"
#include "Collider.h"
#include "..\Physics\PhysicsWorld.h"


Collider::Collider(std::string name) : Component(name){
	_type = "Collider";
	enableRender = 0;
	collisionLayer = CollisionLayers::DEFAULT;
	collideAgainstLayer = CollisionLayers::DEFAULT;
	OnCollisionEnterCallback = nullptr;
	OnCollisionStayCallback = nullptr;
	OnCollisionExitCallback = nullptr;
	cubicDimension = glm::vec3();

	mass = 1;
}


void Collider::EngineUpdate()
{
	if ( _isActive)
	{
		if (!_parent->GetIsStatic())
			PhysicsWorld::Instance().AddCollider(this);
		
		if (enableRender)
			meshRenderer->EngineUpdate();
	}
}

void Collider::Start()
{
	transform.UpdateHierarchy();
	if(_parent->GetIsStatic())
		PhysicsWorld::Instance().AddCollider(this);

	CalculateMomentOfIntertia();
	CalculateCubicDimensions();
}

void Collider::OnAttach(GameObject* go)
{
	transform.parent = &go->transform;
	go->transform.transformChildren.push_back(&transform);
	meshRenderer->transform = &transform;
	meshRenderer->SetParent(go);

	if(OnCollisionEnterCallback == nullptr)
		OnCollisionEnterCallback = std::bind(&GameObject::OnCollisionEnter, go, std::placeholders::_1, std::placeholders::_2);

	if (OnCollisionStayCallback == nullptr)
		OnCollisionStayCallback = std::bind(&GameObject::OnCollisionStay, go, std::placeholders::_1, std::placeholders::_2);

	if (OnCollisionExitCallback == nullptr)
		OnCollisionExitCallback = std::bind(&GameObject::OnCollisionExit, go, std::placeholders::_1);

	meshRenderer->AddPreRenderCallback([](Camera& cam, Shader* s){		
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);	
	});


	meshRenderer->AddPostRenderCallback([](Camera& cam, Shader* s){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);
	});

	Initialize();
	
	// Disable render
	enableRender = 0;
}


