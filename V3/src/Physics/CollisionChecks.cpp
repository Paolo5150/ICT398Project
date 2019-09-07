#include "pch.h"
#include "CollisionChecks.h"
#include "..\Components\BoxCollider.h"
#include "..\Diag\DiagRenderer.h"
#include "..\Components\SphereCollider.h"
#include "..\Utils\Maths.h"

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



void SATtest(glm::vec3& axis,glm::vec3& boxPos, std::vector<glm::vec3> ptSet, glm::vec3& minAlong, glm::vec3& maxAlong, bool first = 0)
{
	float min = -HUGE;
	float max = -HUGE;

	glm::vec3 centerProj = glm::proj(boxPos,axis);

	for (int i = 0; i < ptSet.size(); i++)
	{
		glm::vec3 proj = glm::proj(ptSet[i], axis);
		glm::vec3 boxToPoint = proj - centerProj;
		float length2 = glm::length2(boxToPoint);
		float dot = glm::dot(glm::normalize(boxToPoint), axis);

		if (length2 > min && dot < 0)
		{
			min = length2;
			minAlong = proj;

		}
		if (length2 > max && dot > 0)
		{
			max = length2;
			maxAlong = proj;
		}
	}

/*	if (minAlong == maxAlong)
		Logger::LogError("SAME POSITION");

	glm::vec3 minToMax = maxAlong - minAlong;
	if (glm::dot(glm::normalize(minToMax), axis) < 0)
	{
		minToMax = maxAlong;
		maxAlong = minAlong;
		minAlong = minToMax;
	}*/



}



bool isBetweenOrdered(glm::vec3& min1, glm::vec3& min2, glm::vec3& max2) {

	glm::vec3 box1minMax = max2 - min2;
	glm::vec3 box1MinTobox2Min = min1 - min2;

	if (glm::dot(glm::normalize(box1minMax), glm::normalize(box1MinTobox2Min)) < 0) return 0;

	//volatile float box1minMaxLength = glm::length2(box1minMax);
	//volatile float box1MinTobox2MinLength = glm::length2(box1MinTobox2Min);
	return glm::length2(box1minMax) >= glm::length2(box1MinTobox2Min);
}

bool overlaps(glm::vec3& min1, glm::vec3& max1, glm::vec3& min2, glm::vec3& max2)
{
	return isBetweenOrdered(min2, min1, max1) || isBetweenOrdered(min1, min2, max2) ;
}



bool CollisionChecks::getCollision(BoxCollider* box1, BoxCollider* box2)
{
	/*static glm::vec3 RPos;
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
		
	return 1;*/

		glm::vec3 shape1Min;
		glm::vec3 shape1Max;
		glm::vec3 shape2Min;
		glm::vec3 shape2Max;

		// B1 right
		SATtest(box1->transform.GetLocalRight(),box1->transform.GetGlobalPosition(), box1->GetBoxPoints(), shape1Min, shape1Max,1);
		SATtest(box1->transform.GetLocalRight(),box2->transform.GetGlobalPosition(), box2->GetBoxPoints(), shape2Min, shape2Max);

		/*DiagRenderer::Instance().RenderSphere(shape1Min, 0.1, glm::vec3(1));
		DiagRenderer::Instance().RenderSphere(shape1Max, 0.2, glm::vec3(1, 0, 0));
		DiagRenderer::Instance().RenderSphere(shape2Min, 0.1, glm::vec3(0, 1, 0));
		DiagRenderer::Instance().RenderSphere(shape2Max, 0.2, glm::vec3(0, 0, 1));*/

		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
			//Logger::LogInfo("Box1 right");

			return 0; // NO INTERSECTION
		}
			   		 
	    SATtest(box2->transform.GetLocalRight(), box1->transform.GetGlobalPosition(), box1->GetBoxPoints(), shape1Min, shape1Max, 1);
		SATtest(box2->transform.GetLocalRight(), box2->transform.GetGlobalPosition(), box2->GetBoxPoints(), shape2Min, shape2Max);



		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
			//Logger::LogInfo("Box2 right");

			return 0; // NO INTERSECTION
		}

		
		SATtest(box1->transform.GetLocalUp(), box1->transform.GetGlobalPosition(), box1->GetBoxPoints(), shape1Min, shape1Max, 1);
		SATtest(box1->transform.GetLocalUp(), box2->transform.GetGlobalPosition(), box2->GetBoxPoints(), shape2Min, shape2Max);

		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
			//Logger::LogInfo("Box1 up");

			return 0; // NO INTERSECTION
		}

		SATtest(box2->transform.GetLocalUp(), box1->transform.GetGlobalPosition(), box1->GetBoxPoints(), shape1Min, shape1Max, 1);
		SATtest(box2->transform.GetLocalUp(), box2->transform.GetGlobalPosition(), box2->GetBoxPoints(), shape2Min, shape2Max);

		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
			//Logger::LogInfo("Box2 up");

				return 0; // NO INTERSECTION
		}

		glm::vec3 inverseFront = box1->transform.GetLocalFront() * -1.0f;
		// B1 front
		SATtest(inverseFront, box1->transform.GetGlobalPosition(), box1->GetBoxPoints(), shape1Min, shape1Max);
		SATtest(inverseFront, box2->transform.GetGlobalPosition(), box2->GetBoxPoints(), shape2Min, shape2Max);
	
	

		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
			//Logger::LogInfo("Box1 inverse front");

			return 0; // NO INTERSECTION
		}	

	   glm::vec3  inverseFront2 = box2->transform.GetLocalFront() * -1.0f;

		// B2 front
		SATtest(inverseFront2, box1->transform.GetGlobalPosition(), box1->GetBoxPoints(), shape1Min, shape1Max);
		SATtest(inverseFront2, box2->transform.GetGlobalPosition(), box2->GetBoxPoints(), shape2Min, shape2Max);


		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
		//	Logger::LogInfo("Box2 inverse front");

			return 0; // NO INTERSECTION
		}	

		// Box1front box2front
		glm::vec3 box1Frontbox2front = glm::normalize(glm::cross(-box1->transform.GetLocalFront(), -box2->transform.GetLocalFront()));
		SATtest(box1Frontbox2front, box1->transform.GetGlobalPosition(), box1->GetBoxPoints(), shape1Min, shape1Max);
		SATtest(box1Frontbox2front, box2->transform.GetGlobalPosition(), box2->GetBoxPoints(), shape2Min, shape2Max);


		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
		//	Logger::LogInfo("Box1 front box2 front");
			return 0; // NO INTERSECTION
		}
		// Box1front box2right
		glm::vec3 box1Frontbox2right = glm::normalize(glm::cross(-box1->transform.GetLocalFront(), box2->transform.GetLocalRight()));
		SATtest(box1Frontbox2right, box1->transform.GetGlobalPosition(), box1->GetBoxPoints(), shape1Min, shape1Max);
		SATtest(box1Frontbox2right, box2->transform.GetGlobalPosition(), box2->GetBoxPoints(), shape2Min, shape2Max);


		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
			//Logger::LogInfo("Box1 front box2 right");

			return 0; // NO INTERSECTION
		}

		// Box1front box2up
		glm::vec3 box1Frontbox2up = glm::normalize(glm::cross(-box1->transform.GetLocalFront(), box2->transform.GetLocalUp()));
		SATtest(box1Frontbox2up, box1->transform.GetGlobalPosition(), box1->GetBoxPoints(), shape1Min, shape1Max);
		SATtest(box1Frontbox2up, box2->transform.GetGlobalPosition(), box2->GetBoxPoints(), shape2Min, shape2Max);


		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
			//Logger::LogInfo("Box1 front box2 up");

			return 0; // NO INTERSECTION
		}
		// Box1right box2front
		glm::vec3 box1rightbox2front = glm::normalize(glm::cross(box1->transform.GetLocalRight(), -box2->transform.GetLocalFront()));
		SATtest(box1rightbox2front, box1->transform.GetGlobalPosition(), box1->GetBoxPoints(), shape1Min, shape1Max);
		SATtest(box1rightbox2front, box2->transform.GetGlobalPosition(), box2->GetBoxPoints(), shape2Min, shape2Max);


		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
			//Logger::LogInfo("Box1 right box2 front");

			return 0; // NO INTERSECTION
		}


		// Box1right box2right
		glm::vec3 box1rightbox2right = glm::normalize(glm::cross(box1->transform.GetLocalRight(), box2->transform.GetLocalRight()));
		SATtest(box1rightbox2right, box1->transform.GetGlobalPosition(), box1->GetBoxPoints(), shape1Min, shape1Max);
		SATtest(box1rightbox2right, box2->transform.GetGlobalPosition(), box2->GetBoxPoints(), shape2Min, shape2Max);


		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
			//Logger::LogInfo("Box1 right box2 right");

			return 0; // NO INTERSECTION
		}

		// Box1right box2up
		glm::vec3 box1rightbox2up = glm::normalize(glm::cross(box1->transform.GetLocalRight(), box2->transform.GetLocalUp()));
		SATtest(box1rightbox2up, box1->transform.GetGlobalPosition(), box1->GetBoxPoints(), shape1Min, shape1Max);
		SATtest(box1rightbox2up, box2->transform.GetGlobalPosition(), box2->GetBoxPoints(), shape2Min, shape2Max);


		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
			//Logger::LogInfo("Box1 right box2 up");

			return 0; // NO INTERSECTION
		}


		// Box1up box2front
		glm::vec3 box1upbox2front = glm::normalize(glm::cross(box1->transform.GetLocalUp(), -box2->transform.GetLocalFront()));
		SATtest(box1upbox2front, box1->transform.GetGlobalPosition(), box1->GetBoxPoints(), shape1Min, shape1Max);
		SATtest(box1upbox2front, box2->transform.GetGlobalPosition(), box2->GetBoxPoints(), shape2Min, shape2Max);


		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
			//Logger::LogInfo("Box1 up box2 front");

			return 0; // NO INTERSECTION
		}
		// Box1up box2right

		glm::vec3 box1upbox2right = glm::normalize(glm::cross(box1->transform.GetLocalUp(), box2->transform.GetLocalRight()));
		SATtest(box1upbox2right, box1->transform.GetGlobalPosition(), box1->GetBoxPoints(), shape1Min, shape1Max);
		SATtest(box1upbox2right, box2->transform.GetGlobalPosition(), box2->GetBoxPoints(), shape2Min, shape2Max);


		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
			//Logger::LogInfo("Box1 up box2 right");

			return 0; // NO INTERSECTION
		}
		// Box1up box2up
		glm::vec3 box1upbox2up = glm::normalize(glm::cross(box1->transform.GetLocalUp(), box2->transform.GetLocalUp()));
		SATtest(box1upbox2up, box1->transform.GetGlobalPosition(), box1->GetBoxPoints(), shape1Min, shape1Max);
		SATtest(box1upbox2up, box2->transform.GetGlobalPosition(), box2->GetBoxPoints(), shape2Min, shape2Max);


		if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
		{
			//Logger::LogInfo("Box1 up box2 up");

			return 0; // NO INTERSECTION
		}

		return 1;
}