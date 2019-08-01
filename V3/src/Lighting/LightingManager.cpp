#include "pch.h"

#include "LightingManager.h"
#include "..\Utils\UBOLibrary.h"
#include "..\Utils\ContentManager.h"
#include "..\Rendering\Layers.h"
#include "..\Rendering\RenderingEngine.h"
#include "..\Utils\Maths.h"
#include "..\Core\CameraOrthogonal.h"
#include "..\Core\Core.h"
#include "..\Events\EventDispatcher.h"
#include "..\Events\ApplicationEvents.h"
#include "..\Scene\SceneManager.h"


static int POINT_LIGHT_SIZE = 64; //Size in bytes + offsets
static int DIRECTIONAL_LIGHT_SIZE = 128;


LightManager& LightManager::Instance()
{
	static LightManager instance;
	return instance;
}

LightManager::~LightManager()
{

}

void LightManager::Initialize()
{	
	shadowCamera = std::unique_ptr<Camera>(new CameraOrthogonal(-1000, 1000, -1000, 1000, 0.1, 5000));
	shadowCamera->RemoveLayerMask(RenderingLayers::GUI);
	shadowCamera->RemoveLayerMask(RenderingLayers::TERRAIN);
	shadowCamera->RemoveLayerMask(RenderingLayers::WATER);
	shadowCamera->RemoveLayerMask(RenderingLayers::SKYBOX);

	shadowCamera->SetActive(false);
	fogEnabled = false;
	fogColor = glm::vec3(0.5, 0.5, 0.7);
	sceneMainCamera = nullptr;


	//Directional light UBO
	int directional_total_size = (MAX_LIGHTS * DIRECTIONAL_LIGHT_SIZE) + 4;
	direcionalLightsBuffer = Core::Instance().GetGraphicsAPI().CreateUniformBuffer(directional_total_size, UBOLibrary::DIRECTIONAL_LIGHTS);


	//Directional light UBO
	int point_total_size = (MAX_LIGHTS * POINT_LIGHT_SIZE) + 4;
	pointLightsBuffer = Core::Instance().GetGraphicsAPI().CreateUniformBuffer(point_total_size, UBOLibrary::POINT_LIGHTS);

	EventDispatcher::Instance().SubscribeCallback<SceneChangedEvent>([this, point_total_size, directional_total_size](Event* e){

		pointLightsBuffer = Core::Instance().GetGraphicsAPI().CreateUniformBuffer(point_total_size, UBOLibrary::POINT_LIGHTS);
		direcionalLightsBuffer = Core::Instance().GetGraphicsAPI().CreateUniformBuffer(directional_total_size, UBOLibrary::DIRECTIONAL_LIGHTS);
		sceneMainCamera = nullptr;
		shadowMaps.clear();
		return 0;
	});


}

bool LightManager::GetFogEnable()
{
	return fogEnabled;
}


void LightManager::SetFogEnable(bool fe)
{
	fogEnabled = fe;
}

void LightManager::UpdateUBOs()
{
	shadowMaps.clear();

	//Update Directional lights UBO
	std::vector<DirectionalLight*> allDirLights = SceneManager::Instance().GetCurrentScene().GetGameobjectsByName<DirectionalLight>("DirectionalLight");
	auto dirLightsIT = allDirLights.begin();	
	totalDirLights = allDirLights.size();

	direcionalLightsBuffer->Bind();
	int i = 0;

	
	//shadowCamera->isActive = 1;
	for (; dirLightsIT != allDirLights.end(); dirLightsIT++)
	{
		if (!(*dirLightsIT)->GetActive())
		{
			totalDirLights--;
			continue;
		}

		if ((*dirLightsIT)->GetIsCastingShadow() && sceneMainCamera != nullptr)
		{

			//Create shadow map
			(*dirLightsIT)->shadowMap->Bind();
			glClear(GL_DEPTH_BUFFER_BIT);
			shadowCamera->transform.SetPosition(sceneMainCamera->transform.GetPosition() - (*dirLightsIT)->transform.GetLocalFront() * 1000.0f);
			shadowCamera->transform.LookAt(shadowCamera->transform.GetPosition() + (*dirLightsIT)->transform.GetLocalFront());
			shadowCamera->UpdateViewMatrix();
			RenderingEngine::Instance().RenderBuffer(shadowCamera.get(), MaterialType::COLORONLY);
			(*dirLightsIT)->shadowMap->Unbind();


			shadowMaps.push_back((*dirLightsIT)->shadowMap.get());
		}
		direcionalLightsBuffer->AddDataRange(0 + i * DIRECTIONAL_LIGHT_SIZE, 64, glm::value_ptr((shadowCamera->GetProjectionMatrix() * shadowCamera->GetViewMatrix())));
		direcionalLightsBuffer->AddDataRange(64 + i * DIRECTIONAL_LIGHT_SIZE, 16, &(*dirLightsIT)->transform.GetPosition());
		direcionalLightsBuffer->AddDataRange(64 + 16 + i * DIRECTIONAL_LIGHT_SIZE, 12, &(*dirLightsIT)->transform.GetLocalFront());
		direcionalLightsBuffer->AddDataRange(64 + 32 + i * DIRECTIONAL_LIGHT_SIZE, 12, &(*dirLightsIT)->GetDiffuseColor());
		direcionalLightsBuffer->AddDataRange(64 + 48 + i * DIRECTIONAL_LIGHT_SIZE, 12, &(*dirLightsIT)->GetSpecularColor());
		direcionalLightsBuffer->AddDataRange(64 + 60 + i * DIRECTIONAL_LIGHT_SIZE, 4, &(*dirLightsIT)->GetIntensity());

		i++;
	}

	//shadowCamera->isActive = 0;
	direcionalLightsBuffer->AddDataRange( (MAX_LIGHTS * DIRECTIONAL_LIGHT_SIZE), 4, &totalDirLights);

	std::vector<PointLight*> allPointLights = SceneManager::Instance().GetCurrentScene().GetGameobjectsByName<PointLight>("PointLight");
	auto allPointLightsIT = allPointLights.begin();

	//Update point lights UBO
	totalPointLights = allPointLights.size();

	pointLightsBuffer->Bind();

	i = 0;
	for (; allPointLightsIT != allPointLights.end(); allPointLightsIT++)
	{
		if (!(*allPointLightsIT)->GetActive())
		{
			totalPointLights--;
			continue;
		}

		pointLightsBuffer->AddDataRange(0 + i * POINT_LIGHT_SIZE, 16, &(*allPointLightsIT)->transform.GetGlobalPosition());
		pointLightsBuffer->AddDataRange(16 + i * POINT_LIGHT_SIZE, 12, &(*allPointLightsIT)->transform.GetLocalFront());
		pointLightsBuffer->AddDataRange(32 + i * POINT_LIGHT_SIZE, 12, &(*allPointLightsIT)->GetDiffuseColor());
		pointLightsBuffer->AddDataRange(48 + i * POINT_LIGHT_SIZE, 12, &(*allPointLightsIT)->GetSpecularColor());
		pointLightsBuffer->AddDataRange(60 + i * POINT_LIGHT_SIZE, 4, &(*allPointLightsIT)->GetIntensity());
		i++;
	}

	pointLightsBuffer->AddDataRange((MAX_LIGHTS * POINT_LIGHT_SIZE), 4, &totalPointLights);
	
}

void LightManager::Update()
{
	if (sceneMainCamera == nullptr)
	{
		sceneMainCamera = Camera::GetCameraByName("Main Camera");

	}
	UpdateUBOs();

	//Deactivate textures here
	for (int i = 0; i < shadowMaps.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + (i + 10));
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glActiveTexture(GL_TEXTURE0);
}

// From GL_TEXTURE30 onwards -> SHADOWS
// Between 20 and 30 -> reflection

//Send shadow maps to current shader
void LightManager::SendShadowToShader(Shader& shader)
{

	shader.Bind(); //This line is kind of vital
	//Load shadow maps
	std::string uniformName = "shadowMap[";

	shader.SetInt("shadowMapCount", shadowMaps.size());
	//TODO: improc ve this, cubemap and texture can be bind together, should not be the case
	for (int i = 0; i < shadowMaps.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + (i + 30));

		std::stringstream ss;
		ss << uniformName;
		ss << i;
		ss << ']';
		shader.SetInt(ss.str(), (i + 30));
		shadowMaps[i]->GetDepthTexture()->Bind();
	}
}


void LightManager::SetAmbientLight(float r, float g, float b)
{
	ambientLight.x = r;
	ambientLight.y = g;
	ambientLight.z = b;

}
