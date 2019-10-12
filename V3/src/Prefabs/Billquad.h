#pragma once

#include "..\Core\GameObject.h"
#include "..\Components\Rigidbody.h"
#include "..\Rendering\Texture2D.h"
#include "..\Components\MeshRenderer.h"

class Billquad :
	public GameObject
{
public:
	Billquad();

	Billquad(Texture2D* texture);
	~Billquad();

	void Update() override;
	void Start() override;

	void SetTexture(Texture2D* texture);
	void RenderForSeconds(float seconds);


private:
	MeshRenderer* meshRenderer;

	void Initialize();
	Texture2D* texture;
	float timer;
	bool isRendering;

};
