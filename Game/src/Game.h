#pragma once
#include "Core/Application.h"

/**
* @class Game
* @brief The application instance
*
*
* @author Paolo Ferri
* @version 01
* @date 17/03/2019
*
*
* @bug No known bugs.
*/

class Game : public Application
{

public:
	/**
	* @brief		Creates the Game object
	*
	* @pre			The Game object does not exist
	* @post			The Game object is created.
	*
	*@param appName The application title
	*/
	Game(std::string appName);

	/**
	* @brief		Destroys scenes of this application
	*
	* @pre			The scenes are loaded
	* @post			The scenes are destroyed
	*
	*/
	virtual ~Game();

	/**
	* @brief		Loads the scenes and initialize first one
	*
	* @pre			The scenes objects have been defined
	* @post			The first scene is loaded and run
	*
	*/
	virtual void AppInitialize() override;

	/**
	* @brief		Main loop, update current scene
	*
	*/
	virtual void AppLogicUpdate() override;	

	/**
	* @brief		Destroy scenes and clean up.
	*
	*/
	virtual void AppShutdown() override;


};

/**
* @brief		Function definition for extern in Core.
*
*/
std::unique_ptr<Application> CreateApplication();