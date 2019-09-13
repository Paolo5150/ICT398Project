#pragma once

#include "..\Core\GameObject.h"
#include "..\Components\Rigidbody.h"

class Box :
	public GameObject
{
public:
	Box();
	~Box();

	void Update() override;
	void Start() override;
	void OnCollisionEnter(Collider* g, Collision& col) override;
	void OnCollisionStay(Collider* g, Collision& col) override;

private:
	Rigidbody* rb;
	
};
