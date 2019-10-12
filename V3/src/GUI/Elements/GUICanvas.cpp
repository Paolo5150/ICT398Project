#include "pch.h"
#include "GUICanvas.h"
#include "imgui.h"
#include "..\imgui_impl_glfw.h"
#include "..\imgui_impl_opengl3.h"

GUICanvas::GUICanvas(std::string name) : _name(name)
{
	isActive = true;
}


GUICanvas::~GUICanvas()
{
	//Logger::LogInfo("Deleted canvas", _name);
	allGUIObjects.clear();
}

void GUICanvas::Render()
{
	if (!isActive) return;

	ImGui::SetNextWindowPos(ImVec2(startingPos.x, startingPos.y));
	ImGui::SetNextWindowSize(ImVec2(widthPixels, heightPixels));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(backgroundColor.x,backgroundColor.y,backgroundColor.z,backgroundColor.w));

	ImGui::Begin(_name.c_str(), (bool*)1,flags);

	for (auto it = allGUIObjects.begin(); it != allGUIObjects.end(); it++)
	{
		if((*it).second->isActive)
			(*it).second->Render();
	}

	//Draw elements
	ImGui::End();
	ImGui::PopStyleColor();
}

void GUICanvas::AddGUIObject(GUIObject* obj)
{
	allGUIObjects[obj->name] = std::unique_ptr<GUIObject>(obj);
}

void GUICanvas::RemoveGUIOBject(std::string name)
{
	allGUIObjects.erase(name);
}


GUIObject* GUICanvas::GetGUIObjectByName(std::string name)
{
	auto it = allGUIObjects.find(name);

	if (it != allGUIObjects.end())
		return (*it).second.get();
	else
		return nullptr;
}



void GUICanvas::AddFlag(int flag)
{
	flags |= flag;
}
