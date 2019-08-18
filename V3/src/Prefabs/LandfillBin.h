#pragma once
#include "..\Core\GameObject.h"

class LandfillBin : public GameObject
{

public:
	LandfillBin();
	~LandfillBin();

	void Update() override;
	void Start() override;
	void OnCollision(GameObject* g) override;

private:

};
