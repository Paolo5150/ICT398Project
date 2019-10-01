#pragma once
#include "..\Core\GameObject.h"
#include "..\Affordances\AffordanceObject.h"
#include "..\Affordances\RestAffordance.h"


class Chair : public GameObject, public AffordanceObject
{

public:
	Chair();
	~Chair();

	void Update() override;
	void Start() override;
	void OnCollisionEnter(Collider* g, Collision& collision) override;
	void OnCollisionStay(Collider* g, Collision& collision) override;
	void OnCollisionExit(Collider* g) override;

private:

};