#pragma once
#include "..\Core\GameObject.h"

class Rigidbody;

class Lantern : public GameObject
{

public:
	Lantern();
	~Lantern();

	void Start() override;
	void Update() override;
	Rigidbody* rb;

private:

};