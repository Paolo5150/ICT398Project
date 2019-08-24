#pragma once
#include "..\Core\GameObject.h"

class LandfillBin : public GameObject
{

public:
	LandfillBin();
	~LandfillBin();

	void Update() override;
	void Start() override;
	void OnCollisionEnter(GameObject* g) override;
	void OnCollisionStay(GameObject* g) override;

private:

};
