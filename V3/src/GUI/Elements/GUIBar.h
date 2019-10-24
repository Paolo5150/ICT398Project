#pragma once
#include  "GUIObject.h"
#include "..\..\Utils\FileUtils.h"
#include "..\GUIManager.h"
#include "..\..\Utils\Maths.h"

/**
* @class GUIBar
* @brief Defines a GUI element for displaying a progress bar

* @author Paolo Ferri
* @version 01
* @date 15/09/2019
*
*
* @bug No known bugs.
*/
class GUIBar : public GUIObject
{
public:
	/**
	* @brief					Creates a GUI bar
	* @param sizeX				Width
	* @param sizeY				Height
	* @param posX				Position X on the screen
	* @param posY				Position Y on the screen
	* @param isPercentage		Whether the parameters specified are % of the screen size
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
	* @brief		Destroy the GUIBar
	*
	* @pre			The GUIBar object must exist
	* @post			The GUIBar object is destroyed
	*/
	~GUIBar() {

	};

	/**
	* @brief		The bar background color
	*/
	glm::vec4 backgorundColor;

	/**
	* @brief		The bar foreground color
	*/
	glm::vec4 foregroundColor;

	/**
	* @brief		The bar text color
	*/
	glm::vec4 textColor;

	/**
	* @brief		The text message
	*/
	std::string text;

	/**
	* @brief		The percentage (0 - 1) that determines the bar fill
	*/
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