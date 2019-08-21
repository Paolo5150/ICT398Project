#include "pch.h"
#include "Components\MeshRenderer.h"
#include "SimpleScene.h"
#include "Components/BoxCollider.h"
#include "Core/Core.h"
#include "Prefabs/Bench.h"
#include "Prefabs/Chair.h"
#include "Prefabs/Table.h"
#include "Prefabs/Terrain.h"
#include "Prefabs/LandfillBin.h"
#include "Prefabs/RecycleBin.h"

#include "Diag/DiagRenderer.h"

SimpleScene::SimpleScene() : Scene("SimpleScene")
{
}

void SimpleScene::LoadAssets() {

	ContentManager::Instance().LoadModel("Assets\\Models\\Bench\\bench.obj", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\Chair\\chair.obj", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\Table\\table.fbx", false, false);

	ContentManager::Instance().LoadModel("Assets\\Models\\LandfillBin\\landfillbin.obj", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\RecycleBin\\recyclebin.obj", true, false);

	ContentManager::Instance().LoadCubeMap("Assets\\SkyBoxes\\SunSet");
	ContentManager::Instance().LoadTexture("Assets\\Textures\\grass.jpg");

	//Load textures separetely
	ContentManager::Instance().LoadTexture("Assets\\Models\\LandfillBin\\textures\\LB_Frame.png", 0);
	ContentManager::Instance().LoadTexture("Assets\\Models\\LandfillBin\\textures\\LB_Sides.png", 0);

	ContentManager::Instance().LoadTexture("Assets\\Models\\RecycleBin\\textures\\RB_Frame.png", 0);
	ContentManager::Instance().LoadTexture("Assets\\Models\\RecycleBin\\textures\\RB_Sides.png", 0);



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

	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Metal\\metal_roughness.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Metal\\metal_normal.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Metal\\metal_height.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Metal\\metal_ao.jpg", 0);

	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Limestone\\limestone_albedo.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Limestone\\limestone_roughness.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Limestone\\limestone_normal.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Limestone\\limestone_metallic.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Limestone\\limestone_height.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Limestone\\limestone_ao.jpg", 0);

	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Tiled\\tiled_albedo.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Tiled\\tiled_roughness.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Tiled\\tiled_normal.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Tiled\\tiled_height.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Tiled\\tiled_ao.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Tiled\\tiled_metallic.jpg", 0);

	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Moss\\moss_albedo.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Moss\\moss_roughness.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Moss\\moss_normal.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Moss\\moss_height.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Moss\\moss_ao.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Moss\\moss_metallic.jpg", 0);

}

void SimpleScene::QuitScene() {

	Scene::QuitScene();

}
void SimpleScene::Initialize() {

	Timer::SetDisplayFPS(1);
	LightManager::Instance().SetAmbientLight(0.00, 0.00, 0.00);

	skybox = std::unique_ptr<Skybox>(new Skybox(ContentManager::Instance().GetAsset<CubeMap>("SunSet")));

	LandfillBin* lb = new LandfillBin();
	lb->transform.SetPosition(0, 20, 0);

	RecycleBin* rb = new RecycleBin();
	rb->transform.SetPosition(30, 20, 0);

	Bench* bench = new Bench();
	bench->transform.SetPosition(-30, -10, 0);

	Chair* chair = new Chair();
	chair->transform.SetPosition(30, 0, 0);

	Table* table = new Table();
	table->transform.SetPosition(0, 0, 0);

	Terrain* terrain = new Terrain(50);

	MainCamera* cam = new MainCamera();
	cam->transform.SetPosition(0, 10, 50);
	cam->transform.SetRotation(0, 180, 0);
	
	DirectionalLight* dirLight = new DirectionalLight(false);
	dirLight->transform.SetRotation(30,114,-4);
	dirLight->SetIntensity(1.5);

	PointLight* pointLight = new PointLight();

	pointLight->SetIntensity(2);
	pointLight->transform.SetPosition(20, 3, 20);
	
	AddGameObject(cam);
	AddGameObject(dirLight);
	AddGameObject(pointLight);
	AddGameObject(bench);
	AddGameObject(chair);
	AddGameObject(table);
	AddGameObject(terrain);
	AddGameObject(lb);
	AddGameObject(rb);

}

void SimpleScene::Start()
{
	Scene::Start();
	Input::SetCursorMode("disabled");
	PhysicsWorld::Instance().InitializeQuadtree(0, 0, 5000, 5000);

	glm::vec3 pos = SceneManager::Instance().GetCurrentScene().GetGameobjectsByName("Bench")[0]->GetComponent<BoxCollider>("BoxCollider")->GetMaxPoint();
		
	SceneManager::Instance().GetCurrentScene().GetGameobjectsByName("Bench")[0]->GetComponent<BoxCollider>("BoxCollider")->GetMassMomentIntertia();
}

void SimpleScene::LogicUpdate()
{
	//SceneManager::Instance().GetCurrentScene().GetGameobjectsByName("Bench")[0]->transform.Translate(0.05, 0, 0);

	if (Input::GetKeyDown(GLFW_KEY_ESCAPE))
		EventDispatcher::Instance().DispatchEvent(new QuitRequestEvent());

	if (Input::GetKeyDown(GLFW_KEY_O))
		SceneManager::Instance().LoadNewScene("OtherScene");
	
	DiagRenderer::Instance().RenderSphere(glm::vec3(50, 120, 0), 20,glm::vec3(1,0,0));

	Scene::LogicUpdate(); //Must be last statement!
}



