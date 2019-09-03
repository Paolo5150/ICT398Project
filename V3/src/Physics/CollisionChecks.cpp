#include "pch.h"
#include "CollisionChecks.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\SphereCollider.h"

#include "..\Diag\DiagRenderer.h"

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

glm::vec3 CollisionChecks::getCollisionPoint(Collider * s, Collider * b)
{
	if (s->colliderType == Collider::BOX && b->colliderType == Collider::BOX)
		return getCollisionPoint(dynamic_cast<BoxCollider*>(s), dynamic_cast<BoxCollider*>(b));

	else if (s->colliderType == Collider::BOX && b->colliderType == Collider::SPHERE)
		return getCollisionPoint(dynamic_cast<SphereCollider*>(b), dynamic_cast<BoxCollider*>(s));

	else if (s->colliderType == Collider::SPHERE && b->colliderType == Collider::BOX)
		return getCollisionPoint(dynamic_cast<SphereCollider*>(s), dynamic_cast<BoxCollider*>(b));

	else if (s->colliderType == Collider::SPHERE && b->colliderType == Collider::SPHERE)
		return getCollisionPoint(dynamic_cast<SphereCollider*>(s), dynamic_cast<SphereCollider*>(b));
}

glm::vec3 CollisionChecks::getCollisionPoint(BoxCollider * box1, BoxCollider * box2)
{
	static glm::vec3 RPos;
	RPos = box2->transform.GetGlobalPosition() - box1->transform.GetGlobalPosition();

	std::vector<glm::vec3> vertices = box1->GetBoxPoints();

	std::vector<glm::vec3> collisionPoints = std::vector<glm::vec3>();

	//Determine if any vertice of  box is inside another box
	for (int i = 0; i < vertices.size(); i++)
	{
		if (isPointInBox(vertices[i], box2))
			collisionPoints.push_back(vertices[i]);
	}

	vertices = box2->GetBoxPoints();

	for (int i = 0; i < vertices.size(); i++)
	{
		DiagRenderer::Instance().RenderSphere(vertices[i]);
		if (isPointInBox(vertices[i], box1))
			collisionPoints.push_back(vertices[i]);
	}

	float avgX = 0, avgY = 0, avgZ = 0;
	for (int i = 0; i < collisionPoints.size(); i++)
	{
		DiagRenderer::Instance().RenderSphere(collisionPoints[i]);
		avgX += collisionPoints[i].x / collisionPoints.size();
		avgY += collisionPoints[i].y / collisionPoints.size();
		avgZ += collisionPoints[i].z / collisionPoints.size();
	}

	glm::vec3 collisionPoint = glm::vec3(avgX, avgY, avgZ);

	if (collisionPoints.size() == 0)
	{
		//Simplified point if no vertices of box intersect
		collisionPoint = (box1->transform.GetGlobalPosition() + box2->transform.GetGlobalPosition()) / 2.0f;
		collisionPoint = (getClosestPointToBox(collisionPoint, box1) + getClosestPointToBox(collisionPoint, box2)) / 2.0f;
	}

	return collisionPoint;
}

glm::vec3 CollisionChecks::getCollisionPoint(SphereCollider * s, BoxCollider * b)
{
	return getClosestPointToBox(s->transform.GetGlobalPosition(), b);
}

glm::vec3 CollisionChecks::getCollisionPoint(SphereCollider * s, SphereCollider * b)
{
	return s->transform.GetGlobalPosition() + glm::normalize(s->transform.GetGlobalPosition() - b->transform.GetGlobalPosition()) * (s->transform.GetGlobalScale().x / 2);
}

glm::vec3 CollisionChecks::getCollisionNormal(glm::vec3 point, Collider * col)
{
	switch (col->colliderType)
	{
	case Collider::BOX:
		return getCollisionNormal(point, dynamic_cast<BoxCollider*>(col));
	case Collider::SPHERE:
		return getCollisionNormal(point, dynamic_cast<SphereCollider*>(col));
	}
}

glm::vec3 CollisionChecks::getCollisionNormal(glm::vec3 point, BoxCollider * col)
{
	glm::mat4 rot = col->transform.GetGlobalRotation();
	rot = glm::inverse(rot);
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), -col->transform.GetGlobalPosition());

	auto rotVec = trans * rot * glm::vec4(point, 1.0);

	glm::vec3 closestAxis = col->transform.GetLocalRight();
	float dif = abs(rotVec[0] - (col->transform.GetGlobalScale()[0] / 2.0f));
	float temp = abs(rotVec[0] - -(col->transform.GetGlobalScale()[0] / 2.0f));
	if (temp < dif)
	{
		dif = temp;
		closestAxis = -col->transform.GetLocalRight();
	}
	temp = abs(rotVec[1] - (col->transform.GetGlobalScale()[1] / 2.0f));
	if (temp < dif)
	{
		dif = temp;
		closestAxis = col->transform.GetLocalUp();
	}
	temp = abs(rotVec[2] - -(col->transform.GetGlobalScale()[2] / 2.0f));
	if (temp < dif)
	{
		dif = temp;
		closestAxis = col->transform.GetLocalFront();
	}

	temp = abs(rotVec[2] - -(col->transform.GetGlobalScale()[2] / 2.0f));
	if (temp < dif)
	{
		dif = temp;
		closestAxis = -col->transform.GetLocalFront();
	}

	return closestAxis;
}

glm::vec3 CollisionChecks::getCollisionNormal(glm::vec3 point, SphereCollider * col)
{
	return glm::normalize(point - col->transform.GetGlobalPosition());
}

bool CollisionChecks::isPointInBox(glm::vec3 point, BoxCollider * box)
{
	glm::mat4 rot = box->transform.GetGlobalRotation();
	rot = glm::inverse(rot);
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), -box->transform.GetGlobalPosition());

	auto rotVec = trans * rot * glm::vec4(point, 1.0);

	if (rotVec.x >= -(box->transform.GetGlobalScale().x / 2) && rotVec.x <= box->transform.GetGlobalScale().x / 2 &&
		rotVec.y >= -(box->transform.GetGlobalScale().y / 2) && rotVec.y <= box->transform.GetGlobalScale().y / 2 &&
		rotVec.z >= -(box->transform.GetGlobalScale().z / 2) && rotVec.z <= box->transform.GetGlobalScale().z / 2)
			return true;

	return false;
}

glm::vec3 CollisionChecks::getClosestPointToBox(glm::vec3 point, BoxCollider * box)
{
	glm::mat4 rot = box->transform.GetGlobalRotation();
	rot = glm::inverse(rot);
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), -box->transform.GetGlobalPosition());

	auto rotVec = trans * rot * glm::vec4(point, 1.0);

	glm::vec3 closestPoint = glm::vec3();
	for (int i = 0; i < 3; i++)
	{
		if (rotVec[i] < -(box->transform.GetGlobalScale()[i] / 2))
			closestPoint[i] = -(box->transform.GetGlobalScale()[i] / 2);
		if (rotVec[i] > box->transform.GetGlobalScale()[i] / 2)
			closestPoint[i] = box->transform.GetGlobalScale()[i] / 2;
	}

	closestPoint = glm::inverse(trans * rot) * glm::vec4(closestPoint, 1.0);

	return closestPoint;
}
