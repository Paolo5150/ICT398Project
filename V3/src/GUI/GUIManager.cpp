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

	

}



void GUIManager::Refresh()
{


}

void GUIManager::AddGUIObject(GUIObject* gobj, bool preserve)
{


}


void GUIManager::Render(bool forceRefresh, bool forceClear)
{


	if (forceClear)
		Core::Instance().GetGraphicsAPI().ClearColorBuffer();


	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowPos(ImVec2(0, 50));

	int x, y;
	Window::Instance().GetWindowSize(x, y);
	ImGui::SetNextWindowSize(ImVec2(100,100));

	ImGui::Begin("W1");
	ImGui::Text("Win 1");
	ImGui::End();


	ImGui::SetNextWindowPos(ImVec2(150, 0));
	ImGui::SetNextWindowSize(ImVec2(100, 100));
	ImGui::Begin("W2");
	ImGui::Text("Win 2");

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (forceRefresh)
		Window::Instance().Refresh();



}


void GUIManager::SelectFont(std::string fontName)
{

}


void GUIManager::DeleteGUIObjects(bool preservedToo)
{

	

}


void GUIManager::SetBackgroundColor(float r, float g, float b, float a)
{

}
void GUIManager::Shutdown()
{

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

}

