#pragma once
#include  "GUIObject.h"
#include "..\..\Utils\FileUtils.h"
#include "..\GUIManager.h"
#include "..\..\Utils\Maths.h"

/**
* @class GUIText
* @brief Defines a GUI element for displaying text

* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class GUIBar : public GUIObject
{
public:
	/**
	* @brief		Creates a GUI text
	*
	* @post					The GUIText object is created
	* @param message		The text to display
	* @param posX			The X position on the screen
	* @param posY			The Y position on the screen
	* @param r				The red channel of the color
	* @param g				The green channel of the color
	* @param b				The blue channel of the color
	* @param isPercentage	Wether the details provided are percentage of the current window
	*/
	GUIBar(std::string uniqueName, float sizeX = 50, float sizeY = 50, float posX = 0, float posY = 0, bool isPercentage = false) : GUIObject(uniqueName){
		position.x = posX;
		position.y = posY;
		size.x = sizeX;
		size.y = sizeY;
		resizable = isPercentage;
		percentage = 0.5;
		CalculateSizePosition();
		foregroundColor = glm::vec4(1, 0, 0, 0.5);
		backgorundColor = glm::vec4(1, 1, 1, 0.5);
		textColor = glm::vec4(1,1,0, 1.0);
		text = "";		
	}

	/**
	* @brief		Destroy the GUIText
	*
	* @pre			The GUIText object must exist
	* @post			The GUIText object is destroyed
	*/
	~GUIBar() {

	};

	/**
	* @brief		The mtext color
	*/
	glm::vec4 backgorundColor;
	glm::vec4 foregroundColor;
	glm::vec4 textColor;

	std::string text;

	float percentage;

	ImGuiCol col;


	/**
	* @brief		Render the GUI object
	*/
	void Render() override
	{

		ImGui::SetCursorPosX(pixelPosition.x);
		ImGui::SetCursorPosY(pixelPosition.y);
		ImGui::PushStyleColor(ImGuiCol_PlotHistogram, Maths::vec4ToImVec4(foregroundColor));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, Maths::vec4ToImVec4(backgorundColor));
		ImGui::PushStyleColor(ImGuiCol_Text, Maths::vec4ToImVec4(textColor));

		ImGui::ProgressBar(percentage, ImVec2(pixelSize.x, pixelSize.y),text.c_str());
		ImGui::PopStyleColor(3);

	}

};