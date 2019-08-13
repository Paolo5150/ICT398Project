#include "pch.h"
#include "DiagSphere.h"
#include "..\Utils\ContentManager.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Rigidbody.h"

DiagSphere::DiagSphere(float radius, glm::vec3 pos, glm::vec3 col) : GameObject("DiagSphere")
{
	//SetIsStatic(false);
	ContentManager::Instance().GetAsset<Model>("Sphere")->PopulateGameObject(this);
	transform.SetScale(radius);
	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("ColorOnlyStatic"));
	m.SetColor(col.x, col.y, col.z);
	transform.SetPosition(pos);
	ApplyMaterial(m);

}

DiagSphere::~DiagSphere()
{

}

void DiagSphere::Update()
{
	GameObject::Update();
}

void DiagSphere::Start()
{

	GameObject::Start(); //This will call start on all the object components, so it's better to leave it as last call when the collider
						 // has been added.
}

