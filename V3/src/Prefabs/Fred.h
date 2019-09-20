#pragma once
#include "..\Core\GameObject.h"

class Fred : public GameObject
{

public:
	Fred();
	~Fred();

	void Update() override;
	void Start() override;
	void OnCollisionEnter(Collider* g, Collision& collision) override;
	void OnCollisionStay(Collider* g, Collision& collision) override;
	void OnCollisionExit(Collider* g) override;

private:

};