#pragma once
#include "Scene/Scene.h"

#include "Components/PathFinder.h"


class GUIImage;
class Player;
class GUIProgressBar;
/**
* @class MainScene
* @brief The application main scene
*
*
* @author Paolo Ferri
* @version 01
* @date 07/03/2019
*
*
* @bug No known bugs.
*/
class MainScene : public Scene
{
public:
	enum SCENE_STATES
	{
		PLAYING,
		GAMEOVER
	};
	/**
	* @brief		Creates the MainScene object
	*
	* @pre			The MainScene object does not exist
	* @post			The MainScene object is created.
	*/
	MainScene();

	/**
	* @brief		Loads the assets needed for this scene.
	*
	* @pre			The external assets must be available.
	*/
	virtual void LoadAssets() override;

	/**
	* @brief		Callback used when exiting the scene.
	*
	* @post			The scene is exited.
	*/
	virtual void QuitScene() override;

	/**
	* @brief		Initialize objects in the scene.
	*/
	void Initialize() override;

	void Start() override;

	/**
	* @brief		Update objects in the scene.
	*/
	virtual void LogicUpdate() override;

	MainCamera* cam;

	glm::vec3 pathGoal = glm::vec3(0, 0, 0); //Temporary for debugging pathfinding
	std::vector<PathFinder*> pathfinders; //Temporary for debugging pathfinding
	std::vector<glm::vec3> locs; //Temporary for debugging pathfinding
	glm::vec3 nextNode = glm::vec3(0, 0, 0);

};