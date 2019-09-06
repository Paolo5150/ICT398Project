#pragma once

#include <list>
#include <unordered_map>
#include "..\Events\EventDispatcher.h"
#include "Elements/GUICanvas.h"
class GUIObject;
class GUIText;
class GUIImage;

/**
* @class GUIManager
* @brief Manages all GUIObjects and renders them
* This class is a facade for the ImGUI Library
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class GUIManager
{
public:
	/**
	* @brief		Returns the GUIManager instance
	*
	* @post			The GUIManager instance is returned
	*/
	static GUIManager& Instance();

	/**
	* @brief		The GUIManager is destroyed
	* @pre			The GUIManager must exist
	* @post			The GUIManager instance is destroyed
	*/
	~GUIManager();

	/**
	* @brief		Initialize the GUIManager, initialize the library
	* @pre			The library is installed
	* @post			The GUIManager instance is initialized
	*/
	void Initialize();


	/**
	* @brief		Shutdown the GUIManager, close library
	* @pre			The GUIManager instance must exist
	* @post			The GUIManager is shut down
	*/
	void Shutdown();

	/**
	* @brief				Render all the GUIObjects submitted
	* @pre					The GUIObjects in the list must exist
	* @post					TThe GUIObjects in the list are rendered on the screen
	* @param forceRefresh	Whether the window will be refreshed
	* @param forceClear		Whether the window will be cleared
	*/
	void Render(bool forceRefresh = false, bool forceClear = false);



	/**
	* @brief				Add the GUIObjects to the ImGui list
	* @pre					The GUIManager instance must exist
	* @post					The GUIObjects are added to the ImGui render list
	*/
	void Refresh();

	void AddCanvas(GUICanvas* canvas);
	void RemoveCanvas(std::string name);

	GUICanvas* GetCanvasByName(std::string name);

	void SetColorBuffer(float r, float g, float b);

private:


	std::unordered_map<std::string, std::unique_ptr<GUICanvas>> allCanvas;

	/**
	* @brief		Create the GUIManager instance
	*
	* @post			The GUIManager instance is created
	*/
	GUIManager() {};

	void CreateAndAddMainCanvas();

};


