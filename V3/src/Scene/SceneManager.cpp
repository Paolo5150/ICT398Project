#pragma once#pragma once
#include "pch.h"
#include "SceneManager.h"
#include <assert.h>
#include "..\Core\Logger.h"
#include "..\Events\EventDispatcher.h"
#include "..\Events\ApplicationEvents.h"
#include "Scene.h"
#include "..\Core\Input.h"
#include <stdlib.h>
SceneManager::SceneManager()
{
	
}

SceneManager& SceneManager::Instance()
{
	static SceneManager instance;
	return instance;
}

Scene& SceneManager::GetCurrentScene()
{	
	return *m_currentScene;
}
void SceneManager::AddScene(std::unique_ptr<Scene>& s)
{
	auto it = m_allScenes.find(s->name);

	if(it != m_allScenes.end())
	{ 
		Logger::LogError("ERROR: A scene named", s->name, "already exists! Program will crash brutally now");
		exit(EXIT_FAILURE);
	}
	else
	{
		Logger::LogInfo("Added scene",s->name);

		m_allScenes[s->name] = std::move(s);
	}
}

void SceneManager::ReloadCurrent()
{
	//Check if scene is already loaded
	if (m_currentScene != nullptr)
	{
		if (m_currentScene != nullptr)
		{
			m_currentScene->QuitScene();

			m_currentScene->m_isReady = false;
		}

		EventDispatcher::Instance().DispatchEvent(new SceneChangedEvent(m_currentScene));

		m_currentScene->Initialize();
		m_currentScene->m_isReady = true;
		m_currentScene->Start();
		Input::SetIsEnabled(1);
		Timer::ResetTickCount();

	}
}

void SceneManager::LoadNewScene(std::string sceneName)
{
	Input::SetIsEnabled(0);

	//Check if scene is already loaded
	if(m_currentScene != nullptr)
	{
		if (m_currentScene->name == sceneName)
			return;
	}

	auto it = m_allScenes.find(sceneName);

	if (it == m_allScenes.end())
	{
		Logger::LogError("The scene",sceneName,"does not exists.");
		return;		
	}

	if (m_currentScene != nullptr)
	{
		m_currentScene->QuitScene();
		m_currentScene->UnloadAssets();
		m_currentScene->m_isReady = false;
	}
	m_currentScene = it->second.get();
	EventDispatcher::Instance().DispatchEvent(new SceneChangedEvent(m_currentScene));

	m_currentScene->LoadAssets();
	m_currentScene->Initialize();
	m_currentScene->Start();
	Input::SetIsEnabled(1);
	Timer::ResetTickCount();
	m_currentScene->m_isReady = true;
	//Input::Update();


}

void SceneManager::DestroyAllScenes()
{
	auto it = m_allScenes.begin();

	for (; it != m_allScenes.end(); it++)
	{
		it->second->QuitScene();
		it->second->UnloadAssets(); //Not sure about this one
	}

	m_allScenes.clear();
}
SceneManager::~SceneManager()
{


}