#include "pch.h"

#include "Renderer.h"

#include "..\Core\Timer.h"
#include "..\Events\EventDispatcher.h"
#include "..\Core\Camera.h"
#include "..\Events\ApplicationEvents.h"
#include "..\Rendering\RenderingEngine.h"
#include "..\Rendering\Material.h"
#include "..\Utils\ContentManager.h"
#include "..\Lighting\LightingManager.h"


Renderer::Renderer(std::string name, Material m) : Component(name) {

	submitted = 0;
	_type = "Renderer";
	isCullable = true;
	SetMaterial(m);
}

Renderer::Renderer(std::string name) : Component(name) {

	submitted = 0;
	_type = "Renderer";
	isCullable = true;
}

void Renderer::CreateOtherMaterials(Material& defaultMat)
{

	std::size_t res =  defaultMat.GetShader().name.find("Static");
	std::string colorOnlyShader = "ColorOnlyStatic";
	std::string nolightShader = "DefaultStaticNoLight";

	if (res == std::string::npos)
	{
		colorOnlyShader = "ColorOnlyAnimated";
		nolightShader = "DefaultAnimatedNoLight";
	}
	//Create a ColorOnly material for all renderers
	Material co;
	co.SetShader(ContentManager::Instance().GetAsset<Shader>(colorOnlyShader));

	float r, g, b;
	defaultMat.GetColor(r, g, b);
	co.SetColor(r, g, b);
	SetMaterial(co, COLORONLY);

	//Create a NoLight material for all renderers, copy from default one (textures and color)
	

	Material nolight(defaultMat); //Copy from default
	nolight.SetShader(ContentManager::Instance().GetAsset<Shader>(nolightShader));
	nolight.SetColor(r, g, b);
	SetMaterial(nolight, NOLIGHT);
}

void Renderer::OnAttach(GameObject* go)
{
	transform = &go->transform;
}

void Renderer::EngineUpdate()
{
	if (_isActive)
	{
		if (isCullable)
		{
			glm::vec3 camToHere = transform->GetGlobalPosition() - Camera::GetCameraByName("Main Camera")->transform.GetGlobalPosition();
			float d = glm::dot(glm::normalize(camToHere), Camera::GetCameraByName("Main Camera")->transform.GetLocalFront());
			if (d >= 0.1)
			{

				RenderingEngine::Instance().SubmitRenderer(this);
				submitted = true;
			}
		}
		else
		{

			RenderingEngine::Instance().SubmitRenderer(this);
			submitted = true;
		}
	}

}

void Renderer::Update()
{
	
}

void Renderer::OnPostRender(Camera& cam, Shader* currentShader )
{
	for (unsigned i = 0; i < postRenderCallbacks.size(); i++)
		postRenderCallbacks[i](cam, currentShader);
}


void Renderer::OnPreRender(Camera& cam, Shader* currentShader )
{
	//Logger::LogInfo("Prerender called on", _parent->GetName());
	
	glm::mat4 mvp = cam.GetProjectionMatrix() * cam.GetViewMatrix() * transform->GetMatrix();
	Shader::GetCurrentShader().SetMat4("u_mvp", mvp);
	Shader::GetCurrentShader().SetMat4("u_model", transform->GetMatrix());
	Shader::GetCurrentShader().SetMat4("u_view", cam.GetViewMatrix());
	Shader::GetCurrentShader().SetMat4("u_projection", cam.GetProjectionMatrix());
	Shader::GetCurrentShader().SetVec3("u_cameraPosition", cam.transform.GetPosition());
	Shader::GetCurrentShader().SetVec3("AmbientLight", LightManager::Instance().GetAmbientLight());
	Shader::GetCurrentShader().SetVec4("u_clippingPlane", LightManager::Instance().GetClippingPlane());



	for (unsigned i = 0; i < preRenderCallbacks.size(); i++)
		preRenderCallbacks[i](cam, currentShader);

}

void Renderer::AddPreRenderCallback(std::function<void(Camera&, Shader*)> cb)
{
	preRenderCallbacks.push_back(cb);
}
void Renderer::AddPostRenderCallback(std::function<void(Camera&, Shader*)> cb)
{
	postRenderCallbacks.push_back(cb);

}


Material& Renderer::GetMaterial(MaterialType mt)
{
	auto it = allMaterials.find(mt);

	if (it != allMaterials.end())
		return allMaterials[mt];
	else
		return allMaterials[DEFAULT];


}
void Renderer::SetMaterial(Material m, MaterialType mt) {
	allMaterials[mt] = m;
/*
	if (mt == MaterialType::DEFAULT)
		CreateOtherMaterials(m);*/
		
		//Create a ColorOnly material for all renderers
	Material co;
	co.SetShader(ContentManager::Instance().GetAsset<Shader>("ColorOnlyStatic"));
	co.SetColor(0,0,0);

	{
		auto it = allMaterials.find(COLORONLY);
		if (it == allMaterials.end())
		{
			allMaterials[COLORONLY] = co;
		}
	}

	
	{
	auto it = allMaterials.find(NOLIGHT);
	if(it == allMaterials.end())
		allMaterials[NOLIGHT] = co;
	}

};