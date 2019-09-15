#pragma once

#include "..\Core\GameObject.h"
#include "..\Components\Rigidbody.h"

class Box2 :
	public GameObject
{
public:
	Box2();
	~Box2();

	void Update() override;
	void Start() override;
	void OnCollisionEnter(Collider* g, Collision& col) override;
	void OnCollisionStay(Collider* g, Collision& col) override;

	Rigidbody* rb;
private:
	
};
