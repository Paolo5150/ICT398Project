#pragma once

#include "..\Core\Component.h"
#include "..\Components\MeshRenderer.h"

#include "..\Physics\CollisionChecks.h"
#include "..\Core\Timer.h"
#include "..\Physics\CollisionLayer.h"
#include <functional>

class SphereCollider;
class BoxCollider;


/**
* @class Collider
* @brief Generic class for a collider component
*
*
* @author Paolo Ferri
* @version 01
* @date 27/04/2019
*
* @bug No known bugs.
*/
class Collider : public Component
{
public:
	/**
	* @brief		Collider types
	*/
	enum COLLIDER_TYPE
	{
		SPHERE,
		BOX
	};

	/**
	* @brief		Constructor
	* @pre			The collider does not exist
	* @post			The collider is created
	* @param		The collider name
	*/
	Collider(std::string name);

	/**
	* @brief		Destructor
	* @pre			The collider must exist
	* @post			The collider is destroyed
	*/
	virtual ~Collider(){  };

	/**
	* @brief		The collider transform
	*/
	Transform transform;

	/**
	* @brief		Callback invoked when the component is attached to a gameobhect
	* @param go		The gameobject the component belongs to
	*/
	virtual void OnAttach(GameObject* go) override ;

	/**
	* @brief		The collider mesh renderer
	*/
	std::unique_ptr<MeshRenderer> meshRenderer;

	/**
	* @brief		Overridden method for engine update
	*/
	void EngineUpdate() override;

	void Start() override;

	/**
	* @brief		Virtual method to initialize collider
	*/
	virtual void InitializeMeshRenderer(){};

	/**
	* @brief		Virtual method to initialize collider
	*/
	virtual void Initialize(){};

	/**
	* @brief		Whether the collider should be rendered
	*/
	bool enableRender;

	/**
	* @brief		Overridable function pointer invoked when collision occurs
	*/
	std::function<void(Collider*, Collision&)> OnCollisionEnterCallback;

	/**
	* @brief		Overridable function pointer invoked when collision occurs
	*/
	std::function<void(Collider*, Collision&)> OnCollisionStayCallback;

	/**
* @brief		Overridable function pointer invoked when collision occurs
*/
	std::function<void(Collider*)> OnCollisionExitCallback;


	/**
	* @brief		The collider type
	*/
	COLLIDER_TYPE colliderType;

	/**
	* @brief		Add collision layer
	* @pre			The collider exist
	* @post			The collision layer is added
	* @param layer	The collision layer
	*/
	void AddCollisionLayer(unsigned int layer) { collisionLayer |= layer; }

	/**
	* @brief		Remove all collision layers
	* @pre			The collider exist
	* @post			The collision layer is reset
	*/
	void ResetCollisionLayer() { collisionLayer = 0; }

	/**
	* @brief		Remove a collision layer
	* @pre			The collider exist
	* @post			The collision layer is removed
	* @param layer	The layer to be removed
	*/
	void RemoveCollisionLayer(unsigned layer) { collisionLayer = collisionLayer & (~layer); }

	/**
	* @brief		Get the collision layers
	* @pre			The collider exist
	* @post			The collision layer is returned
	*/
	unsigned GetCollisionLayer() { return collisionLayer; }

	/**
	* @brief		Add a collision layer the collider can collide against
	* @pre			The collider exist
	* @post			The collision layer is added
	* @param layer	The layer to be added
	*/
	void AddCollideAgainstLayer(unsigned layer) { collideAgainstLayer |= layer; }

	/**
	* @brief		Remove all collision layers the colliders collide agasint
	* @pre			The collider exist
	* @post			The collision layer is reset
	*/
	void ResetCollideAgainstLayer() { collideAgainstLayer = 0; }

	/**
	* @brief		Remove a collision layer the collider can collider against
	* @pre			The collider exist
	* @post			The collision layer is removed
	* @param layer	The layer to be removed
	*/
	void RemoveCollideAgainstLayer(unsigned layer) { collideAgainstLayer = collideAgainstLayer & (~layer); }

	/**
	* @brief		Get the collision layers the collider can collider against
	* @pre			The collider exist
	* @post			The collision layer is returned
	*/
	unsigned GetCollideAgainstLayer() { return collideAgainstLayer; }

	void SetMass(float m) { mass = glm::abs(m); CalculateMomentOfIntertia(); }
	float GetMass() { return mass; }

	glm::vec3& GetMomentOfIntertia() { return momentOfIntertia; };

	virtual void CalculateCubicDimensions() { cubicDimension = glm::vec3(); };
	glm::vec3 cubicDimension;

	
	std::list<Collider*> collidersInCollision;
protected:

	virtual void CalculateMomentOfIntertia() = 0;
	float mass;
	/**
	* @brief		The collision layer
	*/
	int collisionLayer;

	/**
	* @brief		The collision layer the collider can collide against
	*/
	int collideAgainstLayer;

	glm::vec3 momentOfIntertia;


};