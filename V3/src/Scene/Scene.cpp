#include "pch.h"
#include "Scene.h"
#include "SceneManager.h"
#include "..\Core\Logger.h"
#include "..\Utils\ContentManager.h"
#include "..\Core\Input.h"

Scene::Scene(std::string n) : name(n)
{
	//skybox = nullptr;
}

void Scene::AddGameObject(std::unique_ptr<GameObject> go)
{
	auto it = m_allGameObjects.begin();

	for (; it != m_allGameObjects.end(); it++)
	{
		if ((*it).get() == go.get())
			return;
	}

	m_allGameObjects.push_back(std::move(go));
	go->OnAddToScene(*this);

	auto child = go->GetChildList().begin();

	for (; child != go->GetChildList().end(); child++)
		AddGameObject(*child);

	//go->transform.Update();
}

void Scene::AddGameObject(GameObject* go)
{
	auto it = m_allGameObjects.begin();

	for (; it != m_allGameObjects.end(); it++)
		{
			if ((*it).get() == go)
				return;
		}

	std::unique_ptr<GameObject> m_unique = std::unique_ptr<GameObject>(go);
	m_allGameObjects.push_back(std::move(m_unique));
	go->OnAddToScene(*this);

	auto child = go->GetChildList().begin();

	for (; child != go->GetChildList().end(); child++)
			AddGameObject(*child);

	//go->transform.Update();
}

void Scene::Start()
{
	auto it = m_allGameObjects.begin();

	for (; it != m_allGameObjects.end(); it++)
	{
	
		(*it)->Start();
	}
}

void Scene::UnloadAssets()
{
	ContentManager::Instance().Unload<Model>();
	ContentManager::Instance().Unload<Texture2D>();
	ContentManager::Instance().Unload<Mesh>();
	ContentManager::Instance().Unload<CubeMap>();


}



void Scene::LateUpdate()
{
	// Delete ToBeDestroyed gameobjects here
	//Logger::LogInfo("Late update");
	{

		auto it = m_allGameObjects.begin();

		for (; it != m_allGameObjects.end(); it++)
		{
			(*it)->LateUpdate();
		}
	}


	auto it = m_allGameObjects.begin();
	for (; it != m_allGameObjects.end();)
	{
		if ((*it)->GetToBeDestroyed())
		{
			it = m_allGameObjects.erase(it);
		}
		else
			it++;
	}	
}

void Scene::EngineUpdate()
{
	//Logger::LogError("Updating", m_allGameObjects.size());
	if (skybox != nullptr)
		skybox->EngineUpdate(); // Call engine update to the skybox so the cube (its renderer component) is sent to the rendering engine for rendering

	auto it = m_allGameObjects.begin();

	for (; it != m_allGameObjects.end(); it++)
	{
		(*it)->EngineUpdate();
	}
}

void Scene::LogicUpdate()
{
	auto it = m_allGameObjects.begin();

	for (; it != m_allGameObjects.end(); it++)
	{
		if((*it)->GetActive() == true)
			(*it)->Update();
	}

	PhysicsWorld::Instance().Update();
}

void Scene::QuitScene()
{
	m_allGameObjects.clear();
	skybox.reset();

	Input::Update();
}

std::vector<GameObject*> Scene::GetGameobjectsByName(std::string name)
{
	std::vector<GameObject*> r;

	for (auto it = m_allGameObjects.begin(); it != m_allGameObjects.end(); it++)
	{
		if ((*it)->GetName() == name)
			r.push_back((*it).get());
	}
	 
	return r;
}

bool Scene::RemoveGameobjectsByName(std::string name)
{
	bool deleted = false;

	for (auto it = m_allGameObjects.begin(); it != m_allGameObjects.end(); it++)
	{
		if ((*it)->GetName() == name)
		{
			(*it)->FlagToBeDestroyed();
		}
	}

	return deleted;
}