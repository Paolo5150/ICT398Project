#pragma once
#include "..\Core\GameObject.h"

class Chair : public GameObject
{

public:
	Chair();
	~Chair();

	void Update() override;
	void Start() override;
	void OnCollisionEnter(Collider* g, Collision collision) override;
	void OnCollisionStay(Collider* g, Collision collision) override;
	void OnCollisionExit(Collider* g, Collision collision) override;

private:

};