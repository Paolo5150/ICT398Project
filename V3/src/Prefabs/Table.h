#pragma once
#include "..\Core\GameObject.h"

class Table : public GameObject
{

public:
	Table();
	~Table();

	void Update() override;
	void Start() override;
	void OnCollisionEnter(GameObject* g) override;
	void OnCollisionStay(GameObject* g) override;

private:

};