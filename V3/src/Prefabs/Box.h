#pragma once

#include "..\Core\GameObject.h"
#include "..\Components\Rigidbody.h"

class Box :
	public GameObject
{
public:
	Box();
	~Box();

	void Update() override;
	void Start() override;
	void OnCollision(GameObject* g, glm::vec3 collPoint, glm::vec3 collNormal) override;

private:
	Rigidbody* rb;
};

