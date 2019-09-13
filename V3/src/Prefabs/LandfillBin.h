#pragma once
#include "..\Core\GameObject.h"

class Rigidbody;

class LandfillBin : public GameObject
{

public:
	LandfillBin();
	~LandfillBin();

	void Update() override;
	void Start() override;
	void OnCollisionEnter(Collider* g, Collision col) override;
	void OnCollisionStay(Collider* g, Collision col) override;
	void OnCollisionExit(Collider* g, Collision col) override;


private:
	Rigidbody* rb;
};
