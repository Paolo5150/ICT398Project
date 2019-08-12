#pragma once
#include "..\Core\GameObject.h"



class Bench : public GameObject
{

public:
	Bench();
	~Bench();

	void Update() override;
	void Start() override;
	void OnCollision(GameObject* g, glm::vec3 collPoint, glm::vec3 collNormal) override;

private:

};