#pragma once
#include "..\Core\GameObject.h"

class RecycleBin : public GameObject
{

public:
	RecycleBin();
	~RecycleBin();

	void Update() override;
	void Start() override;
	void OnCollision(GameObject* g) override;

private:

};

