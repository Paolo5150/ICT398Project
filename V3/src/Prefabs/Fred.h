#pragma once
#include "..\Core\GameObject.h"
#include "..\Affordances\AffordanceObject.h"
#include "Billquad.h"

class AffordanceObject;

class Fred : public GameObject, public AffordanceObject
{

public:
	Fred();
	~Fred();

	void Update() override;
	void Start() override;
	void OnCollisionEnter(Collider* g, Collision& collision) override;
	void OnCollisionStay(Collider* g, Collision& collision) override;
	void OnCollisionExit(Collider* g) override;
	void Test(AffordanceObject*);
	Billquad& GetBillquad() { return *billquad; }
private:
	Billquad* billquad;
	void Move(); //Navigates to affordances or wanders if no affordance is selected

};