#pragma once

#include "GL\glew.h"
#include "Mesh.h"
#include <vector>
#include <string>
#include <map>
#include "Texture2D.h"
#include "Material.h"
#include "ModelNode.h"

class GameObject;

/**
* @class Model
* @brief Describe a 3D model
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class Model : public Asset
{
public:
	friend class AssimpWrapper;
	friend class ModelAnimation;
	/**
	* @brief		Creates the model object
	* @post			The model is created
	*/
	Model();

	/**
	* @brief		Destroy the Model object
	* @pre			The Model object exist
	* @post			The Model is destroyed
	*/
	virtual ~Model();

	/**
	* @brief		Return the list of meshes of the model
	* @pre			The Model object exist
	* @post			The list of meshes of the model is returned
	* @return		The list of meshes of this model
	*/
	std::vector<Mesh*> GetMeshes();

	/**
	* @brief		Create a GameObject with the needed component attached to render the model
	* @pre			The Model object exist
	* @post			 GameObject with the needed components is created
	* @return		A redy to be used game object with the meshes and components needed to render the model
	*/
	virtual std::unique_ptr<GameObject> CreateGameObject();

	/**
	* @brief		Populate the game object argument with the needed component to render the model
	* @pre			The Model object exist, the game object must exist
	* @post			The GameObject is populated with the needed components
	*/
	virtual void PopulateGameObject(GameObject* go);

	/**
	* @brief		The name of the model
	*/
	std::string name;

	/**
	* @brief		The map of meshes
	*/
	std::map<int, Mesh*>& GetMeshesMap(){ return allMeshes; };
protected:

	//ModelNode* rootNode;
	//std::map<std::string, ModelNode*> allNodes;


	/**
	* @brief The meshes of the model
	*/
	std::map<int, Mesh*> allMeshes;

	/**
	* @brief The materials of the model (when imported from external asset)
	*/
	std::map<int, Material> allMaterials;

	/**
	* @brief The meshes names
	*/
	std::map<int, std::string> meshesNames;
};

