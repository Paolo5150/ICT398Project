#include "pch.h"
#include "PostProcecssStage.h"
#include "Shader.h"
#include "..\Core\Window.h"
#include "..\Core\Core.h"

PostProcessStage::PostProcessStage(std::string name, Shader* shader, Mesh* quadMesh, bool HDR_FBO)
{
	this->shader = shader;

	int w, h;
	Window::Instance().GetWindowSize(w, h);

	buffer = Core::Instance().GetGraphicsAPI().CreateFrameBuffer(name, w, h,1,HDR_FBO);
	this->quadMesh = quadMesh;

}

Texture2D* PostProcessStage::Process(Texture2D* previous)
{
	buffer->Bind();
	Core::Instance().GetGraphicsAPI().ClearColorBuffer();
	Core::Instance().GetGraphicsAPI().ClearDepthBuffer();

	shader->Bind();
	previous->Bind();
	shader->SetInt("sceneTexture", 0);
	quadMesh->Render();

	buffer->Unbind();
	return buffer->GetColorTexture();
}
