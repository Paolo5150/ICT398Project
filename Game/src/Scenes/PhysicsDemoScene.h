#pragma once
#include "C:\Users\Dutchy\Documents\ICT398Project\V3\src\Scene\Scene.h"
class PhysicsDemoScene :
	public Scene
{
public:
	PhysicsDemoScene();
	~PhysicsDemoScene();
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
};

