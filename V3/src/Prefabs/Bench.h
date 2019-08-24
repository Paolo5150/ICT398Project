#pragma once
#include "..\Core\GameObject.h"



class Bench : public GameObject
{

public:
	Bench();
	~Bench();

	void Update() override;
	void Start() override;
	void OnCollisionEnter(GameObject* g) override;
	void OnCollisionStay(GameObject* g) override;


private:

};