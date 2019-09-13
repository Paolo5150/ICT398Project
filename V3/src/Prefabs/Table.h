#pragma once
#include "..\Core\GameObject.h"
#include "..\Components\Rigidbody.h"

class Table : public GameObject
{

public:
	Table();
	~Table();

	void Update() override;
	void Start() override;
	void OnCollisionEnter(Collider* g, Collision collision) override;
	void OnCollisionStay(Collider* g, Collision collision) override;

private:
	Rigidbody* rb;
};