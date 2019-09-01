#pragma once
#include "..\Core\GameObject.h"

class RecycleBin : public GameObject
{

public:
	RecycleBin();
	~RecycleBin();

	void Update() override;
	void Start() override;
	void OnCollisionEnter(Collider* g, Collision col) override;
	void OnCollisionStay(Collider* g, Collision col) override;
	void OnCollisionExit(Collider* g, Collision col) override;


private:

};

