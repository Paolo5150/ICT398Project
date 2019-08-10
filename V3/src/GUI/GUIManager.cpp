#include "pch.h"
#include "GUIManager.h"
#include "..\Core\Window.h"
#include "..\Events\ApplicationEvents.h"
#include "..\Events\WindowEvents.h"

#include "..\Core\Core.h"
#include <thread>
#include "Elements/GUIButton.h"
#include "imgui.h"
#include "..\GUI\imgui_impl_glfw.h"
#include "..\GUI\imgui_impl_opengl3.h"


GUIManager& GUIManager::Instance()
{
	static GUIManager instance;
	return instance;
}

GUIManager::~GUIManager()
{
	allCanvas.clear();
}

void GUIManager::Initialize()
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(Window::Instance().window.get(), false);
	ImGui_ImplOpenGL3_Init("#version 430");

	// When the scene changes, removes all canvas and recreate the main one as per default
	EventDispatcher::Instance().SubscribeCallback<SceneChangedEvent>([this](Event* e) {
	allCanvas.clear();
		CreateAndAddMainCanvas();
		Logger::LogInfo("GUIManager reset");
		return 0;
	});
	
	EventDispatcher::Instance().SubscribeCallback<WindowResizeEvent>([this](Event* e) {

		// Resize canvas
		return 0;
	});

}

void GUIManager::CreateAndAddMainCanvas()
{
	// Add main canvas
	GUICanvas* mainCanvas = new GUICanvas("MainCanvas");
	mainCanvas->SetBackgroundColor(1, 0, 0, 0);
	mainCanvas->AddFlag(ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
	mainCanvas->AddGUIObject(new GUIButton("Test", "Click", []() { Logger::LogInfo("Clicked!"); }));
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

GUICanvas* GUIManager::GetCanvasByName(std::string name)
{
	auto it = allCanvas.find(name);

	if (it != allCanvas.end())
		return it->second.get();
	else
		return nullptr;
}

void GUIManager::RemoveCanvas(std::string name)
{
	auto it = allCanvas.find(name);

	if (it != allCanvas.end())
	{
		allCanvas.erase(name);
	}
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

