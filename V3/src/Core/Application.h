#pragma once
#include <string>



/**
* @class Application
* @brief Generic abstract class defines an engine application
*
*
* @author Paolo Ferri
* @version 01
* @date 17/03/2019
*
*
* @bug No known bugs.
*/
class Application 
{

public:
	friend class Core;


	/**
	* @brief The application name
	*/
	std::string name;

	/**
	* @brief		Creates the application object
	*
	* @pre			The application object does not exist
	* @post			The application object is created.
	*
	*/
	Application();

	/**
	* @brief		Initialize the application (overridable).
	*/
	virtual void AppInitialize(){};

	/**
	* @brief		Update the application using the logic update loop (overridable).
	*/
	virtual void AppLogicUpdate();

	/**
	* @brief		Close the application (overridable).
	*/
	virtual void AppShutdown(){};

	/**
	* @brief		Update the application using the engine update loop (overridable).
	*/
	virtual void AppEngineUpdate();

	/**
	* @brief		Update the application using the late update loop (overridable).
	*/
	virtual void AppLateUpdate();

	/**
	* @brief		Destroy the application (overridable)
	*/
	virtual ~Application() {};
};