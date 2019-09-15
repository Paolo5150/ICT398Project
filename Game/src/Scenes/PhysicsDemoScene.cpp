#include "pch.h"
#include "PhysicsDemoScene.h"
#include "Prefabs/Box.h"
#include "Prefabs/Box2.h"
#include "GUI/GUIManager.h"
#include "GUI/Elements/GUIImage.h"
#include "GUI/Elements/GUIText.h"

PhysicsDemoScene::PhysicsDemoScene() : Scene("PhysicsDemo")
{
}


PhysicsDemoScene::~PhysicsDemoScene()
{
}

void PhysicsDemoScene::LoadAssets() {

	// Load splash screen
	GUIImage* image = new GUIImage("SplashImage", ContentManager::Instance().GetAsset<Texture2D>("logo"), 100, 100, 0, 0, 1, 1, 1, 1);
	GUIText* text = new GUIText("LoadingText", "Loading", 1, 95, glm::vec3(1), 2.5, 1);

	GUIManager::Instance().GetCanvasByName("MainCanvas")->AddGUIObject(image);
	GUIManager::Instance().GetCanvasByName("MainCanvas")->AddGUIObject(text);

	GUIManager::Instance().SetColorBuffer(0.8, 0.8, 0.8);
	GUIManager::Instance().Render(true, true);


	text->message = "Loading uncomfrotable feelings...";
	GUIManager::Instance().Render(true);

	ContentManager::Instance().LoadModel("Assets\\Models\\Bench\\bench.obj", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\Table\\table.fbx", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\Chair\\chair.obj", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\LandfillBin\\landfillbin.obj", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\RecycleBin\\recyclebin.obj", false, false);

	ContentManager::Instance().LoadTexture("Assets\\Models\\LandfillBin\\textures\\LB_Frame.png", 0);
	ContentManager::Instance().LoadTexture("Assets\\Models\\LandfillBin\\textures\\LB_Sides.png", 0);

	ContentManager::Instance().LoadTexture("Assets\\Models\\RecycleBin\\textures\\RB_Frame.png", 0);
	ContentManager::Instance().LoadTexture("Assets\\Models\\RecycleBin\\textures\\RB_Sides.png", 0);





	ContentManager::Instance().LoadCubeMap("Assets\\SkyBoxes\\SunSet");


	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Iron\\iron_albedo.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Iron\\iron_roughness.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Iron\\iron_metallic.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Iron\\iron_normal.jpg", 0);

	text->message = "Instantiating sense of despair...";
	GUIManager::Instance().Render(true, true);

	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_albedo.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_roughness.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_metallic.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_normal.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_ao.jpg", 0);

	ContentManager::Instance().LoadTexture("Assets\\Textures\\water_normal.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\Textures\\dudv.png", 0);

	text->message = "Finalizing feeling of hopelessness...";
	GUIManager::Instance().Render(true, true);

	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Wood\\wood_albedo.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Wood\\wood_roughness.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Wood\\wood_metallic.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Wood\\wood_normal.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Wood\\wood_ao.jpg", 0);

	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Metal\\metal_roughness.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Metal\\metal_normal.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Metal\\metal_height.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Metal\\metal_ao.jpg", 0);

	image->isActive = 0;
	text->isActive = 0;
	text->message = "Loading next scene.."; //Just prepare the message for going to the exit scene
}

void PhysicsDemoScene::QuitScene() {

	Scene::QuitScene();

}
void PhysicsDemoScene::Initialize() {


	LightManager::Instance().SetAmbientLight(0.00, 0.00, 0.00);

	skybox = std::unique_ptr<Skybox>(new Skybox(ContentManager::Instance().GetAsset<CubeMap>("SunSet")));

	Box* box = new Box();
	box->transform.SetPosition(5, 7, 0);
	box->transform.SetRotation(0, 0, 0);
	Rigidbody* rb = box->GetComponent<Rigidbody>("Rigidbody");
	if (rb != nullptr)
	{
		rb->SetVelocity(-5, 0, 0);
		rb->SetAngularVelocity(20, -20, 0);
	}

	Box2* box2 = new Box2();
	box2->transform.SetPosition(-6, 10, 0);
	box2->transform.SetRotation(0, 0, 0);

	MainCamera* cam = new MainCamera();
	cam->transform.SetPosition(-3, 10, 20);
	cam->transform.SetRotation(0, 180, 0);

	DirectionalLight* dirLight = new DirectionalLight(false);
	dirLight->transform.SetRotation(40, 114, -4);
	dirLight->SetDiffuseColor(1.0, 0.9, 0.9);
	dirLight->SetSpecularColor(1.0, 0.8, 0.4);
	dirLight->SetIntensity(1.5);

	DirectionalLight* dirLight2 = new DirectionalLight(false);
	dirLight2->transform.SetRotation(90, 0, 0);
	dirLight2->SetSpecularColor(1.0, 0.8, 0.4);

	dirLight2->SetIntensity(0.2);

	PointLight* pointLight = new PointLight();

	pointLight->SetIntensity(10);
	pointLight->transform.SetPosition(0, 0, 10);

	AddGameObject(cam);
	AddGameObject(pointLight);
	AddGameObject(box);
	AddGameObject(box2);
}

void PhysicsDemoScene::Start()
{
	Scene::Start();
	Input::SetCursorMode("disabled");
	PhysicsWorld::Instance().InitializeQuadtree(0, 0, 100, 100);
	PhysicsWorld::Instance().FillQuadtree(1); // Fill static quadtree

}

void PhysicsDemoScene::LogicUpdate()
{
	if (Input::GetKeyDown(GLFW_KEY_ESCAPE))
	{
		GUIManager::Instance().GetCanvasByName("MainCanvas")->GetGUIObjectByName("LoadingText")->isActive = 1;
		GUIManager::Instance().Render(1);
		SceneManager::Instance().LoadNewScene("ExitScene");
		return;
	}

	Scene::LogicUpdate(); //Must be last statement!

	((PointLight*)GetGameobjectsByName("PointLight")[0])->RenderDiag();

}