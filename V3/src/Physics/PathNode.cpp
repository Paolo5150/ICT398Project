#include "pch.h"
#include "PathNode.h"
#include "..\Components\BoxCollider.h"

PathNode::PathNode() : GameObject("PathNode")
{

	SetIsStatic(1);
	distanceFromPrevious = 0;
	distanceFromTarget = 0;
	cost = 0;
	totalCost = 0;
}
PathNode::~PathNode()
{
}


void PathNode::Start()
{
	bc = new BoxCollider();
	bc->ResetCollideAgainstLayer();
	bc->ResetCollisionLayer();
	bc->AddCollideAgainstLayer(CollisionLayers::DEFAULT);
	bc->AddCollisionLayer(CollisionLayers::PATHNODE);
	bc->transform.SetScale(2.5,2.5,2.5);
	cost = 0;
	totalCost = 0;
	lock = false;
	parentNode = nullptr;
	AddComponent(bc);

	GameObject::Start();
}


void PathNode::EngineUpdate()
{
	GameObject::EngineUpdate();
}

void PathNode::LateUpdate()
{

}

void PathNode::OnCollisionEnter(Collider* g, Collision& collision)
{
	//SetActive(0);
	bc->meshRenderer->GetMaterial().SetColor(1, 0, 0);
	cost = 1000;
	//Logger::LogInfo("Node collided against",go->GetName());
}


