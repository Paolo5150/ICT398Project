#include "pch.h"
#include "Components\MeshRenderer.h"
#include "ExitScene.h"
#include "Components/BoxCollider.h"
#include "Core/Core.h"
#include "Prefabs/Bench.h"
#include "Prefabs/Chair.h"
#include "Prefabs/Table.h"
#include "Prefabs/Terrain.h"
#include "Prefabs/LandfillBin.h"
#include "Prefabs/RecycleBin.h"
#include "Prefabs/Water.h"

#include "Diag/DiagRenderer.h"

ExitScene::ExitScene() : Scene("ExitScene")
{
}

void ExitScene::LoadAssets() {

	ContentManager::Instance().LoadCubeMap("Assets\\SkyBoxes\\SunSet");	

	ContentManager::Instance().LoadTexture("Assets\\Textures\\water_normal.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\Textures\\dudv.png", 0);
	ContentManager::Instance().LoadModel("Assets\\Models\\Paolo\\paolo.fbx", false, false);
	ContentManager::Instance().LoadModel("Assets\\Models\\Drew\\drew.fbx", false, false);

	ContentManager::Instance().LoadTexture("Assets\\Models\\Paolo\\textures\\paolo.png", 0);
	ContentManager::Instance().LoadTexture("Assets\\Models\\Drew\\textures\\drew.png", 0);



}

void ExitScene::QuitScene() {

	Scene::QuitScene();

}
void ExitScene::Initialize() {

	LightManager::Instance().SetAmbientLight(0.00, 0.00, 0.00);

	skybox = std::unique_ptr<Skybox>(new Skybox(ContentManager::Instance().GetAsset<CubeMap>("SunSet")));

	//std::vector<GameObject*> objs = FileUtils::ReadSceneFile("Assets\\SceneFiles\\MainScene.txt");

	MainCamera* cam = new MainCamera();
	cam->transform.SetPosition(0, 10, 50);
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

	Water* water = new Water();
	water->transform.SetScale(500, 500, 1);


	AddGameObject(cam);

	AddGameObject(dirLight);
	AddGameObject(dirLight2);

	AddGameObject(water);

}

void ExitScene::Start()
{
	Scene::Start();
	Input::SetCursorMode("disabled");

	(GetGameobjectsByName("Main Camera")[0])->transform.RotateBy(90, 0, 1, 0);
	(GetGameobjectsByName("Main Camera")[0])->transform.SetPosition(0, 2, 0);
	((MainCamera*)GetGameobjectsByName("Main Camera")[0])->blockRotation = 1;


}

void ExitScene::LogicUpdate()
{


	if (Input::GetKeyDown(GLFW_KEY_ESCAPE))
		EventDispatcher::Instance().DispatchEvent(new QuitRequestEvent());


	Scene::LogicUpdate(); //Must be last statement!


}



