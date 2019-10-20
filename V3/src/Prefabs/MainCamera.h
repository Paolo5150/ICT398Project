#pragma once
#include "..\Core\CameraPerspective.h"
#include "..\Core\Input.h"
#include "..\Components\AffordanceAgent.h"
#include "..\Affordances\AffordanceObject.h"

class Rigidbody;

/**
* @class MainCamera
* @brief Specialized perspective camera used in the MainScene
*
*
* @author Paolo Ferri
* @version 01
* @date 10/04/2019
*
*
* @bug No known bugs.
*/
class MainCamera : public CameraPerspective, public AffordanceObject
{
public:

	/**
	* @brief		Create a MainCamera object
	*
	* @pre			The MainCamera does not exist
	* @post			The MainCamera is created
	*
	*/
	MainCamera();

	void Update() override;
	void Start() override;
	void OnCollisionEnter(Collider* c, Collision& collision) override;
	void OnCollisionStay(Collider* c, Collision& collision) override;


	bool blockRotation;
	bool blockMovement;
private:
	float m_movementSpeed;
	float m_rotationSpeed;
	Rigidbody* rb;
	AffordanceAgent* affordanceAgent;
	GameObject* collectedObject;
};

