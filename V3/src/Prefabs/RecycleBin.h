#pragma once
#include "..\Core\GameObject.h"

class RecycleBin : public GameObject
{

public:
	RecycleBin();
	~RecycleBin();

	void Update() override;
	void Start() override;
	void OnCollisionEnter(GameObject* g) override;
	void OnCollisionStay(GameObject* g) override;
	void OnCollisionExit(GameObject* g) override;


private:

};

