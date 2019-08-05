#include "pch.h"
#include "Model.h"
#include "..\Core\GameObject.h"
#include "..\Components\MeshRenderer.h"
#include "..\Utils\ContentManager.h"

Model::Model()
{
//	rootNode = NULL;
}

Model::~Model()
{
	//Logger::LogError("Model", name, "died");
	allMeshes.clear();
}



std::vector<Mesh*> Model::GetMeshes()
{
	std::vector<Mesh*> v;

	for (int i = 0; i < allMeshes.size(); i++)
	{
		v.push_back(allMeshes[i]);

	}
	return v;

}


void Model::PopulateGameObject(GameObject* go)
{	
	for (int i = 0; i < allMeshes.size(); i++)
	{

		GameObject* c = new GameObject(meshesNames[i]); //Will become a unique ptr in scene
		MeshRenderer* m = (MeshRenderer*)c->AddComponent(new MeshRenderer(allMeshes[i], allMaterials[i]));

		
		c->AddComponent(m);

		go->AddChild(c);

	}

}


std::unique_ptr<GameObject> Model::CreateGameObject()
{
	std::unique_ptr<GameObject> e = std::unique_ptr<GameObject>(new GameObject(name));

	for (int i = 0; i < allMeshes.size(); i++)
	{

		GameObject* c = new GameObject(meshesNames[i]);
		MeshRenderer* m =(MeshRenderer*) c->AddComponent(new MeshRenderer(allMeshes[i], allMaterials[i]));
		m->GetMaterial().SetColor(0, 1, 0);
		c->AddComponent(m);
		e->AddChild(c);

	}
	return std::move(e);
}



