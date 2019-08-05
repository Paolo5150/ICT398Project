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
class GUIButton : public GUIObject
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
	GUIButton(std::string uniqueName, std::string message, std::function<void()> onclick, std::string fontName = "defaultFont", float fontSize = 1, float sizeX = 50, float sizeY = 50, float posX = 0, float posY = 0, float r = 1, float g = 1, float b = 1, bool isPercentage = false) : GUIObject(uniqueName), _message(message) {
		_color = glm::vec4(r, g, b, 1);
		position.x = posX;
		position.y = posY;
		size.x = sizeX;
		size.y = sizeY;
		resizable = isPercentage;
		CalculateSizePosition();
		fontScale = fontSize;
		this->fontName = fontName;
		this->OnClick = onclick;



	}

	/**
	* @brief		Destroy the GUIText
	*
	* @pre			The GUIText object must exist
	* @post			The GUIText object is destroyed
	*/
	~GUIButton() {
		OnClick = nullptr;
	};

	std::function<void()> OnClick;

	/**
	* @brief		The message to be displayed
	*/
	std::string _message;

	/**
	* @brief		The mtext color
	*/
	glm::vec4 _color;

	/**
	* @brief The name of the font used
	*/
	std::string fontName;

	/**
	* @brief The scale of the text
	*/
	float fontScale;

	/**
	* @brief		Render the GUI object
	*/
	void Render() override
	{
		ImGui::SetCursorPosX(pixelPosition.x);
		ImGui::SetCursorPosY(pixelPosition.y);


		//if (ImGui::ColorButton(_message.c_str(), ImVec4(_color.r, _color.g, _color.b, _color.a), ImGuiColorEditFlags_NoTooltip, ImVec2(size.x, size.y)))
		//	OnClick();
		ImGui::SetWindowFontScale(fontScale);

		if (ImGui::Button(_message.c_str(), ImVec2(pixelSize.x, pixelSize.y)))
		{
			OnClick();
		}

	}

};