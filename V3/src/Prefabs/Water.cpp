#include "pch.h"
#include "Water.h"
#include "..\Rendering\Material.h"
#include "..\Utils\ContentManager.h"
#include "..\Core\Core.h"
#include "..\Utils\Maths.h"
#include "..\Rendering\RenderingEngine.h"
#include "..\Lighting\LightingManager.h"
#include "..\Scene\SceneManager.h"
#include "MainCamera.h"

namespace
{
std::string waterResizeToken;
bool cubemapLoaded = 0;
}


Water::Water(Texture2D* normalMap, Texture2D* distortion) : GameObject("Water")
{
	
	waterResizeToken = EventDispatcher::Instance().SubscribeCallback<WindowResizeEvent>(std::bind(&Water::ResizeFrameBuffers, this, std::placeholders::_1));
	Initialize(normalMap, distortion);	
}

Water::Water() : GameObject("Water")
{
	Initialize(ContentManager::Instance().GetAsset<Texture2D>("water_normal"), ContentManager::Instance().GetAsset<Texture2D>("dudv"));
}

void Water::Initialize(Texture2D* normalMap, Texture2D* distortion)
{
	mainCamera = nullptr;

	timer = 0;
	waterCamera = std::unique_ptr<CameraPerspective>(new CameraPerspective(60, Window::Instance().GetAspectRatio(), 0.1, 50000));
	waterCamera->RemoveAllMaskLayers();
	waterCamera->AddLayerMask(RenderingLayers::DEFAULT);
	waterCamera->AddLayerMask(RenderingLayers::TERRAIN);
	//waterCamera->AddLayerMask(RenderingLayers::SKYBOX);


	waterCamera->SetActive(false);


	int w, h;
	Window::Instance().GetWindowSize(w, h);
	refractionBuffer = Core::Instance().GetGraphicsAPI().CreateFrameBuffer("WaterRefraction FB",w/4, h/4);
	reflectionBuffer = Core::Instance().GetGraphicsAPI().CreateFrameBuffer("WaterReflection FB",w/4, h/4);

	Material material;
	material.SetShader(ContentManager::Instance().GetAsset<Shader>("Water"));


	material.Loadtexture(normalMap, "normal0");
	material.Loadtexture(distortion, "special0");

	material.Loadtexture(refractionBuffer->GetColorTexture(), "refraction0");
	material.Loadtexture(reflectionBuffer->GetColorTexture(), "reflection0");
	material.LoadCubemap(&SceneManager::Instance().GetCurrentScene().GetSkyBox()->GetCubeMap(),"cubemap0");

	transform.SetRotation(-90, 0, 0);
	material.LoadFloat("shininess", 300.0f);
	material.SetColor(0.8, 0.8f, 1.0f);

	material.LoadFloat("UVScale", 3.0f);

	ContentManager::Instance().GetAsset<Model>("Quad")->PopulateGameObject(this);
	meshRenderer =(GetChild("QuadMesh")->GetComponentByType<MeshRenderer>("Renderer"));
	meshRenderer->AddPreRenderCallback(std::bind(&Water::OnPreRender, this, std::placeholders::_1, std::placeholders::_2));
	meshRenderer->AddPostRenderCallback(std::bind(&Water::OnPostRender, this, std::placeholders::_1, std::placeholders::_2));

	meshRenderer->SetIsCullable(false);
	SetIsStatic(true);
	SetLayer(0);
	SetLayer(RenderingLayers::WATER);
	meshRenderer->SetMaterial(material);
	//meshRenderer->SetMaterial(material,NOLIGHT);
	//meshRenderer->SetMaterial(material,COLORONLY);


}


Water::~Water()
{
	EventDispatcher::Instance().UnsubscribeCallback<WindowResizeEvent>(waterResizeToken);

}

void Water::Update()
{
	if (mainCamera == nullptr)
	{
		mainCamera = dynamic_cast<MainCamera*>(Camera::GetCameraByName("Main Camera"));
		if (mainCamera == nullptr)
			return;
	}

	GameObject::Update();
	Core::Instance().GetGraphicsAPI().SetClipPlaneActive(true);
	timer += Timer::GetDeltaS();
	

	waterCamera->SetActive(1);
	glm::vec3 color = glm::vec3(0.5,0.5,0.5);

	//Refraction
	refractionBuffer->Bind();
	Core::Instance().GetGraphicsAPI().SetClearColor(0.321, 0.3529, 0.3550);
	Core::Instance().GetGraphicsAPI().ClearDepthBuffer();
	Core::Instance().GetGraphicsAPI().ClearColorBuffer();
	LightManager::Instance().SetClippingPlane(glm::vec4(0, -1, 0, transform.GetGlobalPosition().y));

	waterCamera->transform = mainCamera->transform;
	waterCamera->Update();
	//Logger::LogInfo("Wat cam", mainCamera->transform.VectorsToString());
	RenderingEngine::Instance().RenderBufferOverrideColor(waterCamera.get(),color, MaterialType::NOLIGHT);

	refractionBuffer->Unbind();

	//Reflection
	
	reflectionBuffer->Bind();
	Core::Instance().GetGraphicsAPI().SetClearColor(0.321, 0.3529, 0.3550);
	Core::Instance().GetGraphicsAPI().ClearDepthBuffer();
	Core::Instance().GetGraphicsAPI().ClearColorBuffer();
	//LightManager::Instance().SetClippingPlane(glm::vec4(0, 1, 0, transform.GetGlobalPosition().y));
	LightManager::Instance().SetClippingPlane(glm::vec4(0, 1, 0, -transform.GetGlobalPosition().y));

	color = glm::vec3(0.2, 0.2, 0.5);
	glm::vec3 ref = glm::reflect(mainCamera->transform.GetLocalFront(), glm::vec3(0, 1, 0));

	float heightDiff = transform.GetPosition().y - mainCamera->transform.GetPosition().y;
	waterCamera->transform.SetPosition(glm::vec3(mainCamera->transform.GetPosition().x, mainCamera->transform.GetPosition().y + heightDiff * 2.0, mainCamera->transform.GetPosition().z));

	waterCamera->transform.LookAt(waterCamera->transform.GetPosition() + ref);
	waterCamera->Update();
	LightManager::Instance().SetClippingPlane(glm::vec4(0, 1, 0, -transform.GetGlobalPosition().y));
	RenderingEngine::Instance().RenderBuffer(waterCamera.get(),MaterialType::NOLIGHT);

	reflectionBuffer->Unbind();

	Core::Instance().GetGraphicsAPI().SetClipPlaneActive(false);
	waterCamera->SetActive(0);


}

void Water::OnPostRender(Camera& camera, Shader* currentShader)
{
	//glEnable(GL_CULL_FACE);

}

void Water::OnPreRender(Camera& camera, Shader* currentShader)
{
	//glDisable(GL_CULL_FACE);

	//Logger::LogInfo("Water pre render");
	currentShader->SetFloat("timer", timer);
	currentShader->SetFloat("reflectionRefractionRatio", reflectionRefractionRatio);

	currentShader->SetInt("underwater", mainCamera->transform.GetGlobalPosition().y <  transform.GetPosition().y ? 1 : 0);


	if (SceneManager::Instance().GetCurrentScene().GetSkyBox() != nullptr && !cubemapLoaded)
	{
		meshRenderer->GetMaterial().LoadCubemap(&SceneManager::Instance().GetCurrentScene().GetSkyBox()->GetCubeMap());
		cubemapLoaded = 1;
	}

}

bool Water::ResizeFrameBuffers(Event* e)
{
	WindowResizeEvent* wc = dynamic_cast<WindowResizeEvent*>(e);

	refractionBuffer->ResizeTexture(wc->width/4, wc->height/4);
	reflectionBuffer->ResizeTexture(wc->width/4, wc->height/4);
	return 0;
}

