#include "pch.h"
#include "PhysicsWorld.h"
#include "..\Core\Collision.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\SphereCollider.h"
#include "..\Events\EventDispatcher.h"
#include "..\Events\ApplicationEvents.h"
#include "..\Components\Rigidbody.h"
#include "..\Diag\DiagRenderer.h"
#include "Bullet/btBulletCollisionCommon.h"
#include "Bullet\btBulletDynamicsCommon.h"

#include <algorithm>


#define CHANGE_COLOR 0

struct MyContactResultCallback : public btCollisionWorld::ContactResultCallback
{
	bool collided;
	glm::vec3 contactPoint;
	glm::vec3 normal;

	MyContactResultCallback()
	{
		collided = 0;
	}

	btScalar addSingleResult(btManifoldPoint& cp,
		const btCollisionObjectWrapper* colObj0Wrap,
		int partId0,
		int index0,
		const btCollisionObjectWrapper* colObj1Wrap,
		int partId1,
		int index1)
	{

		//Logger::LogInfo("Some collision occurred");
		contactPoint = glm::vec3(cp.getPositionWorldOnA().x(), cp.getPositionWorldOnA().y(), cp.getPositionWorldOnA().z());
		normal = glm::vec3(cp.m_normalWorldOnB.x(), cp.m_normalWorldOnB.y(), cp.m_normalWorldOnB.z());

		collided = true;
		return 0;
	}
};


namespace
{
	btCollisionConfiguration* bt_collision_configuration;
	btCollisionDispatcher* bt_dispatcher;
	btBroadphaseInterface* bt_broadphase;
	btCollisionWorld* bt_collision_world;
	double scene_size = 5000;
	unsigned int max_objects = 16000;
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

	bt_collision_configuration = new btDefaultCollisionConfiguration();
	bt_dispatcher = new btCollisionDispatcher(bt_collision_configuration);

	btScalar sscene_size = (btScalar)scene_size;
	btVector3 worldAabbMin(-sscene_size, -sscene_size, -sscene_size);
	btVector3 worldAabbMax(sscene_size, sscene_size, sscene_size);
	//This is one type of broadphase, bullet has others that might be faster depending on the application
	bt_broadphase = new bt32BitAxisSweep3(worldAabbMin, worldAabbMax, max_objects, 0, true);  // true for disabling raycast accelerator

	bt_collision_world = new btCollisionWorld(bt_dispatcher, bt_broadphase, bt_collision_configuration);


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
			if ((*it)->GetActive() && allNonStaticColliders[i]->GetActive())
			{
				if (allNonStaticColliders[i]->GetCollideAgainstLayer() & (*it)->GetCollisionLayer() ||
					(*it)->GetCollideAgainstLayer() & allNonStaticColliders[i]->GetCollisionLayer())
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

glm::vec3 PhysicsWorld::gravity = glm::vec3(0.0, -3.8, 0);

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
				if ((*it)->GetActive() && (*it2)->GetActive())
				{
					// Check that the colliders do not belong to the same GameObject
					if ((*it)->GetParent() != (*it2)->GetParent())
					{
						if ((*it)->GetCollideAgainstLayer() & (*it2)->GetCollisionLayer() ||
							(*it2)->GetCollideAgainstLayer() & (*it)->GetCollisionLayer())
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

	///////////////////////////////////
		//Create two collision objects
	std::unique_ptr<btCollisionObject> A = std::unique_ptr<btCollisionObject>(new btCollisionObject());
	std::unique_ptr<btCollisionObject> B = std::unique_ptr<btCollisionObject>(new btCollisionObject());

	//Move each to a specific location
	A->getWorldTransform().setOrigin(btVector3((btScalar)(it->transform.GetGlobalPosition().x), (btScalar)(it->transform.GetGlobalPosition().y), (btScalar)(it->transform.GetGlobalPosition().z)));
	glm::quat qa = glm::quat(it->transform.GetGlobalRotation());
	btQuaternion qaBt(qa.x, qa.y, qa.z, qa.w);
	A->getWorldTransform().setRotation(qaBt);

	B->getWorldTransform().setOrigin(btVector3((btScalar)(it2->transform.GetGlobalPosition().x), (btScalar)(it2->transform.GetGlobalPosition().y), (btScalar)(it2->transform.GetGlobalPosition().z)));
	qa = glm::quat(it2->transform.GetGlobalRotation());
	btQuaternion qbBt(qa.x, qa.y, qa.z, qa.w);
	B->getWorldTransform().setRotation(qbBt);
	   
	std::unique_ptr<btBoxShape> sphere_shape1 = std::unique_ptr<btBoxShape>(new btBoxShape(btVector3((btScalar)(it->transform.GetGlobalScale().x), (btScalar)(it->transform.GetGlobalScale().y), (btScalar)(it->transform.GetGlobalScale().z))));
	std::unique_ptr<btBoxShape> sphere_shape2 = std::unique_ptr<btBoxShape>(new btBoxShape(btVector3((btScalar)(it2->transform.GetGlobalScale().x), (btScalar)(it2->transform.GetGlobalScale().y), (btScalar)(it2->transform.GetGlobalScale().z))));

	A->setCollisionShape(sphere_shape1.get());
	B->setCollisionShape(sphere_shape2.get());

	MyContactResultCallback callback;
	bt_collision_world->contactPairTest(A.get(), B.get(), callback);

	if (callback.collided)
	{

		glm::vec3 pos;
		glm::vec3 normal;

		
		/////////////////////////////////
		pos = callback.contactPoint;
		normal = callback.normal;
		Collision col2 = Collision(pos, normal);
	//	normal = CollisionChecks::getCollisionNormal(pos, it2);
		Collision col1 = Collision(pos, normal);

		// Check if colliders were colliding
		if (!WereCollidersColliding((it), (it2)))
		{

			// Record that colliders are now colliding
			collidersCollisionMap[(it)].push_back(it2);
			collidersCollisionMap[(it2)].push_back(it);

			// If the gameobjects were not colliding, call OnCollision enter (this is the first collision)
			if (!WereGameObjectsColliding((it)->GetParent(), (it2)->GetParent()))
			{
				PhysicsCalculation((it), (it2), col1);

				// OnCollisionEnter
				if((it)->GetCollideAgainstLayer() & (it2)->GetCollisionLayer())
					(it)->OnCollisionEnterCallback((it2), col1);

				if ((it2)->GetCollideAgainstLayer() & (it)->GetCollisionLayer())
					(it2)->OnCollisionEnterCallback((it), col2);

				gameObjectCollisionMap[(it)->GetParent()][(it2)->GetParent()].push_back((it2));
				gameObjectCollisionMap[(it2)->GetParent()][(it)->GetParent()].push_back((it));
			}
			else
			{
				// If the colliders were not colliding, but the GameObjects were
				// it means that we are colliding with a new collider of the same gameobjects
				/*Rigidbody* rb1 = it->GetParent()->GetComponent<Rigidbody>("Rigidbody");
				Rigidbody* rb2 = it2->GetParent()->GetComponent<Rigidbody>("Rigidbody");
				if (rb1 != nullptr && rb1->GetUseDynamicPhysics())
				{
					MoveTransform(it->GetParent()->transform, -rb1->GetVelocity(), -rb1->GetAngularVelocity());
					ZeroOutVelocity(rb1);
				}
				if (rb2 != nullptr && rb2->GetUseDynamicPhysics())
				{
					MoveTransform(it2->GetParent()->transform, -rb2->GetVelocity(), -rb2->GetAngularVelocity());
					ZeroOutVelocity(rb2);
				}	*/		

				// OnCollisionStay
				if ((it)->GetCollideAgainstLayer() & (it2)->GetCollisionLayer())
					(it)->OnCollisionStayCallback((it2), col1);

				if ((it2)->GetCollideAgainstLayer() & (it)->GetCollisionLayer())
					(it2)->OnCollisionStayCallback((it), col2);

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
		/*	Rigidbody* rb1 = it->GetParent()->GetComponent<Rigidbody>("Rigidbody");
			Rigidbody* rb2 = it2->GetParent()->GetComponent<Rigidbody>("Rigidbody");
			if (rb1 != nullptr && rb1->GetUseDynamicPhysics())
			{
				MoveTransform(it->GetParent()->transform, -rb1->GetVelocity(), -rb1->GetAngularVelocity());
				ZeroOutVelocity(rb1);
			}
			if (rb2 != nullptr && rb2->GetUseDynamicPhysics())
			{
				MoveTransform(it2->GetParent()->transform, -rb2->GetVelocity(), -rb2->GetAngularVelocity());
				ZeroOutVelocity(rb2);
			}*/
			// OnCollisionStay
			if ((it)->GetCollideAgainstLayer() & (it2)->GetCollisionLayer())
				(it)->OnCollisionStayCallback((it2), col1);

			if ((it2)->GetCollideAgainstLayer() & (it)->GetCollisionLayer())
				(it2)->OnCollisionStayCallback((it), col2);

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
				if ((it)->GetCollideAgainstLayer() & (it2)->GetCollisionLayer())
					(it)->OnCollisionExitCallback(it2);

				if ((it2)->GetCollideAgainstLayer() & (it)->GetCollisionLayer())
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

void PhysicsWorld::PhysicsCalculation(Collider * col1, Collider * col2, const Collision& collision)
{
	float epsilon = 0.8f;

	GameObject* obj1 = col1->GetParent();
	GameObject* obj2 = col2->GetParent();

	Rigidbody* rb1 = obj1->GetComponent<Rigidbody>("Rigidbody");
	Rigidbody* rb2 = obj2->GetComponent<Rigidbody>("Rigidbody");

	glm::vec3 vel1 = glm::vec3();
	glm::vec3 vel2 = glm::vec3();
	glm::vec3 angVel1 = glm::vec3();
	glm::vec3 angVel2 = glm::vec3();

	if (rb1 != nullptr)
	{
		vel1 = rb1->GetVelocity();
		angVel1 = glm::radians(rb1->GetAngularVelocity());
	}

	if (rb2 != nullptr)
	{
		vel2 = rb2->GetVelocity();
		angVel2 = glm::radians(rb2->GetAngularVelocity());
	}

	glm::vec3 r1 = collision.Point() - (obj1->transform.GetGlobalPosition() + obj1->GetCentreOfMass());
	glm::vec3 r2 = collision.Point() - (obj2->transform.GetGlobalPosition() + obj2->GetCentreOfMass());
	glm::vec3 normal = collision.Normal();
	glm::vec3 angularVel;

	float top = -(1 + epsilon) * (glm::dot(normal, vel1 - vel2)
		+ glm::dot(angVel1, glm::cross(r1, normal))
		- glm::dot(angVel2, glm::cross(r2, normal)));

	glm::vec3 bottom = (1 / obj1->GetTotalMass())
		+ (1 / obj2->GetTotalMass())
		+ ((glm::cross(r1, normal) * glm::inverse(obj1->GetInertiaTensor()) * glm::cross(r1, normal))
			+ (glm::cross(r2, normal) * glm::inverse(obj2->GetInertiaTensor()) * glm::cross(r2, normal)));

	glm::vec3 lambda;

	lambda = (top / bottom) * normal;

	if (rb1 != nullptr && rb1->GetUseDynamicPhysics())
	{
		MoveTransform(obj1->transform, -vel1, -angVel1);

		rb1->SetVelocity(vel1 + (lambda / obj1->GetTotalMass()));
		rb1->SetAngularVelocity(glm::degrees(angVel1 + glm::cross(lambda, r1) * glm::inverse(obj1->GetInertiaTensor()) * glm::cross(r1, normal)));
	}

	if (rb2 != nullptr && rb2->GetUseDynamicPhysics())
	{
		MoveTransform(obj2->transform, -vel2, -angVel2);

		rb2->SetVelocity(vel2 - (lambda / obj2->GetTotalMass()));
		rb2->SetAngularVelocity(glm::degrees(angVel2 - glm::cross(lambda, r2) * glm::inverse(obj2->GetInertiaTensor()) * glm::cross(r2, normal)));
	}
	
}

void PhysicsWorld::MoveTransform(Transform& tf, const glm::vec3& vel, const glm::vec3& angVel)
{
	tf.Translate(vel * Timer::GetDeltaS() );
	tf.RotateBy(angVel.z * Timer::GetDeltaS() , 0, 0, 1);
	tf.RotateBy(angVel.x * Timer::GetDeltaS()  , 1, 0, 0);
	tf.RotateBy(angVel.y * Timer::GetDeltaS() , 0, 1, 0);
}

void PhysicsWorld::ZeroOutVelocity(Rigidbody * rb)
{
	//rb->SetVelocity(glm::vec3());
	//rb->SetAngularVelocity(glm::vec3());
}




