#pragma once

#include "Window.h"
#include "Logger.h"
#include "Timer.h"
#include "Application.h"
#include "..\Rendering\GraphicsAPI.h"
#include <iostream>


extern "C++" std::unique_ptr<Application> CreateApplication();

/**
* @class Core
* @brief The core of the engine
*
* Manages loops and timer
*
* @author Paolo Ferri
* @version 01
* @date 12/03/2019
*
*
* @bug No known bugs.
*/
class Core
{
public:
	/**
	* @brief Get the singleton instance
	*/
	static Core& Instance();

	/**
	* @brief Initialize the engine
	* Create game instances, initialize manager, pre load common assets
	* Displays the splash screen, set up timer
	*
	* @pre No application is running
	* @post The engine is ready and the application isrunning
	*/
	void Initialize();

	/**
	* @brief Run the engine loops
	* Update the timer to send loop and render events
	*
	* @pre The engine is not running
	* @post The engine is running
	*/
	void Run();

	/**
	* @brief Unload all assets, close libraries, shutdown engine
	*
	* @pre The engine is running
	* @post The engine is not running
	*/
	void Shutdown();

	/**
	* @brief Logic update loop
	*
	* Used to update gameobjects
	*
	* @param e The event dispatched
	*/
	bool LogicUpdate(Event* e);

	/**
	* @brief Engine update loop
	*
	* Used for engine specific update tasks (eg. send renderer to rendering engine)
	*
	* @param e The event dispatched
	*/
	bool EngineUpdate(Event* e);

	/**
	* @brief Engine late loop
	*
	* Called after rendering, used mostly to clean scene from dead objects
	*
	* @param e The event dispatched
	*/
	bool LateUpdate(Event* e);

	/**
	* @brief Rendering loop
	*
	* Render the current scene via rendering engine
	*
	* @param e The event dispatched
	*/
	bool Render(Event* e);


	/**
	* @brief Get the current running application
	*/
	Application& GetRunningApplication() { return *m_runningApplication; }

	GraphicsAPI&  GetGraphicsAPI() { return *m_graphicsAPI; }

	/**
	* @brief Shutdown the engine and destroy it.
	*
	* @pre The engine exists
	* @post The engine is destroyed
	*/
	~Core();

	/**
	* @brief Return whether the engine is currently running
	*/
	bool IsRunning();


private:

	/**
	* @brief Create the engine instance
	* 
	* @pre The engine instance does not exist
	* @post The engine instance eis created
	*/
	Core();
	Core& operator=(const Core& other) = delete;
	Core(const Core& other) = delete;

	/**
	* @brief The current running app
	*/
	std::unique_ptr<Application> m_runningApplication;

	std::unique_ptr<GraphicsAPI> m_graphicsAPI;

	/**
	* @brief Whtether the engine is running
	*/
	bool m_isRunning;


	/**
	* @brief The text displayed on the splash screen
	*/
	GUIText* loading;

	/**
	* @brief Load assets to be used throughout the entire engine
	*
	* @pre The assets are not loaded
	* @post The assets are loaded into the engine for use
	*/
	void LoadBasicAssets();


};