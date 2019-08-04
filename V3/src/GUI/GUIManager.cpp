#include "pch.h"
#include "GUIManager.h"
#include "..\Core\Window.h"
#include "..\Events\ApplicationEvents.h"
#include "..\Core\Core.h"
#include <thread>

#include "imgui.h"
#include "..\GUI\imgui_impl_glfw.h"
#include "..\GUI\imgui_impl_opengl3.h"


GUIManager& GUIManager::Instance()
{
	static GUIManager instance;
	return instance;
}

GUIManager::~GUIManager()
{}

void GUIManager::Initialize()
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(Window::Instance().window.get(), false);
	ImGui_ImplOpenGL3_Init("#version 430");

	// Load fonts

	// Add main canvas
	GUICanvas* mainCanvas = new GUICanvas("MainCanvas");
	mainCanvas->SetBackgroundColor(1, 0, 0, 0);
	mainCanvas->AddFlag(ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
	
	int x, y;
	Window::Instance().GetWindowSize(x, y);
	
	mainCanvas->SetSize(x, y);
	
	AddCanvas(mainCanvas);
}



void GUIManager::Refresh()
{


}

void GUIManager::AddCanvas(GUICanvas* canvas)
{
	allCanvas[canvas->GetName()] = std::unique_ptr<GUICanvas>(canvas);
}


void GUIManager::Render(bool forceRefresh, bool forceClear)
{


	if (forceClear)
		Core::Instance().GetGraphicsAPI().ClearColorBuffer();


	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	
	// Render all canvas
	auto it = allCanvas.begin();

	for (; it != allCanvas.end(); it++)
		(*it).second->Render();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (forceRefresh)
		Window::Instance().Refresh();
}



void GUIManager::Shutdown()
{
	allCanvas.clear();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

}

