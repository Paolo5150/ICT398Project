#pragma once

#include <map>
#include <string>
#include "Scene.h"

/**
* @class SceneManager
* @brief Manages scenes in the game
*
*
* @author Paolo Ferri
* @version 01
* @date 21/03/2019
*
*
* @bug No known bugs.
*/
class SceneManager
{
public:
	/**
	* @brief Returns the scene manager instance
	*
	* @pre The scene manager instance exists
	* @post The scene manager instance is returned
	* @return The scene manager instance
	*/
	static SceneManager& Instance();

	/**
	* @brief Returns the current scene
	*
	* @pre The scene manager instance exists, the scene is not NULL
	* @post The current scene is returned
	* @return The current scene is returned
	*/
	Scene& GetCurrentScene();

	/**
	* @brief Add a new scene
	* All scenes should be added when the game is initialized
	* @pre The scene manager instance exists, the scene is not NULL
	* @post The scene is added to the list
	*/
	void AddScene(std::unique_ptr<Scene>& s);

	/**
	* @brief Load a new scene to be updated
	* @pre The scene is no null, The scene manager instance exists
	* @post The scene is loaded
	*/
	void LoadNewScene(std::string sceneName);

	/**
	* @brief Load a new scene to be updated
	* @pre The scene is no null, The scene manager instance exists
	* @post The scene is loaded
	*/
	void ReloadCurrent();

	/**
	* @brief Destroys all scenes from memory
	* @pre The scene manager instance exists
	* @post The scenes are destroyed
	*/
	void DestroyAllScenes();

	/**
	* @brief Destroy the scene manager instance
	*
	* @pre The camera object exists
	* @post The camera object is destroyed
	*/
	~SceneManager();

private:
	/**
	* @brief Creates scene manager instance
	*/
	SceneManager();


	SceneManager(const SceneManager& s) = delete;
	std::map<std::string, std::unique_ptr<Scene>> m_allScenes;

	/**
	* @brief The current scene
	*/
	Scene* m_currentScene;

};

