#pragma once
#include "..\Core\GameObject.h"
#include "..\Affordances\AffordanceObject.h"
#include "Billquad.h"

class AffordanceObject;
class AIEmotion;
class AffordanceAgent;
class PathFinder;
class Rigidbody;
/**
* @class Riley
* @brief Premade gameobject for a Riley NPC
*
*
* @author Paolo Ferri
* @version 01
* @date 05/10/2019
*
*
* @bug No known bugs.
*/

class Riley : public GameObject, public AffordanceObject
{

public:
	/**
	* @brief						Create a new object
	*/
	Riley();
	/**
	* @brief						Destroy the object
	*/
	~Riley();
	/**
	* @brief						Update the object
	* @pre							The object must exist
	*/
	void Update() override;
	/**
	* @brief						Strt callbackt
	* @pre							The object must exist
	*/
	void Start() override;
	/**
	* @brief						Collision enter callbackt
	* @param g						The other collider
	* @param collisioni				Collision information
	*/
	void OnCollisionEnter(Collider* g, Collision& collision) override;
	/**
	* @brief						Collision stay callbackt
	* @param g						The other collider
	* @param collisioni				Collision information
	*/
	void OnCollisionStay(Collider* g, Collision& collision) override;
	/**
	* @brief						Collision exit callbackt
	* @param g						The other collider
	*/
	void OnCollisionExit(Collider* g) override;
	void Test(AffordanceObject*);
	/**
	* @brief						Return the billquad object
	*/
	Billquad& GetBillquad() { return *billquad; }

private:
	Billquad* billquad;
	void Move(); //Navigates to affordances or wanders if no affordance is selected
	AffordanceAgent* aa;
	GameObject* player;
	AIEmotion* aiE;
	PathFinder* pf;
	Rigidbody* rb;
	glm::vec3 nextPos; //Next position to navigate to
	float timer = 0; //Used to regenerate path every now and then
	AffordanceObject* pathAffordanceObject; //Which affordance the current path is made from
	bool waiting = false; //Waiting while wandering

};