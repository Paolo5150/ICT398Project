#pragma once
#include "..\Core\GameObject.h"
#include "..\Affordances\AffordanceObject.h"

class Rigidbody;

class Lantern : public GameObject, public AffordanceObject
{

public:
	Lantern();
	~Lantern();

	void Start() override;
	void Update() override;
	Rigidbody* rb;

private:

};