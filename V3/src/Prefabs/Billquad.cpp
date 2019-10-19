#include "pch.h"
#include "Billquad.h"
#include "..\Utils\ContentManager.h"
#include <future>
#include <thread>
#include <chrono>

namespace
{
	std::promise<bool> promise;
	std::future<bool> fut;
}



Billquad::Billquad() : GameObject("Billquad")
{
	Initialize();
}

Billquad::Billquad(Texture2D* texture) : GameObject("Billquad")
{
	this->texture = texture;
	Initialize();
}

Billquad::~Billquad()
{

}

void Billquad::CheckEmotions(AIEmotion* aiE)
{
	auto it = aiE->GetNeeds().begin();

	// Check for needs that are below their threshold
	for (; it != aiE->GetNeeds().end(); it++)
	{
		if (aiE->GetNeedValue(it->first) < it->second->GetLowSeekThreshold() || aiE->GetNeedValue(it->first) > it->second->GetHighSeekThreshold())
		{
			// If found one, check if there's a texture with the need's name
			Texture2D* t = ContentManager::Instance().GetAsset<Texture2D>(it->second->GetName());
			if (t)
			{
				//If there is, display the emotion
				SetTexture(t);
				RenderForSeconds(2, 2);
			}
		}
	}
}


void Billquad::Update()
{
	GameObject::Update();



	if (timer > 0)
	{
		timer -= Timer::GetDeltaS();
		isRendering = true;
	}
	else
	{
		timer = 0;
		isRendering = false;

		if (coolDownTimer > 0)
			coolDownTimer -= Timer::GetDeltaS();

	}

	meshRenderer->SetActive(isRendering);
}
void Billquad::Start()
{
	GameObject::Start();

}
void Billquad::SetTexture(Texture2D* texture)
{

	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("TextureBillboarding"));

	if (texture != nullptr)
	{
		m.Loadtexture(texture, "diffuse0");
	}

	ApplyMaterial(m,MaterialType::DEFAULT);
	ApplyMaterial(m, MaterialType::COLORONLY);
	ApplyMaterial(m, MaterialType::NOLIGHT);

}

void Billquad::Initialize()
{
	ContentManager::Instance().GetAsset<Model>("Quad")->PopulateGameObject(this);
	meshRenderer = GetChild(0)->GetComponent<MeshRenderer>("MeshRenderer");

	meshRenderer->AddPreRenderCallback([&](Camera& cam, Shader* shader) {
		shader->SetVec3("scale", transform.GetScale());
		shader->SetVec3("position", transform.GetPosition());

	
	});
	SetTexture(this->texture);
	timer = 0;
	coolDownTimer = 0;
}

void Billquad::RenderForSeconds(float seconds, float coolDown)
{
	if (timer <= 0 && coolDownTimer <= 0)
	{
		timer = seconds;
		coolDownTimer = coolDown;

	}



}
