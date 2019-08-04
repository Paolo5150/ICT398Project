#pragma once

#include <string>
#include <list>
#include <unordered_map>
#include "..\..\Utils\Maths.h"

class GUIObject;

class GUICanvas
{

public:
	GUICanvas(std::string name);
	~GUICanvas();
	void Render();
	void AddFlag(int flag);
	std::string GetName() { return _name; }

	void SetWidthPixels(unsigned w) { widthPixels = w; }
	void SetHeightPixels(unsigned h) { heightPixels = h; }
	void SetSize(unsigned w, unsigned h) { widthPixels = w; heightPixels = h;}
	void SetStartingPosition(unsigned x, unsigned y) { startingPos.x = x; startingPos.y = y; }
	void SetBackgroundColor(float r, float g, float b, float a) { backgroundColor.x = r; backgroundColor.y = g; backgroundColor.z = b; backgroundColor.a = a; }

	void AddGUIObject(GUIObject* obj);


private:
	std::string _name;
	unsigned widthPixels;
	unsigned heightPixels;
	ImGuiWindowFlags flags;
	glm::vec2 startingPos;
	glm::vec4 backgroundColor;

	std::unordered_map<std::string,std::unique_ptr<GUIObject>> allGUIObjects;

};