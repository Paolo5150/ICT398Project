#pragma once

#include "..\Core\GameObject.h"
#include "..\Components\Rigidbody.h"
#include "..\Rendering\Texture2D.h"
#include "..\Components\MeshRenderer.h"
#include "..\Components\AIEmotion.h"
#include <unordered_set>

/**
* @class Billquad
* @brief Premade gameobject for a 'billquad' object, used to display emotions
*
*
* @author Paolo Ferri
* @version 01
* @date 05/10/2019
*
*
* @bug No known bugs.
*/

class Billquad :
	public GameObject
{
public:
	/**
	* @brief						Create a new Billquad object
	*/
	Billquad();
	/**
	* @brief						Create a new Billquad object
	* @param texture				The texture to be displayed
	*/
	Billquad(Texture2D* texture);
	/**
	* @brief						Destroy the Billquad object
	*/
	~Billquad();
	/**
	* @brief						Update the object
	* @pre							The object must exist
	*/
	void Update() override;
	/**
	* @brief						Start callbackt
	* @pre							The object must exist
	*/
	void Start() override;
	/**
	* @brief						Set the texture to be displayed
	* @param texture				The pointer to the texture
	*/
	void SetTexture(Texture2D* texture);
	/**
	* @brief						Check the status of the emotions and display accordingly
	* @param aiE					The emotion component
	*/
	void CheckEmotions(AIEmotion* aiE);

	/**
	* @brief						Add texture to the queue to be displayed
	* @param t						The pointer to the texture
	*/
	void AddToQ(Texture2D* t);


private:
	MeshRenderer* meshRenderer;

	void Initialize();
	Texture2D* texture;
	float timer;
	float coolDownTimer;
	bool isRendering;
	bool isCoolDown;
	std::unordered_set<Texture2D*> texturesQueue;
};
