#include "pch.h"
#include "PhysicsWorld.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\SphereCollider.h"
#include "..\Events\EventDispatcher.h"
#include "..\Events\ApplicationEvents.h"
#include <algorithm>


namespace
{

}

PhysicsWorld&  PhysicsWorld::Instance()
{
	static PhysicsWorld instance;
	return instance;
}


PhysicsWorld::PhysicsWorld()
{
	
	nonStaticQuadtree = nullptr;
	staticQuadtree = nullptr;

	EventDispatcher::Instance().SubscribeCallback<SceneChangedEvent>([this](Event* e){

		//Destroy quadtree
		nonStaticQuadtree.reset();
		staticQuadtree.reset();
		allNonStaticColliders.clear();
		allStaticColliders.clear();
		return 0;
	});

}

void PhysicsWorld::InitializeQuadtree(int x, int y, int w, int h)
{
	if (nonStaticQuadtree == nullptr)
		nonStaticQuadtree = std::unique_ptr<QuadTree<Collider*>>(new QuadTree<Collider*>(x, y, w, h));

	if (staticQuadtree == nullptr)
		staticQuadtree = std::unique_ptr<QuadTree<Collider*>>(new QuadTree<Collider*>(x, y, w, h));

}

void PhysicsWorld::FillQuadtree(bool staticToo)
{
	nonStaticQuadtree->ClearNodes();


	for (unsigned i = 0; i < allNonStaticColliders.size(); i++)
	{
		nonStaticQuadtree->AddElement(allNonStaticColliders[i], allNonStaticColliders[i]->transform.GetGlobalPosition().x, allNonStaticColliders[i]->transform.GetGlobalPosition().z,
			allNonStaticColliders[i]->transform.GetGlobalScale().x, allNonStaticColliders[i]->transform.GetGlobalScale().z);
	}	

	if (staticToo)
	{
		staticQuadtree->ClearNodes();

		for (unsigned i = 0; i < allStaticColliders.size(); i++)
		{
			staticQuadtree->AddElement(allStaticColliders[i], allStaticColliders[i]->transform.GetGlobalPosition().x, allStaticColliders[i]->transform.GetGlobalPosition().z,
				allStaticColliders[i]->transform.GetGlobalScale().x, allStaticColliders[i]->transform.GetGlobalScale().z);
		}

	}
}

PhysicsWorld::~PhysicsWorld()
{
	if (nonStaticQuadtree != nullptr)
	{
		nonStaticQuadtree->ClearNodes();
	}

	if (nonStaticQuadtree != nullptr)
	{
		staticQuadtree->ClearNodes();
	}
}

void PhysicsWorld::AddCollider(Collider* rb)
{
	if (!rb->GetParent()->GetIsStatic())
		allNonStaticColliders.push_back(rb);
	else
	{
		allStaticColliders.push_back(rb);
	}
}

void PhysicsWorld::Update()
{
	if (nonStaticQuadtree && staticQuadtree)
	{
		FillQuadtree(0);
		PerformCollisions(false);
		allNonStaticColliders.clear();
	}

	//collisionMap.clear(); // Clear collision map each frame!
}

void PhysicsWorld::PerformCollisions(bool staticToo)
{
	//Logger::LogInfo("STARTING COLLISION UPDATE");
	PerformCollisions(nonStaticQuadtree->root);
	
	// Collision between static vs non static
	for (unsigned i = 0; i < allNonStaticColliders.size(); i++)
	{
		std::unordered_set<Collider*>& staticCols = staticQuadtree->GameObjectsAt(allNonStaticColliders[i]->transform.GetGlobalPosition().x, allNonStaticColliders[i]->transform.GetGlobalPosition().z);
		
		for (auto it = staticCols.begin(); it != staticCols.end(); it++)
		{
			if (allNonStaticColliders[i]->GetCollideAgainstLayer() & (*it)->GetCollisionLayer() ||
				(*it)->GetCollideAgainstLayer() & allNonStaticColliders[i]->GetCollisionLayer())
			{
				if ((*it)->GetActive() && allNonStaticColliders[i]->GetActive())
				{			
						if (CollisionChecks::Collision(allNonStaticColliders[i], (*it)))
						{			
							//TODO: Calculate collision point.
							//allNonStaticColliders[i]->collisionCallback((*it)->GetParent());				
							//(*it)->collisionCallback(allNonStaticColliders[i]->GetParent());
					
						}				
				}
			}
		}
		
	}

	if (staticToo)
		PerformCollisions(staticQuadtree->root);

	//Logger::LogInfo("ENDING COLLISION UPDATE");

}

glm::vec3 PhysicsWorld::gravity = glm::vec3(0, -9.8, 0);

bool PhysicsWorld::WereGameObjectsColliding(GameObject* obj1, GameObject* obj2)
{
	auto it = collisionMap.find(obj1);

	if (it != collisionMap.end())
	{
		auto other = it->second.find(obj2);

		if (other != it->second.end())
			return true;
	}

	it = collisionMap.find(obj2);
	if (it != collisionMap.end())
		{
		auto other = it->second.find(obj1);

		if (other != it->second.end())
			return true;
		}

	return false;

}

bool PhysicsWorld::WereCollidersColliding(Collider* obj1, Collider* obj2)
{
	auto it = collidersMap.find(obj1);

	if (it != collidersMap.end())
	{
		if (std::find(it->second.begin(), it->second.end(), obj2) != it->second.end())
			return true;
	}

	it = collidersMap.find(obj2);

	if (it != collidersMap.end())
	{
		if (std::find(it->second.begin(), it->second.end(), obj1) != it->second.end())
			return true;
	}

	return false;
}

void PhysicsWorld::PerformCollisions(QuadNode<Collider*>* node)
{
	if (node->isSplit)
	{
		PerformCollisions(node->topLeft);
		PerformCollisions(node->topRight);
		PerformCollisions(node->bottomLeft);
		PerformCollisions(node->bottomRight);
	}
	else
	{
		auto it = node->elements.begin();

		for (; it != node->elements.end(); it++)
		{
			auto it2 = node->elements.begin();

			for (; it2 != node->elements.end(); it2++)
			{
				if (*it == *it2) continue;
				if ((*it)->GetCollideAgainstLayer() & (*it2)->GetCollisionLayer())
				{
					if ((*it)->GetActive() && (*it2)->GetActive())
					{					
						// Check that the colliders do not belong to the same GameObject
						if ((*it)->GetParent() != (*it2)->GetParent())
						{
							if (CollisionChecks::Collision((*it), (*it2)))
							{		
							
								// Check if colliders were colliding
								if (!WereCollidersColliding((*it), (*it2)))
								{
									collidersMap[(*it)].push_back(*it2);
									collidersMap[(*it2)].push_back(*it);

									if (!WereGameObjectsColliding((*it)->GetParent(), (*it2)->GetParent()))
									{
										(*it)->OnCollisionEnterCallback((*it2));
										(*it2)->OnCollisionEnterCallback((*it));

										collisionMap[(*it)->GetParent()][(*it2)->GetParent()] = 1;
										collisionMap[(*it2)->GetParent()][(*it)->GetParent()] = 1;
									}
									else
									{
										(*it)->OnCollisionStayCallback((*it2));
										(*it2)->OnCollisionStayCallback((*it));
										collisionMap[(*it)->GetParent()][(*it2)->GetParent()]++;
										collisionMap[(*it2)->GetParent()][(*it)->GetParent()]++;									
									
									}
								}	
								else
								{
									(*it)->OnCollisionStayCallback((*it2));
									(*it2)->OnCollisionStayCallback((*it));
								}
							}
							else
							{
								if (WereCollidersColliding((*it), (*it2)))
								{
									auto colIt1 = collidersMap.find((*it));

									for (auto collidersAgainst = colIt1->second.begin(); collidersAgainst != colIt1->second.end(); collidersAgainst++)
									{
										if (*collidersAgainst == (*it2))
										{
											colIt1->second.erase(collidersAgainst);
											break;
										}
									}

									auto colIt2 = collidersMap.find((*it2));

									for (auto collidersAgainst = colIt2->second.begin(); collidersAgainst != colIt2->second.end(); collidersAgainst++)
									{
										if (*collidersAgainst == (*it))
										{
											colIt2->second.erase(collidersAgainst);
											break;
										}
									}


									collisionMap[(*it)->GetParent()][(*it2)->GetParent()]--;
									collisionMap[(*it2)->GetParent()][(*it)->GetParent()]--;

									if (collisionMap[(*it)->GetParent()][(*it2)->GetParent()] == 0)
									{
										(*it)->OnCollisionExitCallback((*it2));

										auto mapIt = collisionMap.find((*it)->GetParent());
										mapIt->second.erase((*it2)->GetParent());
									}

									if (collisionMap[(*it2)->GetParent()][(*it)->GetParent()] == 0)
									{

										(*it2)->OnCollisionExitCallback((*it));
										auto mapIt = collisionMap.find((*it2)->GetParent());
										mapIt->second.erase((*it)->GetParent());
									}
								}
							}
						}
					
					}		
				}
			}
		}
	}
}




