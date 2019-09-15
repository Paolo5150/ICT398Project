#pragma once
#include "..\Core\GameObject.h"



class Bench : public GameObject
{

public:
	Bench();
	~Bench();

	void Update() override;
	void Start() override;
	void OnCollisionEnter(Collider* g, Collision& collision) override;
	void OnCollisionStay(Collider* g, Collision& collision) override;

private:

};