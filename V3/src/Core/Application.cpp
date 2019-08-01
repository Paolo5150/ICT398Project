#include "pch.h"
#include "Application.h"
#include "Logger.h"
#include "..\Events\EventDispatcher.h"
#include "..\Events\ApplicationEvents.h"
#include "..\Scene\SceneManager.h"


Application::Application()
{

}
void Application::AppEngineUpdate()
{
	//Logger::LogInfo("Application engine update");
	SceneManager::Instance().GetCurrentScene().EngineUpdate();
}

void Application::AppLogicUpdate()
{
	SceneManager::Instance().GetCurrentScene().LogicUpdate();
}
void Application::AppLateUpdate()
{
	//Logger::LogInfo("Application late update");
	SceneManager::Instance().GetCurrentScene().LateUpdate();


}