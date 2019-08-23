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


	ContentManager::Instance().LoadCubeMap("Assets\\SkyBoxes\\SunSet");


	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Iron\\iron_albedo.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Iron\\iron_roughness.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Iron\\iron_metallic.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Iron\\iron_normal.jpg", 0);	
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_ao.jpg", 0);
}

void SimpleScene::QuitScene() {

	Scene::QuitScene();

}
void SimpleScene::Initialize() {

	Timer::SetDisplayFPS(1);
	LightManager::Instance().SetAmbientLight(0.00, 0.00, 0.00);

	skybox = std::unique_ptr<Skybox>(new Skybox(ContentManager::Instance().GetAsset<CubeMap>("SunSet")));

	std::vector<GameObject*> objs = FileUtils::ReadSceneFile("Assets\\SceneFiles\\MainScene.txt");	

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

	for (int i = 0; i < objs.size(); i++)
		AddGameObject(objs[i]);


}

void SimpleScene::Start()
{
	Scene::Start();
	Input::SetCursorMode("disabled");
	PhysicsWorld::Instance().InitializeQuadtree(0, 0, 5000, 5000);

}

void SimpleScene::LogicUpdate()
{
	//glm::vec3 inertia = SceneManager::Instance().GetCurrentScene().GetGameobjectsByName("Bench")[0]->GetComponent<BoxCollider>("BoxCollider")->GetMomentOfIntertia();

	if (Input::GetKeyDown(GLFW_KEY_ESCAPE))
		EventDispatcher::Instance().DispatchEvent(new QuitRequestEvent());

	if (Input::GetKeyDown(GLFW_KEY_O))
		SceneManager::Instance().LoadNewScene("OtherScene");
	
	//DiagRenderer::Instance().RenderSphere(inertia, 0.5,glm::vec3(1,0,0));

	Scene::LogicUpdate(); //Must be last statement!
}



