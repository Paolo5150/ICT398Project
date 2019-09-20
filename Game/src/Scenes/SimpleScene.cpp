#include "pch.h"
#include "Components\MeshRenderer.h"
#include "SimpleScene.h"
#include "Components/BoxCollider.h"
#include "Core/Core.h"
#include "Prefabs/Bench.h"
#include "Prefabs/Chair.h"
#include "Prefabs/Table.h"
#include "Prefabs/Box.h"
#include "Prefabs/Terrain.h"
#include "Prefabs/LandfillBin.h"
#include "Prefabs/RecycleBin.h"
#include "Prefabs/Water.h"

#include "Diag/DiagRenderer.h"
#include "GUI/GUIManager.h"
#include "GUI/Elements/GUIImage.h"
#include "GUI/Elements/GUIText.h"

namespace
{
	PointLight* pointLight;
	DirectionalLight* dirLight;
	DirectionalLight* dirLight2;

}

SimpleScene::SimpleScene() : Scene("SimpleScene")
{
}

void SimpleScene::LoadAssets() {



}



void SimpleScene::QuitScene() {

	Scene::QuitScene();

}
void SimpleScene::Initialize() {


	LightManager::Instance().SetAmbientLight(0.00, 0.00, 0.00);

	skybox = std::unique_ptr<Skybox>(new Skybox(ContentManager::Instance().GetAsset<CubeMap>("SunSet")));

	MainCamera* cam = new MainCamera();
	cam->transform.SetPosition(-3, 10, 20);
	cam->transform.SetRotation(0, 180, 0);
	
	DirectionalLight* dirLight = new DirectionalLight(false);
	dirLight->transform.SetRotation(40,114,-4);
	dirLight->SetDiffuseColor(1.0, 0.9, 0.9);
	dirLight->SetSpecularColor(1.0, 0.8, 0.4);
	dirLight->SetIntensity(1.5);

	DirectionalLight* dirLight2 = new DirectionalLight(false);
	dirLight2->transform.SetRotation(90,0,0);
	dirLight2->SetSpecularColor(1.0, 0.8, 0.4);

	dirLight2->SetIntensity(0.2);




	AddGameObject(cam);

	AddGameObject(dirLight);
	AddGameObject(dirLight2);


	LoadGameObjectsFromFile("Assets\\SceneFiles\\SimpleScene.txt");

}

void SimpleScene::Start()
{
	Scene::Start();
	Input::SetCursorMode("disabled");
	PhysicsWorld::Instance().InitializeQuadtree(0, 0,100, 100);
	PhysicsWorld::Instance().FillQuadtree(1); // Fill static quadtree

}

void SimpleScene::LogicUpdate()
{
	//GetGameobjectsByName("LandfillBin")[0]->transform.RotateBy(0.1, 0, 0, 1);
	//GetGameobjectsByName("LandfillBin")[0]->transform.Translate(0.01, 0, 0);

	//((PointLight*)GetGameobjectsByName("PointLight")[0])->transform.Translate(0, 0, 0.1);


	if (Input::GetKeyDown(GLFW_KEY_ESCAPE))
	{
		GUIManager::Instance().GetCanvasByName("MainCanvas")->GetGUIObjectByName("LoadingText")->isActive = 1;
		GUIManager::Instance().Render(1);
		SceneManager::Instance().LoadNewScene("ExitScene");
		return;
	}

	if (Input::GetMouseDown(0))
	{
		pointLight->transform.Translate(0, 0, 5 * Timer::GetDeltaS());
	}
	if (Input::GetMouseDown(1))
	{
		pointLight->transform.Translate(0, 0, -5 * Timer::GetDeltaS());
	}

	Scene::LogicUpdate(); //Must be last statement!

	pointLight->RenderDiag();

}



