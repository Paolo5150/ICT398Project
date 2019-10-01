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
#include "Prefabs/Water.h"
#include "Prefabs/BushCourt.h"
#include "Prefabs/Lantern.h"
#include "Physics/PathFindingManager.h"

#include "Diag/DiagRenderer.h"
#include "GUI/GUIManager.h"
#include "GUI/Elements/GUIImage.h"
#include "GUI/Elements/GUIText.h"



#include "Components/PathFinder.h"
#include "Prefabs/Box.h"



MainScene::MainScene() : Scene("MainScene")
{
}

void MainScene::LoadAssets() {

	// Load splash screen
	GUIImage* image = new GUIImage("SplashImage", ContentManager::Instance().GetAsset<Texture2D>("logo"), 100, 100, 0, 0, 1, 1, 1, 1);
	GUIText* text = new GUIText("LoadingText", "Loading", 1, 95, glm::vec3(1), 2.5, 1);

	GUIManager::Instance().GetCanvasByName("MainCanvas")->AddGUIObject(image);
	GUIManager::Instance().GetCanvasByName("MainCanvas")->AddGUIObject(text);

	GUIManager::Instance().SetColorBuffer(0.8, 0.8, 0.8);
	GUIManager::Instance().Render(true, true);


	text->message = "Loading uncomfortable feelings...";
	GUIManager::Instance().Render(true);

	ContentManager::Instance().LoadModel("Assets\\Models\\Bench\\bench.obj", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\Table\\table.fbx", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\Chair\\chair.obj", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\LandfillBin\\landfillbin.obj", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\RecycleBin\\recyclebin.obj", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\BushCourt\\bushcourt.obj", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\Lantern\\lantern.obj", false, false);
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

	// Load this stuff as preserved so they can be used in the exit scene (so there's not much loading when transitioning)
	ContentManager::Instance().LoadModel("Assets\\Models\\Paolo\\paolo.fbx", false, true);
	ContentManager::Instance().LoadModel("Assets\\Models\\Drew\\drew.fbx", false, true);
	ContentManager::Instance().LoadModel("Assets\\Models\\Dylan\\dylan.fbx", false, true);


	ContentManager::Instance().LoadTexture("Assets\\Models\\Paolo\\textures\\paolo.png", true);
	ContentManager::Instance().LoadTexture("Assets\\Models\\Drew\\textures\\drew.png", true);
	ContentManager::Instance().LoadTexture("Assets\\Models\\Dylan\\textures\\Dylan.png", true);


	ContentManager::Instance().LoadModel("Assets\\Models\\PaoloText\\PaoloText.obj", false, true);
	ContentManager::Instance().LoadModel("Assets\\Models\\DrewText\\DrewText.obj", false, true);
	ContentManager::Instance().LoadModel("Assets\\Models\\DylanText\\DylanText.obj", false, true);

	image->isActive = 0;
	text->isActive = 0;
	text->message = "Loading next scene.."; //Just prepare the message for going to the exit scene
}

void MainScene::QuitScene() {

	Scene::QuitScene();

}
void MainScene::Initialize() {


	LightManager::Instance().SetAmbientLight(0.4, 0.4, 0.4);

	skybox = std::unique_ptr<Skybox>(new Skybox(ContentManager::Instance().GetAsset<CubeMap>("SunSet")));


	cam = new MainCamera();
	cam->transform.SetPosition(0, 10, 0);
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

	cam->AddComponent(new PathFinder()); //Temporary for debugging pathfinding
	for (unsigned i = 0; i < 5; i++) //Temporary for debugging pathfinding
	{
		pathfinders.push_back(new PathFinder());
	}

	locs.push_back(glm::vec3(-44, 2, -18)); //Temporary for debugging pathfinding
	locs.push_back(glm::vec3(-45, 2, 32)); //Temporary for debugging pathfinding
	locs.push_back(glm::vec3(-2, 2, 71)); //Temporary for debugging pathfinding
	locs.push_back(glm::vec3(71, 2, -2)); //Temporary for debugging pathfinding
	locs.push_back(glm::vec3(45, 2, -45)); //Temporary for debugging pathfinding
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

	if (Input::GetKeyDown(GLFW_KEY_SPACE))
		std::cout << "X: " << cam->transform.GetGlobalPosition().x << " Y: " << cam->transform.GetGlobalPosition().y << " Z: " << cam->transform.GetGlobalPosition().z << std::endl;

	if (Input::GetKeyPressed(GLFW_KEY_E))
	{
		std::cout << "X: " << cam->transform.GetGlobalPosition().x << " Y: " << cam->transform.GetGlobalPosition().y << " Z: " << cam->transform.GetGlobalPosition().z << std::endl;
	}

	if (Input::GetKeyPressed(GLFW_KEY_I)) //Temo: Sets end node for camera pathfinding
	{
		pathGoal = cam->transform.GetGlobalPosition();
	}
	else if (Input::GetKeyDown(GLFW_KEY_K)) //Temp: Generates a path from the camera to the location set
	{
		for (unsigned i = 0; i < PathFindingManager::Instance().nodeMap.size(); i++) //Temporary for debugging pathfinding
		{
			for (unsigned j = 0; j < PathFindingManager::Instance().nodeMap.at(i).size(); j++)
			{
				PathFindingManager::Instance().nodeMap.at(i).at(j)->bc->enableRender = 0;
			}
		}

		PathFinder* lpath = cam->GetComponent<PathFinder>("PathFinder");
		lpath->UnlockEndNode();
		lpath->GeneratePath(cam->transform.GetGlobalPosition(), glm::vec3(pathGoal));
		std::vector<PathNode*> path = lpath->GetNodes();
		nextNode = lpath->GetNextNodePos();

		for (unsigned i = 0; i < path.size(); i++)
		{
			path.at(i)->bc->enableRender = 1;
		}
	}
	else if (Input::GetKeyDown(GLFW_KEY_1) || Input::GetKeyDown(GLFW_KEY_2) || Input::GetKeyDown(GLFW_KEY_3) || Input::GetKeyDown(GLFW_KEY_4) || Input::GetKeyDown(GLFW_KEY_5)) //Temp: Generates a path from location 1, 2, 3, 4, or 5
	{
		for (unsigned i = 0; i < PathFindingManager::Instance().nodeMap.size(); i++) //Temporary for debugging pathfinding
		{
			for (unsigned j = 0; j < PathFindingManager::Instance().nodeMap.at(i).size(); j++)
			{
				PathFindingManager::Instance().nodeMap.at(i).at(j)->bc->enableRender = 0; //Turn off all renderers
			}
		}

		for (unsigned i = 0; i < pathfinders.size(); i++)
		{
			pathfinders.at(i)->UnlockEndNode(); //Unlock end nodes so we can use them for other pathfinders
		}

		unsigned option; //Which pathfinder/location to use

		if (Input::GetKeyDown(GLFW_KEY_1))
			option = 0;
		else if (Input::GetKeyDown(GLFW_KEY_2))
			option = 1;
		else if (Input::GetKeyDown(GLFW_KEY_3))
			option = 2;
		else if (Input::GetKeyDown(GLFW_KEY_4))
			option = 3;
		else if (Input::GetKeyDown(GLFW_KEY_5))
			option = 4;

		PathFinder* lpath = pathfinders.at(option);
		lpath->GeneratePath(locs.at(option), glm::vec3(cam->transform.GetGlobalPosition().x, cam->transform.GetGlobalPosition().y, cam->transform.GetGlobalPosition().z));
		std::vector<PathNode*> path = lpath->GetNodes();

		for (unsigned i = 0; i < path.size(); i++)
		{
			path.at(i)->bc->enableRender = 1; //Render path nodes
		}
	}
	else if (Input::GetKeyPressed(GLFW_KEY_U)) //Temp: Resets rendering of all nodes and unlocks all pathfinders' nodes
	{
		for (unsigned i = 0; i < PathFindingManager::Instance().nodeMap.size(); i++) //Temporary for debugging pathfinding
		{
			for (unsigned j = 0; j < PathFindingManager::Instance().nodeMap.at(i).size(); j++)
			{
				PathFindingManager::Instance().nodeMap.at(i).at(j)->bc->enableRender = 0;
			}
		}

		for (unsigned i = 0; i < pathfinders.size(); i++)
		{
			pathfinders.at(i)->UnlockEndNode();
		}
	}
	else if (Input::GetKeyDown(GLFW_KEY_Y)) //Temp: Faces and moves camera to next node
	{
		if (sqrt(pow(nextNode.x - cam->transform.GetPosition().x, 2) + pow(nextNode.y - cam->transform.GetPosition().y, 2) + pow(nextNode.z - cam->transform.GetPosition().z, 2)) > 7.5)
		{
			glm::vec3 toTarget = glm::vec3(nextNode.x, cam->transform.GetPosition().y, nextNode.z) - cam->transform.GetPosition();
			float yAngle = glm::degrees(glm::angle(cam->transform.GetLocalFront(), glm::normalize(toTarget)));
			glm::vec3 cross = glm::normalize(glm::cross(cam->transform.GetLocalFront(), glm::normalize(toTarget)));
			int s = glm::sign(cross.y);
			cam->transform.RotateBy((yAngle * s) * Timer::GetDeltaS(), 0, 1, 0);
			cam->transform.SetPosition(cam->transform.GetPosition() + (7.5f * Timer::GetDeltaS() * cam->transform.GetLocalFront()));
		}
		else
		{
			PathFinder* lpath = cam->GetComponent<PathFinder>("PathFinder");
			nextNode = lpath->GetNextNodePos();
		}
	}

	//PathFindingManager::Instance().ClosestNodeAt(cam->transform.GetPosition().x, cam->transform.GetPosition().y, cam->transform.GetPosition().z);

	Scene::LogicUpdate(); //Must be last statement!


}



