#pragma once

#include "..\Core\GameObject.h"
#include "..\Components\Rigidbody.h"
#include "..\Affordances\AffordanceObject.h"


class Box2 :
	public GameObject, public AffordanceObject
{
public:
	Box2();
	~Box2();

	void Update() override;
	void Start() override;
	void OnCollisionEnter(Collider* g, Collision& col) override;
	void OnCollisionStay(Collider* g, Collision& col) override;
	void OnCollisionExit(Collider* g) override;



	Rigidbody* rb;
private:
	
};
