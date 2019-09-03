#include "pch.h"
#include "PhysicsWorld.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\SphereCollider.h"
#include "..\Events\EventDispatcher.h"
#include "..\Events\ApplicationEvents.h"
#include <algorithm>


#define CHANGE_COLOR 1

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
		gameObjectCollisionMap.clear();
		collidersCollisionMap.clear();
		collidersCollisionMapPerFrame.clear();
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
		//Logger::LogInfo("Adding", allNonStaticColliders[i]->GetParent()->name);
		nonStaticQuadtree->AddElement(allNonStaticColliders[i], allNonStaticColliders[i]->transform.GetGlobalPosition().x, allNonStaticColliders[i]->transform.GetGlobalPosition().z,
			allNonStaticColliders[i]->cubicDimension.x, allNonStaticColliders[i]->cubicDimension.z);
	}	

	if (staticToo)
	{
		staticQuadtree->ClearNodes();

		for (unsigned i = 0; i < allStaticColliders.size(); i++)
		{
			staticQuadtree->AddElement(allStaticColliders[i], allStaticColliders[i]->transform.GetGlobalPosition().x, allStaticColliders[i]->transform.GetGlobalPosition().z,
				allStaticColliders[i]->cubicDimension.x, allStaticColliders[i]->cubicDimension.z);
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
		collidersCollisionMapPerFrame.clear(); // Clear collision map each frame!

		FillQuadtree(0);

		PerformCollisions(false);

		allNonStaticColliders.clear();
	}

}

bool PhysicsWorld::WereCollidingThisFrame(Collider* c1, Collider* c2)
{
	// Check if they have been checked for collision this frame
	// Prevents multiple callbacks per single frame
	{
		auto firstOne = collidersCollisionMapPerFrame.find(c1);
		if (firstOne != collidersCollisionMapPerFrame.end())
		{
			if (std::find(firstOne->second.begin(), firstOne->second.end(), c2) != firstOne->second.end())
				return true;
		}
	}

	{
		auto firstOne = collidersCollisionMapPerFrame.find(c2);
		if (firstOne != collidersCollisionMapPerFrame.end())
		{
			if (std::find(firstOne->second.begin(), firstOne->second.end(), c1) != firstOne->second.end())
				return true;
		}
	}

	return false;
	
}


void PhysicsWorld::PerformCollisions(bool staticToo)
{
	/*static int done = 0;
	if (done == 0)
	{
	Logger::LogWarning("STARTING COLLISION UPDATE");
	done = 1;
	}*/

	// Collision between non static vs non static
	PerformCollisions(nonStaticQuadtree->root);
	
	// Collision between static vs non static
	for (unsigned i = 0; i < allNonStaticColliders.size(); i++)
	{
		std::unordered_set<Collider*>& p1 = staticQuadtree->GameObjectsAt(allNonStaticColliders[i]->transform.GetGlobalPosition().x + allNonStaticColliders[i]->cubicDimension.x * 0.5,
			allNonStaticColliders[i]->transform.GetGlobalPosition().z +  allNonStaticColliders[i]->cubicDimension.z * 0.5);

		std::unordered_set<Collider*>& p2 = staticQuadtree->GameObjectsAt(allNonStaticColliders[i]->transform.GetGlobalPosition().x - allNonStaticColliders[i]->cubicDimension.x * 0.5,
			allNonStaticColliders[i]->transform.GetGlobalPosition().z + allNonStaticColliders[i]->cubicDimension.z * 0.5);

		std::unordered_set<Collider*>& p3 = staticQuadtree->GameObjectsAt(allNonStaticColliders[i]->transform.GetGlobalPosition().x - allNonStaticColliders[i]->cubicDimension.x * 0.5,
			allNonStaticColliders[i]->transform.GetGlobalPosition().z - allNonStaticColliders[i]->cubicDimension.z * 0.5);

		std::unordered_set<Collider*>& p4 = staticQuadtree->GameObjectsAt(allNonStaticColliders[i]->transform.GetGlobalPosition().x + allNonStaticColliders[i]->cubicDimension.x * 0.5,
			allNonStaticColliders[i]->transform.GetGlobalPosition().z - allNonStaticColliders[i]->cubicDimension.z * 0.5);

		std::unordered_set<Collider*> staticCols;
		staticCols.insert(p1.begin(), p1.end());
		staticCols.insert(p2.begin(), p2.end());
		staticCols.insert(p3.begin(), p3.end());
		staticCols.insert(p4.begin(), p4.end());



		for (auto it = staticCols.begin(); it != staticCols.end(); it++)
		{
			if (allNonStaticColliders[i]->GetCollideAgainstLayer() & (*it)->GetCollisionLayer() ||
				(*it)->GetCollideAgainstLayer() & allNonStaticColliders[i]->GetCollisionLayer())
			{
				if ((*it)->GetActive() && allNonStaticColliders[i]->GetActive())
				{					
					CheckCollision(*it, allNonStaticColliders[i]);
				}
			}
		}
		
	}

	if (staticToo)
		PerformCollisions(staticQuadtree->root);

	//Logger::LogWarning("ENDING COLLISION UPDATE");
}

glm::vec3 PhysicsWorld::gravity = glm::vec3(0, -9.8, 0);

bool PhysicsWorld::WereGameObjectsColliding(GameObject* obj1, GameObject* obj2)
{
	{
		auto it = gameObjectCollisionMap.find(obj1);

		if (it != gameObjectCollisionMap.end())
		{
			auto it2 = it->second.find(obj2);

			if (it2 != it->second.end())
				return true;
		}
	}

	{
		auto it = gameObjectCollisionMap.find(obj2);

		if (it != gameObjectCollisionMap.end())
		{
			auto it2 = it->second.find(obj1);

			if (it2 != it->second.end())
				return true;
		}
	}

	return false;

}

bool PhysicsWorld::WereCollidersColliding(Collider* obj1, Collider* obj2)
{
	auto it = collidersCollisionMap.find(obj1);

	if (it != collidersCollisionMap.end())
	{
		if (std::find(it->second.begin(), it->second.end(), obj2) != it->second.end())
			return true;
	}

	it = collidersCollisionMap.find(obj2);

	if (it != collidersCollisionMap.end())
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
							CheckCollision(*it, *it2);			
						}
					
					}		
				}
			}
		}
	}
}



void PhysicsWorld::CheckCollision(Collider* it, Collider* it2)
{
	if (WereCollidingThisFrame(it, it2))
	{
		return;
	}

	collidersCollisionMapPerFrame[it].push_back(it2);
	collidersCollisionMapPerFrame[it2].push_back(it);

	
	if (CollisionChecks::Collision((it), (it2)))
	{
		// Check if colliders were colliding
		if (!WereCollidersColliding((it), (it2)))
		{
			// Record that colliders are now colliding
			collidersCollisionMap[(it)].push_back(it2);
			collidersCollisionMap[(it2)].push_back(it);

			// If the gameobjects were not colliding, call OnCollision enter (this is the first collision)
			if (!WereGameObjectsColliding((it)->GetParent(), (it2)->GetParent()))
			{
				// OnCollisionEnter
				(it)->OnCollisionEnterCallback((it2));
				(it2)->OnCollisionEnterCallback((it));

				gameObjectCollisionMap[(it)->GetParent()][(it2)->GetParent()].push_back((it2));
				gameObjectCollisionMap[(it2)->GetParent()][(it)->GetParent()].push_back((it));

			}
			else
			{
				// If the colliders were not colliding, but the GameObjects were
				// it means that we are colliding with a new collider of the same gameobjects

				// OnCollisionStay
				(it)->OnCollisionStayCallback((it2));
				(it2)->OnCollisionStayCallback((it));

#ifdef CHANGE_COLOR
				(it)->meshRenderer->GetMaterial().SetColor(1, 0, 0);
				(it2)->meshRenderer->GetMaterial().SetColor(1, 0, 0);
#endif // CHANGE_COLOR



				if (std::find(gameObjectCollisionMap[(it)->GetParent()][(it2)->GetParent()].begin(), gameObjectCollisionMap[(it)->GetParent()][(it2)->GetParent()].end(), it2) == gameObjectCollisionMap[(it)->GetParent()][(it2)->GetParent()].end())
				{
					gameObjectCollisionMap[(it)->GetParent()][(it2)->GetParent()].push_back((it2));
				}

				if (std::find(gameObjectCollisionMap[(it2)->GetParent()][(it)->GetParent()].begin(), gameObjectCollisionMap[(it2)->GetParent()][(it)->GetParent()].end(), it) == gameObjectCollisionMap[(it2)->GetParent()][(it)->GetParent()].end())
				{
					gameObjectCollisionMap[(it2)->GetParent()][(it)->GetParent()].push_back((it));
				}

			}
		}
		else
		{
			// OnCollisionStay
			(it)->OnCollisionStayCallback((it2));
			(it2)->OnCollisionStayCallback((it));

#ifdef CHANGE_COLOR
			(it)->meshRenderer->GetMaterial().SetColor(1, 0, 0);
			(it2)->meshRenderer->GetMaterial().SetColor(1, 0, 0);
#endif // CHANGE_COLOR
		}
	}
	else
	{


		if (WereCollidersColliding((it), (it2)))
		{
			// Record that the colliders are no longer in collision
			collidersCollisionMap[(it)].remove(it2);
			collidersCollisionMap[(it2)].remove(it);

			if (std::find(gameObjectCollisionMap[(it)->GetParent()][(it2)->GetParent()].begin(), gameObjectCollisionMap[(it)->GetParent()][(it2)->GetParent()].end(), it2) != gameObjectCollisionMap[(it)->GetParent()][(it2)->GetParent()].end())
			{
				gameObjectCollisionMap[(it)->GetParent()][(it2)->GetParent()].remove(it2);
#ifdef CHANGE_COLOR
				(it2)->meshRenderer->GetMaterial().SetColor(0, 1, 0);
#endif // CHANGE_COLOR
			}

			if (std::find(gameObjectCollisionMap[(it2)->GetParent()][(it)->GetParent()].begin(), gameObjectCollisionMap[(it2)->GetParent()][(it)->GetParent()].end(), it) != gameObjectCollisionMap[(it2)->GetParent()][(it)->GetParent()].end())
			{
				gameObjectCollisionMap[(it2)->GetParent()][(it)->GetParent()].remove(it);
#ifdef CHANGE_COLOR
				(it)->meshRenderer->GetMaterial().SetColor(0, 1, 0);
#endif // CHANGE_COLOR

			}

			if (gameObjectCollisionMap[(it)->GetParent()][(it2)->GetParent()].size() == 0 &&
				gameObjectCollisionMap[(it2)->GetParent()][(it)->GetParent()].size() == 0)
			{
				// OnCollisionExit

				(it)->OnCollisionExitCallback(it2);
				(it2)->OnCollisionExitCallback(it);

#ifdef CHANGE_COLOR
				(it2)->meshRenderer->GetMaterial().SetColor(0, 1, 0);
				(it)->meshRenderer->GetMaterial().SetColor(0, 1, 0);
#endif // CHANGE_COLOR

				gameObjectCollisionMap[(it)->GetParent()].erase((it2)->GetParent());
				gameObjectCollisionMap[(it2)->GetParent()].erase((it)->GetParent());
			}
		}
	}
}




