#include "pch.h"
#include "CollisionChecks.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\SphereCollider.h"

bool CollisionChecks::Collision(Collider* s, Collider* b)
{
	if (s->colliderType == Collider::BOX && b->colliderType == Collider::BOX)
		return Collision(dynamic_cast<BoxCollider*>(s), dynamic_cast<BoxCollider*>(b));

	else if (s->colliderType == Collider::BOX && b->colliderType == Collider::SPHERE)
		return Collision(dynamic_cast<SphereCollider*>(b),dynamic_cast<BoxCollider*>(s));

	else if (s->colliderType == Collider::SPHERE && b->colliderType == Collider::BOX)
		return Collision(dynamic_cast<SphereCollider*>(s), dynamic_cast<BoxCollider*>(b));

	else if (s->colliderType == Collider::SPHERE && b->colliderType == Collider::SPHERE)
		return Collision(dynamic_cast<SphereCollider*>(s), dynamic_cast<SphereCollider*>(b));	
}

bool CollisionChecks::Collision(SphereCollider* s, BoxCollider* b)
{
	glm::vec3 dist = glm::abs(s->transform.GetGlobalPosition() - b->transform.GetGlobalPosition());

	if (dist.x >= (b->transform.GetGlobalScale().x + s->transform.GetGlobalScale().x / 2)) { return false; }
	if (dist.y >= (b->transform.GetGlobalScale().y + s->transform.GetGlobalScale().x / 2)) { return false; }
	if (dist.z >= (b->transform.GetGlobalScale().z + s->transform.GetGlobalScale().x / 2)) { return false; }

	if (dist.x < (b->transform.GetGlobalScale().x / 2)) { return true; }
	if (dist.y < (b->transform.GetGlobalScale().y / 2)) { return true; }
	if (dist.z < (b->transform.GetGlobalScale().z / 2)) { return true; }

	float cornerDistance_sq = ((dist.x - b->transform.GetGlobalScale().x) * (dist.x - b->transform.GetGlobalScale().x)) +
		((dist.y - b->transform.GetGlobalScale().y) * (dist.y - b->transform.GetGlobalScale().y) +
		((dist.z - b->transform.GetGlobalScale().z) * (dist.z - b->transform.GetGlobalScale().z)));

	return (cornerDistance_sq < (s->transform.GetGlobalScale().x / 2 * s->transform.GetGlobalScale().x / 2));
	return 0;


}
bool CollisionChecks::Collision(SphereCollider* s, SphereCollider* b)
{
	float dist = glm::length2(s->transform.GetGlobalPosition() - b->transform.GetGlobalPosition());
	float sum = s->transform.GetGlobalScale().x + b->transform.GetGlobalScale().x;

	if (dist < (sum / 2) * (sum / 2))
		return 1;

	return 0;
}
bool CollisionChecks::Collision(BoxCollider* s, BoxCollider* b)
{
		return getCollision(s, b);	
}

bool CollisionChecks::getSeparatingPlane(glm::vec3 RPos, glm::vec3 Plane, BoxCollider* box1, BoxCollider* box2)
{
	return (glm::abs(glm::dot(RPos, Plane)) >(glm::abs(glm::dot((box1->transform.GetLocalRight() *box1->transform.GetGlobalScale().x ), Plane)) + glm::abs(glm::dot((box1->transform.GetLocalUp() *box1->transform.GetGlobalScale().y ), Plane)) + glm::abs(glm::dot((box1->transform.GetLocalFront() *box1->transform.GetGlobalScale().z ), Plane)) +
		glm::abs(glm::dot((box2->transform.GetLocalRight() *box2->transform.GetGlobalScale().x ), Plane)) + glm::abs(glm::dot((box2->transform.GetLocalUp() *box2->transform.GetGlobalScale().y ), Plane)) + glm::abs(glm::dot((box2->transform.GetLocalFront() *box2->transform.GetGlobalScale().z ), Plane)) ));
}

bool CollisionChecks::getCollision(BoxCollider* box1, BoxCollider* box2)
{
	static glm::vec3 RPos;
	RPos = box2->transform.GetGlobalPosition() - box1->transform.GetGlobalPosition();

	//Logger::LogInfo("Box front", box2->transform.VectorsToString());
	//Logger::LogError("Box front2", box1->transform.VectorsToString());

	if (getSeparatingPlane(RPos, box1->transform.GetLocalRight(), box1, box2) || getSeparatingPlane(RPos, box1->transform.GetLocalUp(), box1, box2) || getSeparatingPlane(RPos, box1->transform.GetLocalFront(), box1, box2) ||
		getSeparatingPlane(RPos, box2->transform.GetLocalRight(), box1, box2) || getSeparatingPlane(RPos, box2->transform.GetLocalUp(), box1, box2) || getSeparatingPlane(RPos, box2->transform.GetLocalFront(), box1, box2) ||
		getSeparatingPlane(RPos, glm::int3(box1->transform.GetLocalRight()) ^ glm::int3(box2->transform.GetLocalRight()), box1, box2) || getSeparatingPlane(RPos, glm::int3(box1->transform.GetLocalRight()) ^ glm::int3(box2->transform.GetLocalUp()), box1, box2) ||
		getSeparatingPlane(RPos, glm::int3(box1->transform.GetLocalRight()) ^ glm::int3(box2->transform.GetLocalFront()), box1, box2) || getSeparatingPlane(RPos, glm::int3(box1->transform.GetLocalUp()) ^ glm::int3(box2->transform.GetLocalRight()), box1, box2) ||
		getSeparatingPlane(RPos, glm::int3(box1->transform.GetLocalUp()) ^ glm::int3(box2->transform.GetLocalUp()), box1, box2) || getSeparatingPlane(RPos, glm::int3(box1->transform.GetLocalUp()) ^ glm::int3(box2->transform.GetLocalFront()), box1, box2) ||
		getSeparatingPlane(RPos, glm::int3(box1->transform.GetLocalFront()) ^ glm::int3(box2->transform.GetLocalRight()), box1, box2) || getSeparatingPlane(RPos, glm::int3(box1->transform.GetLocalFront()) ^ glm::int3(box2->transform.GetLocalUp()), box1, box2) ||
		getSeparatingPlane(RPos, glm::int3(box1->transform.GetLocalFront()) ^ glm::int3(box2->transform.GetLocalFront()), box1, box2)) return false;


	return true;
}