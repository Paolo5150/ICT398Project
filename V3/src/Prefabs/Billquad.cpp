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
	static bool found = 0;
	found = 0;
	// Check for needs that are below their threshold
	for (; it != aiE->GetNeeds().end(); it++)
	{
		if (aiE->GetNeedValue(it->first) < it->second->GetLowSeekThreshold())
		{
			found = 1;
			// If found one, check if there's a texture with the need's name
			Texture2D* t = ContentManager::Instance().GetAsset<Texture2D>(it->second->GetName() + "_low");
			if (t)
			{
				AddToQ(t);
			//	Logger::LogInfo("Added texture", it->second->GetName());
			}
		}
		else if (aiE->GetNeedValue(it->first) > it->second->GetHighSeekThreshold())
		{
			found = 1;
			// If found one, check if there's a texture with the need's name
			Texture2D* t = ContentManager::Instance().GetAsset<Texture2D>(it->second->GetName() + "_high");
			if (t)
			{
				AddToQ(t);
			//	Logger::LogInfo("Added texture", it->second->GetName());

			}
		}
	}

}

void Billquad::AddToQ(Texture2D* t)
{
	texturesQueue.insert(t);
}

void Billquad::Update()
{
	GameObject::Update();	

	if (texturesQueue.empty())
	{
		texture = nullptr;
		meshRenderer->SetActive(0);
	}

	if (timer > 0)
	{
		timer -= Timer::GetDeltaS();

	}
	else
	{
		timer = 1;

		if (isCoolDown)
		{
			isCoolDown = 0;
			return;
		}
		else
		{
			isCoolDown = 1;
			if (texture == nullptr)
			{
				if (!texturesQueue.empty())
				{
					SetTexture(*texturesQueue.begin());
					meshRenderer->SetActive(1);
				}

			}
			else
			{

				if (!texturesQueue.empty())
					texturesQueue.erase(texturesQueue.begin());

				if (!texturesQueue.empty())
				{
					SetTexture(*texturesQueue.begin());
					meshRenderer->SetActive(1);
				}
			}
		}
	

	}

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
	this->texture = texture;

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
	texture = nullptr;
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
