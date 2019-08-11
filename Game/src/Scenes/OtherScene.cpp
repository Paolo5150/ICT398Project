#include "pch.h"
#include "Components\MeshRenderer.h"
#include "OtherScene.h"
#include "Components/BoxCollider.h"
#include "Core/Core.h"



OtherScene::OtherScene() : Scene("OtherScene")
{
}

void OtherScene::LoadAssets() {

	ContentManager::Instance().LoadModel("Assets\\Models\\Nanosuit\\nanosuit.obj", false, false);
	ContentManager::Instance().LoadCubeMap("Assets\\SkyBoxes\\SunSet");


	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_albedo.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_roughness.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_metallic.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_normal.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_ao.jpg", 0);


}

void OtherScene::QuitScene() {

	Scene::QuitScene();

}
void OtherScene::Initialize() {

	Timer::SetDisplayFPS(1);
	//	Core::Instance().GetGraphicsAPI().SetClearColor(1, 0, 0);
	LightManager::Instance().SetAmbientLight(0.00, 0.00, 0.00);

	skybox = std::unique_ptr<Skybox>(new Skybox(ContentManager::Instance().GetAsset<CubeMap>("SunSet")));

	GameObject* g = new GameObject("Test");
	ContentManager::Instance().GetAsset<Model>("Nanosuit")->PopulateGameObject(g);

	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("PBR"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("bamboo_normal"), "normalMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("bamboo_albedo"), "albedoMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("bamboo_roughness"), "roughnessMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("bamboo_metallic"), "metallicMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("bamboo_ao"), "aoMap");
	m.LoadCubemap(ContentManager::Instance().GetAsset<CubeMap>("SunSet"), "cubemap0");

	g->ApplyMaterial(m);




	MainCamera* cam = new MainCamera();
	cam->transform.SetPosition(0, 10, 50);
	cam->transform.SetRotation(0, 180, 0);


	DirectionalLight* dirLight = new DirectionalLight(false);
	dirLight->transform.SetRotation(45, 180, 0);
	dirLight->SetIntensity(0.2);

	PointLight* pointLight = new PointLight();

	pointLight->SetIntensity(10);
	pointLight->transform.SetPosition(0, 0, 5);
	pointLight->SetDiffuseColor(1, 0, 0);

	AddGameObject(cam);
	AddGameObject(dirLight);
	AddGameObject(pointLight);
	AddGameObject(g);

}

void OtherScene::Start()
{
	Scene::Start();
	Input::SetCursorMode("disabled");

}

void OtherScene::LogicUpdate()
{
	SceneManager::Instance().GetCurrentScene().GetGameobjectsByName("PointLight")[0]->transform.Translate(0, 0.01, 0.0);


	if (Input::GetKeyDown(GLFW_KEY_ESCAPE))
		EventDispatcher::Instance().DispatchEvent(new QuitRequestEvent());


	if (Input::GetKeyDown(GLFW_KEY_T))
		Input::SetCursorMode("normal");

	if (Input::GetKeyDown(GLFW_KEY_Y))
		Input::SetCursorMode("disabled");

	if (Input::GetKeyDown(GLFW_KEY_R))
		SceneManager::Instance().ReloadCurrent();


	if (Input::GetKeyDown(GLFW_KEY_P))
		SceneManager::Instance().LoadNewScene("SimpleScene");

	Scene::LogicUpdate(); //Must be last statement!

}




