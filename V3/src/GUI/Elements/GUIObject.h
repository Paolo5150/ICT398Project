#pragma once
#include "..\..\Core\GameObject.h"
#include "..\imgui_impl_glfw.h"
#include "..\imgui_impl_opengl3.h"
#include "..\..\Core\Window.h"
#include "..\..\Events\EventDispatcher.h"

#include <functional>
/**
* @class GUIObject
* @brief Parent abstract class to all GUI objects

* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class GUIObject : public InternalAsset
{
public:
	/**
	* @brief		Creates a GUIObject
	*
	* @post			The GUIObject object is created
	*/
	GUIObject(std::string uniqueName) : name(uniqueName) {
		isActive = 1;

	};

	/**
	* @brief		Destroy a GUIObject
	*
	* @pre			The GUIObject must exist
	* @post			The GUIObject object is destroyed
	*/
	virtual ~GUIObject() {/* Logger::LogInfo("Deleted GUIobject", name); */};

	/**
	* @brief		The position on the screen
	*/
	glm::vec2 position;

	/**
	* @brief		The position on the screen
	*/
	glm::vec2 pixelPosition;

	/**
	* @brief		The size of the element
	*/
	glm::vec2 size;

	/**
	* @brief		The size of the element
	*/
	glm::vec2 pixelSize;

	/**
	* @brief		Whether the GUIObject is active or not
	*/
	bool isActive;

	bool resizable;

	std::string name;

	virtual void Render() = 0;

	void CalculateSizePosition()
	{
		int winX, winY;
		Window::Instance().GetWindowSize(winX, winY);
		if (!resizable)
		{
			winX = winY = 100;
		}

		pixelPosition = glm::vec2(position.x * winX / 100, position.y * winY / 100);
		pixelSize.x = size.x * winX / 100;
		pixelSize.y = size.y * winY / 100;
	}



};


