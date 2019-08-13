#pragma once
#include "..\Core\GameObject.h"
#include "..\Utils\Maths.h"
class DiagSphere : public GameObject
{

public:
	DiagSphere(float radius = 1.0f, glm::vec3 pos = glm::vec3(0,0,0), glm::vec3 col = glm::vec3(1,1,1));
	~DiagSphere();

	void Update() override;
	void Start() override;

private:

};