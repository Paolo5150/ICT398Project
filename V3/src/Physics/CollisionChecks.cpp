#include "pch.h"
#include "CollisionChecks.h"
#include "..\Components\BoxCollider.h"
#include "..\Diag\DiagRenderer.h"
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

void SATtest(glm::vec3& axis, std::vector<glm::vec3> ptSet, float& minAlong, float& maxAlong)
{
	minAlong = HUGE, maxAlong = -HUGE;
	
	for (int i = 0; i < ptSet.size(); i++)
	{
		// just dot it to get the min/max along this axis.
		float dotVal = glm::dot(ptSet[i],axis);
		if (dotVal < minAlong)
		{
			minAlong = dotVal;

		}
		if (dotVal > maxAlong) 
		{ 
			maxAlong = dotVal;
		}
	}
}



inline bool isBetweenOrdered(float val, float lowerBound, float upperBound) {
	return lowerBound < val && val < upperBound;
}

bool overlaps(float min1, float max1, float min2, float max2)
{
	return isBetweenOrdered(min2, min1, max1) || isBetweenOrdered(min1, min2, max2);
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
		
	return 1;

		/*float shape1Min = 0;
		float shape1Max = 0;
		float shape2Min = 0;
		float shape2Max = 0;

		// B1 right
		SATtest(box1->transform.GetLocalRight(), box1->GetBoxPoints(), shape1Min, shape1Max);
		SATtest(box1->transform.GetLocalRight(), box2->GetBoxPoints(), shape2Min, shape2Max);

		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
			return 0; // NO INTERSECTION
		}

		// B1 front
		SATtest(box1->transform.GetLocalFront(), box1->GetBoxPoints(), shape1Min, shape1Max);
		SATtest(box1->transform.GetLocalFront(), box2->GetBoxPoints(), shape2Min, shape2Max);

		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
			return 0; // NO INTERSECTION
		}

		// B1 up
		SATtest(box1->transform.GetLocalUp(), box1->GetBoxPoints(), shape1Min, shape1Max);
		SATtest(box1->transform.GetLocalUp(), box2->GetBoxPoints(), shape2Min, shape2Max);

		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
			return 0; // NO INTERSECTION
		}

		// TEST SHAPE2.normals as well
				// B2 right
		SATtest(box2->transform.GetLocalRight(), box1->GetBoxPoints(), shape1Min, shape1Max);
		SATtest(box2->transform.GetLocalRight(), box2->GetBoxPoints(), shape2Min, shape2Max);

		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
			return 0; // NO INTERSECTION
		}

		// B2 front
		SATtest(box2->transform.GetLocalFront(), box1->GetBoxPoints(), shape1Min, shape1Max);
		SATtest(box2->transform.GetLocalFront(), box2->GetBoxPoints(), shape2Min, shape2Max);

		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
			return 0; // NO INTERSECTION
		}

		// B2 up
		SATtest(box2->transform.GetLocalUp(), box1->GetBoxPoints(), shape1Min, shape1Max);
		SATtest(box2->transform.GetLocalUp(), box2->GetBoxPoints(), shape2Min, shape2Max);

		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
			return 0; // NO INTERSECTION
		}

		// if overlap occurred in ALL AXES, then they do intersect
		return 1;*/
}