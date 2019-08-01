#pragma once

#include "DirectionalLight.h"
#include "PointLight.h"
#include "..\Core\GameObject.h"
#include "..\Rendering\UniformBuffer.h"
#include <list>
#include <vector>

class Light;

#define MAX_LIGHTS 10

/**
* @class LightManager
* @brief Manages how lighting information is sent to the GPU
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class LightManager
{
public:
	/**
	* @brief						Return the light manager instance
	*
	* @pre							The light manager must exist
	* @post							The light manager instance is returned
	*/
	static LightManager& Instance();

	/**
	* @brief						Destroy the light manager
	*
	* @pre							The light object must exist
	*/
	~LightManager();

	/**
	* @brief						Initialize the light manager, setus up the buffers for the light on the GPU
	*
	* @pre							The light manager must exist
	* @post							The light manager is ready
	*/
	void Initialize();

	/**
	* @brief						Update lighting information to the GPU
	*
	* @pre							The light manager must exist
	* @post							The light information is sent to the GPU
	*/
	void Update();

	/**
	* @brief						Sends shadow maps to GPU
	*
	* @pre							The light manager must exist, the shadow maps are not null
	* @post							The light shadows are sent to the GPU
	* @param shader					The shader that will get the shadows
	*/
	void SendShadowToShader(Shader& shader);

	/**
	* @brief						Whether the fog is enabled
	*
	* @pre							The light manager must exist
	* @post							The fog is enabled/disabled accoring to the argument
	* @param enable					Whether the fog will be enabled
	*/
	void SetFogEnable(bool enable);


	/**
	* @brief						Get whether the fog is enabled
	*
	* @pre							The light manager must exist
	*/
	bool GetFogEnable();

	/**
	* @brief						Set the ambient light coloe
	*
	* @pre							The light manager must exist
	* @post							The ambient light is set
	* @param r						The red channel amount
	* @param g						The green channel amount
	* @param b						The blue channel amount
	*/
	void SetAmbientLight(float r, float g, float b);

	/**
	* @brief						Return the clipping plane
	*
	* @pre							The light manager must exist
	* @post							The clipping plane is returned
	* @return						The clipping plane
	*/
	glm::vec4& GetClippingPlane(){ return clippingPlane; }

	/**
	* @brief						Set the clipping plane
	*
	* @pre							The light manager must exist
	* @post							The clipping plane is set
	* @param cp						The clipping plane
	*/
	void SetClippingPlane(glm::vec4 cp){ clippingPlane = cp; }

	/**
	* @brief						The number of shadow maps
	*
	* @pre							The light manager must exist
	* @post							The number of shadow maps is returned
	* @return						The shadow maps number
	*/
	int GetShadowMapsCount(){ return shadowMaps.size(); }


	/**
	* @brief						Get the ambient light color
	*
	* @pre							The light manager must exist
	* @post							The ambient light color is returned
	* @return						The sambient light color
	*/
	glm::vec3& GetAmbientLight(){ return ambientLight; }

	/**
	* @brief						Referene to the scene main camera
	*/
	GameObject* sceneMainCamera;



private:
	LightManager() {};
	void UpdateUBOs();
	/**
	* @brief						The fog color
	*/
	glm::vec3 fogColor;

	/**
	* @brief						The total number of directional lights
	*/
	int totalDirLights;

	/**
	* @brief						The total number of point lights
	*/
	int totalPointLights;


	/**
	* @brief						The ambient light color
	*/
	glm::vec3 ambientLight;

	/**
	* @brief						The list of shadow maps
	*/
	std::vector<FrameBuffer*> shadowMaps;

	/**
	* @brief						Whether the fog is enabled
	*/
	bool fogEnabled;

	/**
	* @brief						The clipping plane
	*/
	glm::vec4 clippingPlane;

	/**
	* @brief						The directional light uniform buffer
	*/
	std::unique_ptr<UniformBuffer> direcionalLightsBuffer;
	/**
	* @brief						The point light uniform buffer 
	*/
	std::unique_ptr<UniformBuffer> pointLightsBuffer;

	/**
	* @brief						The camera used for shadows
	*/
	std::unique_ptr<Camera> shadowCamera;


};
