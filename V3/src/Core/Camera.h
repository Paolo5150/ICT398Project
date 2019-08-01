#pragma once
#include "..\Events\EventDispatcher.h"
#include "..\Events\WindowEvents.h"
#include "GameObject.h"
#include "..\Core\Logger.h"
#include "..\Rendering\Layers.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <map>
#include <list>
#include <string>


enum CAMERA_TYPE
{
	PERSPECTIVE,
	ORTHOGONAL
};

/**
* @class Camera
* @brief Generic class that defines a virtual camera
*
*
* @author Paolo Ferri
* @version 01
* @date 21/03/2019
*
*
* @bug No known bugs.
*/

class Camera : public GameObject
{
public:
	/**
	* @brief Destroy the camera object
	*
	* @pre The camera object exists
	* @post The camera object is destroyed
	*/
	~Camera();

	/**
	* @brief Get the list of created cameras
	*
	* @pre The list eists
	* @post The list is returned
	*/
	static std::vector<Camera*>& GetAllCameras() {
		return allCamerasVector;
	};

	/**
	* @brief Get a specific camera by name
	*
	* @post If available, the camera first camera with matching name is returned. Nullptr is returned if not found
	*/
	static Camera* GetCameraByName(std::string name);

	/**
	* @brief Get the culling layers of the camera
	*/
	unsigned GetCullingMask() { return cullingMask; };

	/**
	* @brief Remove a layer from the culling mask
	*/
	void AddLayerMask(unsigned layer) { cullingMask |= layer; };

	/**
	* @brief Add a layer to the culling mask
	*/
	void RemoveLayerMask(unsigned layer){ cullingMask = cullingMask & (~layer); }

	/**
	* @brief Add all layers from the culling mask
	*/
	void RemoveAllMaskLayers() { cullingMask = 0; }

	/**
	* @brief Update the view matrix of the camera based on position and rotation of the object.
	*
	* @pre The view matrix exists
	* @post The view matrix is updated
	*/
	void UpdateViewMatrix();

	/**
	* @brief Update the object
	*
	* @pre The object exists and added to a scene
	* @post The object is updated
	*/
	void Update() override;

	/**
	* @brief Set the camera depth
	*
	* @param d The new camera depth
	*/
	void SetDepth(int d) { depth = d; UpdateOrdererdCameras(); };

	/**
	* @brief Set the camera depth
	*
	* @param d The new camera depth
	*/
	int GetDepth(){ return depth; }

	/**
	* @brief Return the view matrix of the camera
	*/
	glm::mat4& GetViewMatrix() { return viewMatrix; }

	/**
	* @brief Return the projection matrix of the camera
	*/
	glm::mat4& GetProjectionMatrix() { return projectionMatrix; }

	/**
	* @brief Return the near plane
	*/
	float GetNearPlane() { return nearPlane; };

	/**
	* @brief Return the far ratio
	*/
	float GetFarPlane() { return farPlane; };


protected:

	/**
	* @brief Callback method invoked when the screen is resied. Updates the projection matrix
	*
	* @param The event 
	*/
	virtual bool OnScreenResize(Event* e) = 0;

	/**
	* @brief The culling mask
	*/
	unsigned cullingMask;

	/**
	* @brief The camera depth
	*/
	int depth;

	/**
	* @brief The camera type (orthographic or perspective)
	*/
	CAMERA_TYPE camerType;

	/**
	* @brief Creates the camera object. Private as no generic camera can be created
	*
	* @pre The camera does not exist
	* @post The camera object is created
	*/
	Camera(std::string name);

	/**
	* @brief Token used to unsubscribe callback
	*/
	std::string resizeEventToken;
	/**
	* @brief The view matrix
	*/
	glm::mat4 viewMatrix;

	/**
	* @brief The projection matrix
	*/
	glm::mat4 projectionMatrix;

	/**
	* @brief The camera near clipping plane
	*/
	float nearPlane;

	/**
	* @brief The camera far clipping plane
	*/
	float farPlane;




private:

	/**
	* @brief The list of all the cameras
	*/
	static std::list<Camera*> allCameras;

	/**
	* @brief The list of all the cameras ordererd by depth
	*/
	static std::vector<Camera*> allCamerasVector; 

	/**
	* @brief Update the allCamerasVector by updating the cameras by depth
	*
	* @pre The vector is not empty
	* @post The cameras in the vector are oredered by depth
	*/
	static void UpdateOrdererdCameras();



};







