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
#include "Prefabs/Paolo.h"
#include "Prefabs/Drew.h"
#include "Prefabs/Dylan.h"
#include "GUI/GUIManager.h"
#include "GUI/Elements/GUIImage.h"
#include "GUI/Elements/GUIText.h"
#include "Diag/DiagRenderer.h"

namespace
{
	GameObject* dr;
	GameObject* p;
	GameObject* dy;
	Water* water;
	GUIText* text;
}
ExitScene::ExitScene() : Scene("ExitScene")
{
}

void ExitScene::LoadAssets() {

	ContentManager::Instance().LoadCubeMap("Assets\\SkyBoxes\\SunSet");	

	ContentManager::Instance().LoadTexture("Assets\\Textures\\water_normal.jpg", 0);
	ContentManager::Instance().LoadTexture("Assets\\Textures\\dudv.png", 0);




}

void ExitScene::QuitScene() {

	Scene::QuitScene();

}
void ExitScene::Initialize() {

	 text = new GUIText("Quit", "Left click to quit", 80, 1, glm::vec3(1), 2.5, 1);
	text->isActive = 0;
	GUIManager::Instance().GetCanvasByName("MainCanvas")->AddGUIObject(text);

	LightManager::Instance().SetAmbientLight(0.00, 0.00, 0.00);

	skybox = std::unique_ptr<Skybox>(new Skybox(ContentManager::Instance().GetAsset<CubeMap>("SunSet")));

	//std::vector<GameObject*> objs = FileUtils::ReadSceneFile("Assets\\SceneFiles\\MainScene.txt");

	MainCamera* cam = new MainCamera();
	cam->transform.SetPosition(100, 6, 0);
	cam->transform.SetRotation(0,-90, 0);

	DirectionalLight* dirLight = new DirectionalLight(false);
	dirLight->transform.SetRotation(60, 114, -4);
	dirLight->SetDiffuseColor(1.0, 0.9, 0.9);
	dirLight->SetSpecularColor(1.0, 0.8, 0.4);
	dirLight->SetIntensity(1.5);

	DirectionalLight* dirLight2 = new DirectionalLight(false);
	dirLight2->transform.SetRotation(cam->transform.GetRotation());
	dirLight2->transform.RotateBy(20, dirLight2->transform.GetLocalRight());
	dirLight2->SetIntensity(1.8);

	water = new Water();
	water->transform.SetScale(1000, 1000, 1);
	water->reflectionRefractionRatio = -1.0;	

	AddGameObject(cam);
	AddGameObject(dirLight);
	AddGameObject(dirLight2);

	LoadGameObjectsFromFile("Assets\\SceneFiles\\ExitScene.txt");

	p = GetGameobjectsByName("Paolo")[0];
	dr = GetGameobjectsByName("Drew")[0];
	dy = GetGameobjectsByName("Dylan")[0];

	AddGameObject(water);

}

void ExitScene::Start()
{
	Scene::Start();
	Input::SetCursorMode("disabled");

	//(GetGameobjectsByName("Main Camera")[0])->transform.RotateBy(90, 0, 1, 0);
	//(GetGameobjectsByName("Main Camera")[0])->transform.SetPosition(0, 2, 0);
	((MainCamera*)GetGameobjectsByName("Main Camera")[0])->blockRotation = 1;
	((MainCamera*)GetGameobjectsByName("Main Camera")[0])->blockMovement = 1;



}

void ExitScene::LogicUpdate()
{


	if (Input::GetMouseDown(0))
		EventDispatcher::Instance().DispatchEvent(new QuitRequestEvent());

	if (p->transform.GetGlobalPosition().y < 1)
	{
		p->transform.Translate(0, 15 * Timer::GetDeltaS(), 0);
		dr->transform.Translate(0, 15* Timer::GetDeltaS(), 0);
		dy->transform.Translate(0, 15 * Timer::GetDeltaS(), 0);
	}
	else
	{
		if (water->transform.GetGlobalPosition().y > -35)
			water->transform.Translate(0, -15 * Timer::GetDeltaS(), 0);
		else
			text->isActive = 1;
	}

	Scene::LogicUpdate(); //Must be last statement!


}



