#pragma once
#include "..\Core\GameObject.h"

class Rigidbody;

class Lantern : public GameObject
{

public:
	Lantern();
	~Lantern();

	void Start() override;
	Rigidbody* rb;

private:

};