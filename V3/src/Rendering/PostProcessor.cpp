#include "pch.h"
#include "PostProcessor.h"
#include "..\Utils\ContentManager.h"
#include "..\Core\Core.h"

PostProcessor::PostProcessor()
{

	EventDispatcher::Instance().SubscribeCallback<WindowResizeEvent>([this](Event* e) {

		WindowResizeEvent* wc = dynamic_cast<WindowResizeEvent*>(e);

			sceneTexture->ResizeTexture(wc->width, wc->height);
			sceneTexture->ResizeTexture(wc->width, wc->height);

			for (auto it = postsProcessStages.begin(); it != postsProcessStages.end(); it++)
			{
				it->buffer->ResizeTexture(wc->width, wc->height);
			}

		return 0;
	});
	//Create quad manually
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

	int w, h;
	Window::Instance().GetWindowSize(w, h);

	sceneTexture = Core::Instance().GetGraphicsAPI().CreateFrameBuffer("PostProcessFB", w, h);
	quadMesh = std::unique_ptr<Mesh>(new Mesh(vertices, indices));
	currentPostProcessShader = ContentManager::Instance().GetAsset<Shader>("PostProcess_basic");

	//Add Stages
	postsProcessStages.emplace_back("PostProcessHDR", ContentManager::Instance().GetAsset<Shader>("PostProcess_hdr"), quadMesh.get(),true);
	
}

PostProcessor& PostProcessor::Instance()
{
	static PostProcessor instance;
	return instance;
}

void PostProcessor::SetShader(std::string shader)
{
	currentPostProcessShader = ContentManager::Instance().GetAsset<Shader>(shader);
}

void PostProcessor::RenderToScreen()
{
	Texture2D* t = sceneTexture->GetColorTexture();
	for (auto it = postsProcessStages.begin(); it != postsProcessStages.end(); it++)
	{
		t = it->Process(t);
	}

	glActiveTexture(GL_TEXTURE0);
	currentPostProcessShader->Bind();
	t->Bind();
	currentPostProcessShader->SetInt("sceneTexture", 0);
	quadMesh->Render();
}



