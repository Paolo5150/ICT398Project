#include "pch.h"

#include "RenderingEngine.h"
#include "..\Core\Core.h"
#include "..\Events\EventDispatcher.h"
#include "..\Events\ApplicationEvents.h"
#include "..\Components\Renderer.h"
#include "..\Core\Camera.h"
#include "..\Lighting\LightingManager.h"
#include "FrameBuffer.h"
#include "..\Utils\ContentManager.h"
//#include "..\GUI\GUIElements\GUIManager.h"
#include "PostProcessor.h"
#include "..\Diag\DiagRenderer.h"
#include <algorithm>
#include "..\Scene\SceneManager.h"
std::vector<Renderer*> RenderingEngine::allRenderers;
bool RenderingEngine::godRays;

RenderingEngine& RenderingEngine::Instance()
{
	static RenderingEngine instance;
	return instance;
}

RenderingEngine::RenderingEngine()
{
	godRays = false;
}


RenderingEngine::~RenderingEngine()
{
	
}

void RenderingEngine::Initialize()
{
	EventDispatcher::Instance().SubscribeCallback<SceneChangedEvent>([this](Event* e){

		ClearRendererList();
		return 0;
	});

	EventDispatcher::Instance().SubscribeCallback<WindowResizeEvent>([this](Event* e){

		WindowResizeEvent* wc = dynamic_cast<WindowResizeEvent*>(e);

	/*	renderTexture->ResizeTexture(wc->width, wc->height);
		renderTexture->ResizeTexture(wc->width, wc->height);

		occludedTexture->ResizeTexture(wc->width, wc->height);
		occludedTexture->ResizeTexture(wc->width, wc->height);*/
		return 0;
	});


	//int w, h;
	//Window::Instance().GetWindowSize(w, h);
	//renderTexture = Core::Instance().GetGraphicsAPI().CreateFrameBuffer("PostProcessFB",w, h);	
	/*occludedTexture = Core::Instance().GetGraphicsAPI().CreateFrameBuffer(w, h);
	godraysTexture = Core::Instance().GetGraphicsAPI().CreateFrameBuffer(w, h);*/

	/*godRayShader = ContentManager::Instance().GetAsset<Shader>("GodRays");
	postProcessShader = ContentManager::Instance().GetAsset<Shader>("PostProcess");

	Vertex v1(-1.0, -1.0, 0.0);
	v1.UV = glm::vec2(0, 0);

	Vertex v2(1.0, -1.0, 0.0);
	v2.UV = glm::vec2(1, 0);

	Vertex v3(1.0, 1.0, 0.0);
	v3.UV = glm::vec2(1, 1);

	Vertex v4(-1.0, 1.0, 0.0);
	v4.UV = glm::vec2(0, 1);

	std::vector<Vertex> vertices;
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);

	std::vector<unsigned> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(0);

	quadMesh = std::unique_ptr<Mesh>(new Mesh(vertices, indices));*/

}

void RenderingEngine::RenderBufferToTexture(MaterialType mt )
{

	Core::Instance().GetGraphicsAPI().ClearColorBuffer();
	Core::Instance().GetGraphicsAPI().ClearDepthBuffer();
	int previousDepth = 0;
	PostProcessor::Instance().BindFrameBuffer();
	Core::Instance().GetGraphicsAPI().ClearColorBuffer();
	Core::Instance().GetGraphicsAPI().ClearDepthBuffer();

	Camera* mainCam = nullptr;
	//Render opaque
	for (int camIndex = 0; camIndex < Camera::GetAllCameras().size(); camIndex++)
	{
		Camera& cam = *Camera::GetAllCameras()[camIndex];

		if (cam.name == "Main Camera")
			mainCam = &cam;

		if (!cam.GetActive()) continue;

		if (previousDepth != cam.GetDepth())
			Core::Instance().GetGraphicsAPI().ClearDepthBuffer();

		RenderVector(cam, allRenderers, mt);
		previousDepth = cam.GetDepth();

	}

	if (mainCam)
	{
		DiagRenderer::Instance().RenderAll(*mainCam);
	}
	
	Core::Instance().GetGraphicsAPI().ResetTextures();
	PostProcessor::Instance().UnbindFrameBuffer();	
	PostProcessor::Instance().RenderToScreen();

	glActiveTexture(GL_TEXTURE0);
	Core::Instance().GetGraphicsAPI().ResetTextures();
}



void RenderingEngine::SubmitRenderer(Renderer* rend)
{
	if (!rend->submitted)
	{
			
		allRenderers.push_back(rend);

		rend->submitted = true;
	}
}



void RenderingEngine::RenderBuffer(Camera* cam,MaterialType mt)
{
	Core::Instance().GetGraphicsAPI().ClearDepthBuffer();
	Core::Instance().GetGraphicsAPI().ClearColorBuffer();

	RenderVector(*cam, allRenderers, mt);	
	Core::Instance().GetGraphicsAPI().ResetTextures();

}

void RenderingEngine::RenderBuffer(MaterialType mt)
{

	Core::Instance().GetGraphicsAPI().ClearColorBuffer();
	Core::Instance().GetGraphicsAPI().ClearDepthBuffer();

	int previousDepth = 0;
	//Render opaque
	for (int camIndex = 0; camIndex < Camera::GetAllCameras().size(); camIndex++)
	{
		Camera& cam = *Camera::GetAllCameras()[camIndex];

		if (!cam.GetActive()) continue;
	
		if (previousDepth != cam.GetDepth())
		Core::Instance().GetGraphicsAPI().ClearDepthBuffer();

		RenderVector(cam, allRenderers,mt);
		previousDepth = cam.GetDepth();

	}
	Core::Instance().GetGraphicsAPI().ResetTextures();
}

void RenderingEngine::RenderBufferOverrideColor(Camera* camera, glm::vec3 color, MaterialType mt )
{
	RenderVectorOverrideColor(*camera, allRenderers, color, mt);

	Core::Instance().GetGraphicsAPI().ResetTextures();
}


void RenderingEngine::RenderVector(Camera& cam, std::vector<Renderer*>& r, MaterialType m)
{
	for (int i = 0; i < r.size(); i++)
	{
		if (cam.GetCullingMask() & r[i]->_parent->GetLayer()) //Check for culling mask
		{			
			//Logger::LogWarning("Rendering", r[i]->GetParent()->GetName());
			
			r[i]->GetMaterial(m).BindMaterial();		

			r[i]->OnPreRender(cam, &r[i]->GetMaterial(m).GetShader());
			r[i]->Render(cam);
			r[i]->OnPostRender(cam, &r[i]->GetMaterial(m).GetShader());
			r[i]->GetMaterial(m).UnbindMaterial();
			r[i]->submitted = 0;
		}
	}
}

void RenderingEngine::RenderVectorOverrideColor(Camera& cam, std::vector<Renderer*>& r, glm::vec3 color, MaterialType m)
{

	for (int i = 0; i < r.size(); i++)
	{
		if (cam.GetCullingMask() & r[i]->_parent->GetLayer()) //Check for culling mask
		{			
			r[i]->GetMaterial(m).BindMaterial();
			r[i]->GetMaterial(m).SetColor(color.x, color.y, color.z);
			r[i]->GetMaterial(m).GetShader().SetVec3("AmbientLight", LightManager::Instance().GetAmbientLight());
			r[i]->OnPreRender(cam, &r[i]->GetMaterial(m).GetShader());
			r[i]->Render(cam);
			r[i]->OnPostRender(cam, &r[i]->GetMaterial(m).GetShader());
			r[i]->GetMaterial(m).UnbindMaterial();
			r[i]->submitted = 0;

		}
	}
}

void RenderingEngine::ClearRendererList()
{
	allRenderers.clear();
	DiagRenderer::Instance().ClearAll();
}

