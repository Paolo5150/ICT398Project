#include "pch.h"
#include "GUICanvas.h"
#include "GUIObject.h"
#include "imgui.h"
#include "..\imgui_impl_glfw.h"
#include "..\imgui_impl_opengl3.h"

GUICanvas::GUICanvas(std::string name) : _name(name)
{

}


GUICanvas::~GUICanvas()
{

}

void GUICanvas::Render()
{
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


void GUICanvas::AddFlag(int flag)
{
	flags |= flag;
}
