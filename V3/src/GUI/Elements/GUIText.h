#pragma once
#include  "GUIObject.h"
#include "..\..\Utils\FileUtils.h"
#include "..\GUIManager.h"

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
class GUIText : public GUIObject
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
	GUIText(std::string uniqueName, std::string text, float posX, float posY, glm::vec3 color,float fontSize,bool isPercentage) : GUIObject(uniqueName) {
		_color = glm::vec4(color.x,color.y,color.z, 1);
		position.x = posX;
		position.y = posY;
		message = text;
		resizable = isPercentage;
		this->fontSize = fontSize;
		CalculateSizePosition();
	}

	/**
	* @brief		Destroy the GUIText
	*
	* @pre			The GUIText object must exist
	* @post			The GUIText object is destroyed
	*/
	~GUIText() {

	};
	std::string message;

	/**
	* @brief		The mtext color
	*/
	glm::vec4 _color;

	float fontSize;

	/**
	* @brief		Render the GUI object
	*/
	void Render() override
	{
		ImGui::SetCursorPosX(pixelPosition.x);
		ImGui::SetCursorPosY(pixelPosition.y);
		ImGui::SetWindowFontScale(fontSize);
		ImGui::Text(message.c_str());
		ImGui::SetWindowFontScale(1.0);


	}

};