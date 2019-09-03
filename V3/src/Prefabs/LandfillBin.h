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
	void OnCollisionEnter(Collider* g) override;
	void OnCollisionStay(Collider* g) override;
	void OnCollisionExit(Collider* g) override;


private:
	Rigidbody* rb;
};
