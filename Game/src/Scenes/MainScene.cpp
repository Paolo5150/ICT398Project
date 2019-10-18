#include "pch.h"
#include "Components\MeshRenderer.h"
#include "MainScene.h"
#include "Components/BoxCollider.h"
#include "Core/Core.h"
#include "Prefabs/Bench.h"
#include "Prefabs/Chair.h"
#include "Prefabs/Table.h"
#include "Prefabs/Terrain.h"
#include "Prefabs/LandfillBin.h"
#include "Prefabs/RecycleBin.h"
#include "Prefabs/Billquad.h"

#include "Prefabs/BushCourt.h"
#include "Prefabs/Lantern.h"
#include "Physics/PathFindingManager.h"

#include "Diag/DiagRenderer.h"
#include "GUI/GUIManager.h"
#include "GUI/Elements/GUIImage.h"
#include "GUI/Elements/GUIText.h"
#include "GUI/Elements/GUIBar.h"

#include "Affordances/AffordanceManager.h"

namespace
{
	GUIBar* loadingBar;
	GameObject* player;


}

MainScene::MainScene() : Scene("MainScene")
{
}

void MainScene::LoadAssets() {

	// Load splash screen
	GUIImage* image = new GUIImage("SplashImage", ContentManager::Instance().GetAsset<Texture2D>("logo"), 100, 100, 0, 0, 1, 1, 1,1);
	GUIText* text = new GUIText("LoadingText", "Loading", 1, 95, glm::vec3(1), 2.5,1);
	loadingBar = new GUIBar("Bar", 50,3, 25, 90, 1);
	loadingBar->backgorundColor = glm::vec4(0, 0, 0, 0.8);
	loadingBar->foregroundColor = glm::vec4(1, 1, 1, 0.8);
	loadingBar->textColor = glm::vec4(1, 0, 0, 0.8);

	GUIManager::Instance().GetCanvasByName("MainCanvas")->AddGUIObject(image);
	GUIManager::Instance().GetCanvasByName("MainCanvas")->AddGUIObject(text);
	GUIManager::Instance().GetCanvasByName("MainCanvas")->AddGUIObject(loadingBar);

	GUIManager::Instance().SetColorBuffer(0.8, 0.8, 0.8);
	GUIManager::Instance().Render(true, true);

	text->message = "Loading uncomfortable feelings...";
	loadingBar->percentage = 0.2;
	GUIManager::Instance().Render(true);

	ContentManager::Instance().LoadModel("Assets\\Models\\Bench\\bench.obj", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\Table\\table.fbx", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\Chair\\chair.obj", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\LandfillBin\\landfillbin.obj", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\RecycleBin\\recyclebin.obj", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\BushCourt\\bushcourt.obj", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\Lantern\\lantern.obj", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\Crate\\crate.obj",false, false);

	ContentManager::Instance().LoadTexture("Assets\\Textures\\Emotions\\Rest.png", false);
	ContentManager::Instance().LoadTexture("Assets\\Textures\\Emotions\\happy.png", false);
	ContentManager::Instance().LoadTexture("Assets\\Textures\\Emotions\\Anger.png", false);



	ContentManager::Instance().LoadModel("Assets\\Models\\Fred\\Fred.fbx", false, false);
	ContentManager::Instance().LoadTexture("Assets\\Models\\Fred\\textures\\Fred_Base_Color.png", false);

	ContentManager::Instance().LoadModel("Assets\\Models\\Joey\\Joey.fbx", false, false);
	ContentManager::Instance().LoadTexture("Assets\\Models\\Joey\\textures\\Joey_Base_Color.png", false);

	ContentManager::Instance().LoadModel("Assets\\Models\\Riley\\Riley.fbx", false, false);
	ContentManager::Instance().LoadTexture("Assets\\Models\\Riley\\textures\\Riley_Base_Color.png", false);

	ContentManager::Instance().LoadTexture("Assets\\Models\\Lantern\\textures\\Lantern.png", 0);

	ContentManager::Instance().LoadTexture("Assets\\Models\\LandfillBin\\textures\\LB_Frame.png", 0);
	ContentManager::Instance().LoadTexture("Assets\\Models\\LandfillBin\\textures\\LB_Sides.png", 0);

	ContentManager::Instance().LoadTexture("Assets\\Models\\RecycleBin\\textures\\RB_Frame.png", 0);
	ContentManager::Instance().LoadTexture("Assets\\Models\\RecycleBin\\textures\\RB_Sides.png", 0);

	ContentManager::Instance().LoadTexture("Assets\\Textures\\BushCourt\\BushCourt.png", 0);
	ContentManager::Instance().LoadCubeMap("Assets\\SkyBoxes\\SunSet");

	// Preserve these as they are used in the exit scene
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Iron\\iron_albedo.jpg", 1);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Iron\\iron_roughness.jpg", 1);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Iron\\iron_metallic.jpg", 1);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Iron\\iron_normal.jpg", 1);

	text->message = "Instantiating sense of despair...";
	loadingBar->percentage = 0.5;
	GUIManager::Instance().Render(true, true);

	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_albedo.jpg",0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_roughness.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_metallic.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_normal.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Bamboo\\bamboo_ao.jpg", 0);

	ContentManager::Instance().LoadTexture("Assets\\Textures\\water_normal.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\Textures\\dudv.png", 0);

	text->message = "Normalizing regret and depression...";
	loadingBar->percentage = 0.7;
	GUIManager::Instance().Render(true,true);

	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Wood\\wood_albedo.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Wood\\wood_roughness.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Wood\\wood_metallic.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Wood\\wood_normal.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Wood\\wood_ao.jpg", 0);

	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Metal\\metal_roughness.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Metal\\metal_normal.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Metal\\metal_height.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\PBRMaterials\\Metal\\metal_ao.jpg", 0);

	text->message = "Interpolating sadness";
	loadingBar->percentage = 0.9;
	GUIManager::Instance().Render(true, true);
	// Load this stuff as preserved so they can be used in the exit scene (so there's not much loading when transitioning)
	ContentManager::Instance().LoadModel("Assets\\Models\\Paolo\\paolo.fbx", false, true);
	ContentManager::Instance().LoadModel("Assets\\Models\\Drew\\drew.fbx", false, true);
	ContentManager::Instance().LoadModel("Assets\\Models\\Dylan\\dylan.fbx", false, true);

	ContentManager::Instance().LoadTexture("Assets\\Models\\Paolo\\textures\\paolo.jpg",true);
	ContentManager::Instance().LoadTexture("Assets\\Models\\Drew\\textures\\drew.jpg", true);
	ContentManager::Instance().LoadTexture("Assets\\Models\\Dylan\\textures\\Dylan.png", true);

	ContentManager::Instance().LoadModel("Assets\\Models\\PaoloText\\PaoloText.obj", false, true);
	ContentManager::Instance().LoadModel("Assets\\Models\\DrewText\\DrewText.obj", false, true);
	ContentManager::Instance().LoadModel("Assets\\Models\\DylanText\\DylanText.obj", false, true);

	image->isActive = 0;
	text->isActive = 0;
	text->message = "Loading next scene.."; //Just prepare the message for going to the exit scene
	//Disable loading bar
	loadingBar->isActive = 0;
}

void MainScene::QuitScene() {

	Scene::QuitScene();

}
void MainScene::Initialize() {


	LightManager::Instance().SetAmbientLight(0.4, 0.4, 0.4);

	skybox = std::unique_ptr<Skybox>(new Skybox(ContentManager::Instance().GetAsset<CubeMap>("SunSet")));

	cam = new MainCamera();
	cam->transform.SetPosition(0, 10, 40);
	cam->transform.SetRotation(0, 180, 0);

	DirectionalLight* dirLight = new DirectionalLight(false);
	dirLight->transform.SetRotation(20, 114, -4);
	dirLight->SetDiffuseColor(1.0, 0.9, 0.9);
	dirLight->SetSpecularColor(1.0, 0.8, 0.4);
	dirLight->SetIntensity(1.5);

	DirectionalLight* dirLight2 = new DirectionalLight(false);
	dirLight2->transform.SetRotation(0, -60, 0);
	dirLight2->SetSpecularColor(0, 0, 0);
	dirLight2->SetIntensity(1.5);

	DirectionalLight* dirLight3 = new DirectionalLight(false);
	dirLight3->transform.SetRotation(70, 0, 0);
	dirLight3->SetIntensity(0.4);

	BushCourt* bushCourt = new BushCourt();	


	AddGameObject(cam);

	AddGameObject(dirLight);
	AddGameObject(dirLight2);
	AddGameObject(dirLight3);
	AddGameObject(bushCourt);


	
	LoadGameObjectsFromFile("Assets\\SceneFiles\\MainScene.txt");
}

void MainScene::Start()
{
	Scene::Start();
	Input::SetCursorMode("disabled");

	PathFindingManager::Instance().Generate(0, 0, 180, 180, 5);
	PathFindingManager::Instance().Start();

	PhysicsWorld::Instance().InitializeQuadtree(0, 0, 100, 100);
	PhysicsWorld::Instance().FillQuadtree(1); // Fill static quadtree
	PhysicsWorld::Instance().PerformCollisions(1);




}

void MainScene::LogicUpdate()
{
	if (Input::GetKeyDown(GLFW_KEY_ESCAPE))
	{
		GUIManager::Instance().GetCanvasByName("MainCanvas")->GetGUIObjectByName("LoadingText")->isActive = 1;
		GUIManager::Instance().Render(1);
		SceneManager::Instance().LoadNewScene("ExitScene");
		return;
	}

	
	PathFindingManager::Instance().ClosestNodeAt(cam->transform.GetPosition().x, cam->transform.GetPosition().y, cam->transform.GetPosition().z);





	Scene::LogicUpdate(); //Must be last statement!


}



