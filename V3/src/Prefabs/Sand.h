#pragma once
#include "..\Core\GameObject.h"

class Sand : public GameObject
{

public:
	Sand();
	~Sand();

	void Update() override;
	void Start() override;

private:

};