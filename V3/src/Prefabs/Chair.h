#pragma once
#include "..\Core\GameObject.h"

class Chair : public GameObject
{

public:
	Chair();
	~Chair();

	void Update() override;
	void Start() override;
	void OnCollisionEnter(Collider* g) override;
	void OnCollisionStay(Collider* g) override;
	void OnCollisionExit(Collider* g) override;


private:

};