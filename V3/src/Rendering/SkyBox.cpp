#include "pch.h"
#include "Skybox.h"
#include "..\Utils\ContentManager.h"

Skybox::Skybox(CubeMap* cubemap)
{
	
	this->cubemap = cubemap;

	material.SetShader(ContentManager::Instance().GetAsset<Shader>("Skybox"));

	material.LoadCubemap(cubemap);
	
	dummy = std::unique_ptr<GameObject>(new GameObject("SkyboxDummyGameObject"));
	dummy->SetLayer(RenderingLayers::SKYBOX);

	meshRenderer =new MeshRenderer(ContentManager::Instance().GetAsset<Model>("Cube")->GetMeshes()[0],material);
	meshRenderer->SetIsCullable(false);

	meshRenderer->AddPreRenderCallback(std::bind(&Skybox::OnPreRender, this, std::placeholders::_1, std::placeholders::_2));
	meshRenderer->AddPostRenderCallback(std::bind(&Skybox::OnPostRender, this, std::placeholders::_1, std::placeholders::_2));
	dummy->AddComponent(meshRenderer);
	

}

Skybox::Skybox(EquirectangularMap* cubemap)
{
	material.SetShader(ContentManager::Instance().GetAsset<Shader>("SkyboxHDR"));

	material.LoadEquirectangularMap(cubemap);

	dummy = std::unique_ptr<GameObject>(new GameObject("SkyboxDummyGameObject"));
	dummy->SetLayer(RenderingLayers::SKYBOX);

	meshRenderer = new MeshRenderer(ContentManager::Instance().GetAsset<Model>("Cube")->GetMeshes()[0], material);
	meshRenderer->SetIsCullable(false);

	meshRenderer->AddPreRenderCallback(std::bind(&Skybox::OnPreRender, this, std::placeholders::_1, std::placeholders::_2));
	meshRenderer->AddPostRenderCallback(std::bind(&Skybox::OnPostRender, this, std::placeholders::_1, std::placeholders::_2));
	dummy->AddComponent(meshRenderer);
}

Skybox::~Skybox()
{	

}


void Skybox::OnPreRender(Camera& cam, Shader* s)
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

}
void Skybox::OnPostRender(Camera& cam, Shader* s)
{

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

}

void Skybox::EngineUpdate()
{	
	dummy->EngineUpdate();
}

