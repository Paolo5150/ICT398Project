#include "pch.h"
#include "Components\MeshRenderer.h"
#include "SimpleScene.h"
#include "Components/BoxCollider.h"
#include "Core/Core.h"
#include "Prefabs/Bench.h"
#include "Prefabs/Chair.h"
#include "Prefabs/Table.h"
#include "Prefabs/Terrain.h"


SimpleScene::SimpleScene() : Scene("SimpleScene")
{
}

void SimpleScene::LoadAssets() {

	ContentManager::Instance().LoadModel("Assets\\Models\\Bench\\bench.obj", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\Chair\\chair.obj", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\Table\\table.fbx", false, false);


	ContentManager::Instance().LoadCubeMap("Assets\\SkyBoxes\\SunSet");
	ContentManager::Instance().LoadTexture("Assets\\Textures\\grass.jpg");

	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Iron\\iron_albedo.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Iron\\iron_roughness.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Iron\\iron_metallic.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Iron\\iron_normal.jpg", 0);	
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_ao.jpg", 0);

	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_albedo.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_roughness.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_metallic.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_normal.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_ao.jpg", 0);

	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Wood\\wood_albedo.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Wood\\wood_roughness.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Wood\\wood_metallic.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Wood\\wood_normal.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Wood\\wood_ao.jpg", 0);

	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Grass\\grass_albedo.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Grass\\grass_roughness.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Grass\\grass_normal.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Grass\\grass_ao.jpg", 0);
}

void SimpleScene::QuitScene() {

	Scene::QuitScene();

}
void SimpleScene::Initialize() {

	Timer::SetDisplayFPS(1);
	LightManager::Instance().SetAmbientLight(0.00, 0.00, 0.00);

	skybox = std::unique_ptr<Skybox>(new Skybox(ContentManager::Instance().GetAsset<CubeMap>("SunSet")));	

	Bench* bench = new Bench();
	bench->transform.SetPosition(-30, 0, 0);

	Chair* chair = new Chair();
	chair->transform.SetPosition(30, 0, 0);

	Table* table = new Table();
	table->transform.SetPosition(0, 0, 0);

	Terrain* terrain = new Terrain(50);

	MainCamera* cam = new MainCamera();
	cam->transform.SetPosition(0, 10, 50);
	cam->transform.SetRotation(0, 180, 0);
	
	DirectionalLight* dirLight = new DirectionalLight(false);
	dirLight->transform.SetRotation(45, 180, 0);
	dirLight->SetIntensity(0.2);

	PointLight* pointLight = new PointLight();

	pointLight->SetIntensity(10);
	pointLight->transform.SetPosition(0, 10, 5);
	
	AddGameObject(cam);
	AddGameObject(dirLight);
	AddGameObject(pointLight);
	AddGameObject(bench);
	AddGameObject(chair);
	AddGameObject(table);
	AddGameObject(terrain);


}

void SimpleScene::Start()
{
	Scene::Start();
	Input::SetCursorMode("disabled");
	PhysicsWorld::Instance().InitializeQuadtree(0, 0, 5000, 5000);

}

void SimpleScene::LogicUpdate()
{
	//SceneManager::Instance().GetCurrentScene().GetGameobjectsByName("Chair")[0]->transform.Translate(0.05, 0, 0);

	if (Input::GetKeyDown(GLFW_KEY_ESCAPE))
		EventDispatcher::Instance().DispatchEvent(new QuitRequestEvent());

	if (Input::GetKeyDown(GLFW_KEY_O))
		SceneManager::Instance().LoadNewScene("OtherScene");
	
	Scene::LogicUpdate(); //Must be last statement!
}



