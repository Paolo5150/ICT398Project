#pragma once
#include "pch.h"
#include "Game.h"
#include "Core\Window.h"
#include "Core\Logger.h"
#include "Scene\SceneManager.h"
#include "Scenes/SimpleScene.h"
#include "Scenes\PhysicsDemoScene.h"
#include "Scenes/OtherScene.h"
#include "Scenes/ExitScene.h"






std::unique_ptr<Application> CreateApplication()
{
	return std::unique_ptr<Application>(new Game("398 Project"));
}

Game::Game(std::string appName)
{
	this->name = appName;	
}

Game::~Game()
{
	//Logger::LogError("Game instance destroyed");
}


void Game::AppInitialize()
{
	//Create all scenes here, might need to use LUA...?
	/*SceneManager::Instance().AddScene(new MainScene());
	SceneManager::Instance().AddScene(new ExitScene());
	SceneManager::Instance().AddScene(new MainMenuScene());*/

	auto simple = std::unique_ptr<Scene>(new SimpleScene());
	SceneManager::Instance().AddScene(simple);

	auto physics = std::unique_ptr<Scene>(new PhysicsDemoScene());
	SceneManager::Instance().AddScene(physics);

	auto other = std::unique_ptr<Scene>(new OtherScene());
	SceneManager::Instance().AddScene(other);

	auto exit = std::unique_ptr<Scene>(new ExitScene());
	SceneManager::Instance().AddScene(exit);

	//Load first scene
	SceneManager::Instance().LoadNewScene("PhysicsDemo"); //Scene initialize is called here*/


	
}

void Game::AppLogicUpdate()
{
	//Logger::LogInfo("Game logic update");
	Application::AppLogicUpdate();
}
void Game::AppShutdown()
{
	
	SceneManager::Instance().DestroyAllScenes();
	//Logger::LogInfo("Game shutdown");
}