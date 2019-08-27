#pragma once
#include "..\Core\GameObject.h"

class RecycleBin : public GameObject
{

public:
	RecycleBin();
	~RecycleBin();

	void Update() override;
	void Start() override;
	void OnCollisionEnter(Collider* g) override;
	void OnCollisionStay(Collider* g) override;
	void OnCollisionExit(Collider* g) override;


private:

};

