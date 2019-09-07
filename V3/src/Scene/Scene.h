#pragma once
#include "..\Core\GameObject.h"
#include "..\Core\Timer.h"
#include "..\Core\Input.h"
#include "..\Core\Logger.h"
#include "SceneManager.h"
#include "..\Core\CameraPerspective.h"
#include "..\Core\Window.h"
#include "..\Utils\ContentManager.h"
#include "..\Prefabs/MainCamera.h"
#include "..\Events/ApplicationEvents.h"
#include "..\Lighting\DirectionalLight.h"
#include "..\Lighting\PointLight.h"
#include "..\Rendering\SkyBox.h"
#include "..\Physics\PhysicsWorld.h"
#include "..\Physics\CollisionLayer.h"
#include "..\Lighting\LightingManager.h"
#include "..\GUI\GUIManager.h"
#include <map>
#include <vector>
#include <list>
#include <string>

/**
* @class Scene
* @brief Generic abstract class for a scene
*
*
* @author Paolo Ferri
* @version 01
* @date 17/04/2019
*
*
* @bug No known bugs.
*/

class Scene
{
public:
	friend class SceneManager;

	/**
	* @brief		Creates the scene object
	*
	* @pre			The scene object does not exist
	* @post			The scene object is created.
	* @param n		The scene nae
	*/
	Scene(std::string n);

	/**
	* @brief		Destroy the scene object
	*
	* @pre			The scene object must exist
	* @post			The scene object is destroyed
	*/
	virtual ~Scene() { Logger::LogError("Destroyed scene", name); };

	/**
	* @brief		Add a gameobject to the list
	*
	* @pre			The scene object must exist, the gameobject exists
	* @post			The gameobject is added to the list for updating
	* @param go		The gameobject to be added
	*/
	void AddGameObject(GameObject* go);

		/**
	* @brief		Add a gameobject to the list
	*
	* @pre			The scene object must exist, the gameobject exists
	* @post			The gameobject is added to the list for updating
	* @param go		The gameobject to be added
	*/
	void AddGameObject(std::unique_ptr<GameObject> go);

	/**
	* @brief		Loads the assets needed for this scene.
	*
	* @pre			The external assets must be available.
	*/
	virtual void LoadAssets() = 0;


	/**
	* @brief		Unload the assets needed for this scene.
	*
	* @post			The assets are removed from memory.
	*/
	void UnloadAssets();

	/**
	* @brief		Callback used when exiting the scene.
	*
	* @post			The scene is exited.
	*/
	virtual void QuitScene() = 0;

	/**
	* @brief		Initialize objects in the scene.
	*/
	virtual void Initialize() = 0;


	/**
	* @brief		Initialize objects in the scene.
	*/
	virtual void Start();


	/**
	* @brief		Update objects in the scene in the Logic Update Loop
	*/
	virtual void LogicUpdate() = 0;


	/**
	* @brief		Update objects in the scene in the Engine Update Loop
	*/
	virtual void EngineUpdate();

	/**
	* @brief		Update objects in the scene in the Engine Update Loop
	*				Mostly used to clear the list form dead gameobjects
	*/
	virtual void LateUpdate() ;

	/**
	* @brief		Returns whether the scene is ready
	* @return		Whether the scene has been loaded and ready
	*/
	bool GetIsReady() { return m_isReady; };

	/**
	* @brief		Returns thr skybox of the scene
	*/
	Skybox* GetSkyBox(){ return skybox.get(); }

	/**
	* @brief		The name of the scene
	*/
	std::string name;

	std::vector<GameObject*> GetGameobjectsByName(std::string name);

	template <class T>
	std::vector<T*> GetGameobjectsByName(std::string name);

	bool RemoveGameobjectsByName(std::string name); //returns true if any objects were removed

	void LoadGameObjectsFromFile(std::string filePath);

protected:
	/**
	* @brief		The list of gameobjects in the scene
	*/
	std::list<std::unique_ptr<GameObject>> m_allGameObjects;

	/**
	* @brief		Whether the scne is ready
	*/
	bool m_isReady;

	/**
	* @brief		The skybox of the scene
	*/
	std::unique_ptr<Skybox> skybox;

};

template <class T>
std::vector<T*> Scene::GetGameobjectsByName(std::string name)
{
	std::vector<T*> r;

	for (auto it = m_allGameObjects.begin(); it != m_allGameObjects.end(); it++)
	{
		if ((*it)->GetName() == name)
			r.push_back((T*)(*it).get());
	}

	return r;
}