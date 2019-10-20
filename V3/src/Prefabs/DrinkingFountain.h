#pragma once
#include "..\Core\GameObject.h"
#include "..\Components\Rigidbody.h"
#include "..\Affordances\AffordanceObject.h"

class DrinkingFountain : public GameObject, public AffordanceObject
{

public:
	DrinkingFountain();
	~DrinkingFountain();

	void Update() override;
	void Start() override;
	void OnCollisionEnter(Collider* g, Collision& collision) override;
	void OnCollisionStay(Collider* g, Collision& collision) override;

private:
	Rigidbody* rb;
};