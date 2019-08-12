#pragma once
#include "..\Core\GameObject.h"

class Chair : public GameObject
{

public:
	Chair();
	~Chair();

	void Update() override;
	void Start() override;
	void OnCollision(GameObject* g, glm::vec3 collPoint, glm::vec3 collNormal) override;

private:

};