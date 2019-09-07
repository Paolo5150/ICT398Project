#pragma once
#include "..\Core\GameObject.h"

class BushCourt : public GameObject
{

public:
	BushCourt();
	~BushCourt();

	void Update() override;
	void Start() override;
	void OnCollisionEnter(Collider* g) override;
	void OnCollisionStay(Collider* g) override;

private:

};