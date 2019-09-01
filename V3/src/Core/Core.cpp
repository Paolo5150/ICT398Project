#include "pch.h"

#include "Core.h"
#include "Input.h"
#include "..\Events\EventDispatcher.h"
#include "..\Events\WindowEvents.h"
#include "..\Events\TimerEvents.h"
#include "..\Events\ApplicationEvents.h"
#include "..\Rendering\API_Opengl.h"
#include "..\Rendering\RenderingEngine.h"
#include "..\Utils\ContentManager.h"
#include "..\Lighting\LightingManager.h"
#include "..\GUI\GUIManager.h"
#include "..\Physics\PhysicsWorld.h"
#include "..\Diag\DiagRenderer.h"

void Core::Initialize()
{
	Window::Initialize(); //Set context

	m_graphicsAPI = std::make_unique<API_Opengl>();
	m_graphicsAPI->Initialize();

	Logger::LogInfo("OpenGL version supported by this platform", glGetString(GL_VERSION));
	//Events subscirption
	std::string s = EventDispatcher::Instance().SubscribeCallback<LogicUpdateEvent>(std::bind(&Core::LogicUpdate, this, std::placeholders::_1));
	EventDispatcher::Instance().SubscribeCallback<LateUpdateEvent>(std::bind(&Core::LateUpdate, this, std::placeholders::_1));
	EventDispatcher::Instance().SubscribeCallback<RenderEvent>(std::bind(&Core::Render, this, std::placeholders::_1));
	EventDispatcher::Instance().SubscribeCallback<EngineUpdateEvent>(std::bind(&Core::EngineUpdate, this, std::placeholders::_1));

	EventDispatcher::Instance().SubscribeCallback<WindowResizeEvent>([this](Event* e){
		WindowResizeEvent* wre = dynamic_cast<WindowResizeEvent*>(e);
		GetGraphicsAPI().SetViewPort(wre->width, wre->height);
		
		return 0;
	});

	EventDispatcher::Instance().SubscribeCallback<QuitRequestEvent>([this](Event* e){
		m_isRunning = false;
		return 0;
	});

	//Close window, exit loop
	EventDispatcher::Instance().SubscribeCallback<WindowCloseEvent>([this](Event* event) -> bool{
		m_isRunning = 0;
		return 0; });


	m_runningApplication = CreateApplication();
	//WINDOW
	// Set up windows after flew initialization (and after the context has been set).
	Window::Instance().SetWindowSize(1200,800);
	
	LoadBasicAssets();

	//Get cpplication
	
	Window::Instance().SetWindowTitle(m_runningApplication->name.c_str()); //Window title -> game title

	//Managers initialization
	// Initialize here as some managers need assets (eg. RenderingEngine need shaders)
	Input::Init(false, true);
	RenderingEngine::Instance().Initialize();
	Timer::Initialize();
	LightManager::Instance().Initialize();
	GUIManager::Instance().Initialize();

	//Start update loop
	m_isRunning = true;
	Input::SetCursorMode("normal");
}
void Core::Run()
{
	m_runningApplication->AppInitialize();
	while (m_isRunning)
	{
		// Just update the timer
		// The timer will send out events for update, render and so on
		Window::Instance().UpdateEvents();		
		Timer::Update();		
	}
}
void Core::Shutdown()
{
	m_runningApplication->AppShutdown();
	ContentManager::Instance().UnloadPreserved<Shader>();
	ContentManager::Instance().UnloadPreserved<Texture2D>();
	ContentManager::Instance().UnloadPreserved<Model>();
	ContentManager::Instance().UnloadPreserved<Mesh>();

	GUIManager::Instance().Shutdown();

	Window::Instance().Destroy();
	glfwTerminate();

}

Core& Core::Instance()
{
	static Core instance;
	return instance;
}

Core::~Core()
{
	
}

Core::Core()
{}

bool Core::IsRunning()
{
	return m_isRunning;
}

bool Core::LogicUpdate(Event* e)
{
	//Logger::LogInfo("Core logic update");

	m_runningApplication->AppLogicUpdate();
	
	return 0;
}


bool Core::EngineUpdate(Event* e)
{
	//Logger::LogInfo("Core engine update");
	m_runningApplication->AppEngineUpdate();

	return 0;
}

bool Core::LateUpdate(Event* e)
{
	//Logger::LogInfo("Core late update");

	m_runningApplication->AppLateUpdate();
	RenderingEngine::Instance().ClearRendererList();
	Input::Update();
	return 0;
}


bool Core::Render(Event* e)
{
	//Logger::LogInfo("Core rendering");
	
	LightManager::Instance().Update();
	RenderingEngine::Instance().RenderBufferToTexture();
	GUIManager::Instance().Render();

	Window::Instance().Refresh();
	return 0;
}

void Core::LoadBasicAssets()
{

	ContentManager::Instance().LoadShader("ColorOnlyStatic", "Assets\\Shaders\\ColorOnlyStatic.v", "Assets\\Shaders\\ColorOnlyStatic.f", true);
	ContentManager::Instance().LoadShader("ColorOnlyAnimated", "Assets\\Shaders\\ColorOnlyAnimated.v", "Assets\\Shaders\\ColorOnlyStatic.f", true);
	ContentManager::Instance().LoadShader("DefaultAnimated", "Assets\\Shaders\\DefaultAnimated.v", "Assets\\Shaders\\DefaultAnimated.f", true);
	ContentManager::Instance().LoadShader("DefaultStatic", "Assets\\Shaders\\DefaultStatic.v", "Assets\\Shaders\\DefaultStatic.f", true);
	ContentManager::Instance().LoadShader("DefaultStaticNormalMap", "Assets\\Shaders\\DefaultStaticNormalMap.v", "Assets\\Shaders\\DefaultStaticNormalMap.f", true);
	ContentManager::Instance().LoadShader("DefaultStaticNoLight", "Assets\\Shaders\\DefaultStaticNoLight.v", "Assets\\Shaders\\DefaultStaticNoLight.f", true);
	ContentManager::Instance().LoadShader("DefaultAnimatedNoLight", "Assets\\Shaders\\DefaultAnimatedNoLight.v", "Assets\\Shaders\\DefaultStaticNoLight.f", true);
	ContentManager::Instance().LoadShader("PostProcess", "Assets\\Shaders\\PostProcess.v", "Assets\\Shaders\\PostProcess.f", true);
	ContentManager::Instance().LoadShader("GodRays", "Assets\\Shaders\\PostProcess.v", "Assets\\Shaders\\GodRays.f", true);
	ContentManager::Instance().LoadShader("Terrain", "Assets\\Shaders\\Terrain.v", "Assets\\Shaders\\Terrain.f", true);
	ContentManager::Instance().LoadShader("Water", "Assets\\Shaders\\Water.v", "Assets\\Shaders\\Water.f", true);
	ContentManager::Instance().LoadShader("Skybox", "Assets\\Shaders\\Skybox.v", "Assets\\Shaders\\Skybox.f", true);
	ContentManager::Instance().LoadShader("SkyboxHDR", "Assets\\Shaders\\SkyboxHDR.v", "Assets\\Shaders\\SkyboxHDR.f", true);

	ContentManager::Instance().LoadShader("PBR", "Assets\\Shaders\\PBR.v", "Assets\\Shaders\\PBR.f", true);
	ContentManager::Instance().LoadShader("PBRHeight", "Assets\\Shaders\\PBR.v", "Assets\\Shaders\\PBRHeight.f", true);

	ContentManager::Instance().LoadShader("PostProcess_basic", "Assets\\Shaders\\PostProcess_basic.v", "Assets\\Shaders\\PostProcess_basic.f", true);
	ContentManager::Instance().LoadShader("PostProcess_hdr", "Assets\\Shaders\\PostProcess_hdr.v", "Assets\\Shaders\\PostProcess_hdr.f", true);
	ContentManager::Instance().LoadShader("PostProcess_upsidedown", "Assets\\Shaders\\PostProcess_upsidedown.v", "Assets\\Shaders\\PostProcess_upsidedown.f", true);


	ContentManager::Instance().LoadShader("TerrainNoLight", "Assets\\Shaders\\TerrainNoLight.v", "Assets\\Shaders\\TerrainNoLight.f", true);
	ContentManager::Instance().LoadTexture("Assets\\Textures\\errorTexture.png",true);
	ContentManager::Instance().LoadModel("Assets\\Models\\Quad\\quad.obj",false,true);
	ContentManager::Instance().LoadModel("Assets\\Models\\Cube\\cube.obj", false, true);

	ContentManager::Instance().LoadModel("Assets\\Models\\Sphere\\sphere.fbx", false, true);


}