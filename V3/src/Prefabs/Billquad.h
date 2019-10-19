#pragma once

#include "..\Core\GameObject.h"
#include "..\Components\Rigidbody.h"
#include "..\Rendering\Texture2D.h"
#include "..\Components\MeshRenderer.h"
#include "..\Components\AIEmotion.h"
#include <unordered_set>

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
	void RenderForSeconds(float seconds, float coolDown = 0);
	void CheckEmotions(AIEmotion* aiE);
	void AddToQ(Texture2D* t);


private:
	MeshRenderer* meshRenderer;

	void Initialize();
	Texture2D* texture;
	float timer;
	float coolDownTimer;
	bool isRendering;
	bool isCoolDown;
	std::unordered_set<Texture2D*> texturesQueue;
};
