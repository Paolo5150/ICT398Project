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

	collisionMap.clear();
}

void PhysicsWorld::PerformCollisions(bool staticToo)
{
	Logger::LogInfo("STARTING COLLISION UPDATE");
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

	Logger::LogInfo("ENDING COLLISION UPDATE");

}

glm::vec3 PhysicsWorld::gravity = glm::vec3(0, -9.8, 0);

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
						auto mapIt = collisionMap.find((*it));

						if (mapIt != collisionMap.end())
						{
							// If they have collided already in this frame, skip!
							if (std::find(mapIt->second.begin(), mapIt->second.end(), *it2) != mapIt->second.end())
							{
								continue;
							}
						}
				
						if (CollisionChecks::Collision((*it), (*it2)))
						{							// Check that the colliders do not belong to the same GameObject
							if ((*it)->GetParent() != (*it2)->GetParent())
							{

								// Check if they were in collisions before, if not, call onCollisionEnter
								if (std::find((*it)->collidersInCollision.begin(), (*it)->collidersInCollision.end(), (*it2)) == (*it)->collidersInCollision.end())
								{
									(*it)->OnCollisionEnterCallback((*it2)->GetParent());
									(*it2)->OnCollisionEnterCallback((*it)->GetParent());

									(*it)->collidersInCollision.push_back((*it2));
									(*it2)->collidersInCollision.push_back((*it));
								}
								else
								{									
									(*it)->OnCollisionStayCallback((*it2)->GetParent());
									(*it2)->OnCollisionStayCallback((*it)->GetParent());

									// Update collision map
									collisionMap[*it].push_back(*it2);
									collisionMap[*it2].push_back(*it);


								}
							}
						}
						else
						{
							if (std::find((*it)->collidersInCollision.begin(), (*it)->collidersInCollision.end(), (*it2)) != (*it)->collidersInCollision.end())
							{
								(*it)->collidersInCollision.remove((*it2));
								(*it2)->collidersInCollision.remove((*it));

								(*it)->OnCollisionExitCallback((*it2)->GetParent());
								(*it2)->OnCollisionExitCallback((*it)->GetParent());
							}

						}
					}		
				}
			}
		}
	}
}




