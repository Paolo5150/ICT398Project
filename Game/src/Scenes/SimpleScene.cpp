#include "pch.h"
#include "Components\MeshRenderer.h"
#include "SimpleScene.h"
#include "Components/BoxCollider.h"


GameObject* g;
GameObject* g2;

MainCamera* cam;
DirectionalLight* dirLight;
PointLight* pointLight;

SimpleScene::SimpleScene() : Scene("SimpleScene")
{
}

void SimpleScene::LoadAssets() {

	//AssetLoader::Instance().LoadModel("Assets\\Models\\Pumpkin\\pumpkin.obj",false);	
	ContentManager::Instance().LoadModel("Assets\\Models\\Nanosuit\\nanosuit.obj");
	//AssetLoader::Instance().LoadModel("Assets\\Models\\Crate\\crate.obj",false,false);
	ContentManager::Instance().LoadCubeMap("Assets\\SkyBoxes\\SunSet");
	ContentManager::Instance().LoadEquirectangularMap("Assets\\SkyBoxes\\HDR\\HDR_029_Sky_Cloudy_Ref.hdr");

	ContentManager::Instance().LoadTexture("Assets\\Textures\\wood.jpg", 0);

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

}

void SimpleScene::QuitScene() {

	Scene::QuitScene();

}
void SimpleScene::Initialize() {

	Timer::SetDisplayFPS(1);
	LightManager::Instance().SetAmbientLight(0.00, 0.00, 0.00);

	skybox = std::unique_ptr<Skybox>(new Skybox(ContentManager::Instance().GetAsset<CubeMap>("SunSet")));
	
	g = new GameObject("Test");
	ContentManager::Instance().GetAsset<Model>("Nanosuit")->PopulateGameObject(g);

	Material m;
	m.SetShader(ContentManager::Instance().GetAsset<Shader>("PBR"));
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("iron_normal"),"normalMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("iron_albedo"), "albedoMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("iron_roughness"), "roughnessMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("iron_metallic"), "metallicMap");
	m.Loadtexture(ContentManager::Instance().GetAsset<Texture2D>("bamboo_ao"), "aoMap");
	m.LoadCubemap(ContentManager::Instance().GetAsset<CubeMap>("SunSet"),"cubemap0");

	g->ApplyMaterial(m);


/*	g2 = new GameObject("Test");
	ContentManager::Instance().GetAsset<Model>("Nanosuit")->PopulateGameObject(g2);

	BoxCollider* b2 = (BoxCollider*)g2->AddComponent(new BoxCollider());
	b2->transform.SetPosition(0, 5, 0);
	b2->transform.SetScale(2, 10, 2);
	b2->enableRender = 1;
	g2->transform.SetPosition(-50, 0, 0);
	//b2->ResetCollisionLayer();
	//b2->AddCollisionLayer(CollisionLayers::DEFAULT);
	b2->collisionCallback = [](GameObject* ggg) {
		Logger::LogInfo("Colliding with", ggg->name);
	};*/

	
	cam = new MainCamera();
	cam->transform.SetPosition(0, 10, 50);
	cam->transform.SetRotation(0, 180, 0);

	
	dirLight = new DirectionalLight(false);
	dirLight->transform.SetRotation(45, 180, 0);
	dirLight->SetIntensity(0.2);

	pointLight = new PointLight();

	pointLight->SetIntensity(10);
	pointLight->transform.SetPosition(0, 0, 5);
	
	AddGameObject(cam);
	AddGameObject(dirLight);
	AddGameObject(pointLight);
	AddGameObject(g);
	//AddGameObject(g2);



}

void SimpleScene::Start()
{
	Scene::Start();
	Input::SetCursorMode("disabled");

	PhysicsWorld::Instance().InitializeQuadtree(0, 0, 5000, 5000);

}

void SimpleScene::LogicUpdate()
{
	pointLight->transform.Translate(0, 0.01, 0.0);
	
	static float timer = 0;
	static bool done = false;
	timer += Timer::GetDeltaS();

	if (timer >= 3 && !done)
	{
		done = 1;
		//GUIManager::Instance().RemoveCanvas("MainCanvas");
	}

	if (Input::GetKeyPressed(GLFW_KEY_ESCAPE))
		EventDispatcher::Instance().DispatchEvent(new QuitRequestEvent());


	if (Input::GetKeyDown(GLFW_KEY_T))
		Input::SetCursorMode("normal");

	if (Input::GetKeyDown(GLFW_KEY_Y))
		Input::SetCursorMode("disabled");

	if (Input::GetKeyDown(GLFW_KEY_R))
		Restart();
	
	Scene::LogicUpdate(); //Must be last statement!

}

void SimpleScene::Restart()
{
	Logger::LogInfo("Reloading scene");
	SceneManager::Instance().ReloadCurrent();
}

void SimpleScene::UpdateUI()
{

}


