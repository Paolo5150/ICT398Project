
#include "pch.h"
#include "GameObject.h"
#include "Component.h"
//#include "..\Graphics\Shader.h"
//#include "..\Core\Camera.h"
#include "..\Components\MeshRenderer.h"
#include "..\Core\Timer.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\SphereCollider.h"
#include "ColliderInfo.h"


GameObject::GameObject(std::string name, bool isActive, unsigned int layer, GameObject* parent) : transform(Transform(this))
{
	SetName(name);
	SetActive(isActive);
	SetLayer(layer);
	SetParent(parent);
	SetIsSelfManaged(false, true);
	SetIsStatic(0);
	flashing = 0;
}

GameObject::~GameObject()
{
	_components.clear();

	
	if (_parent != nullptr)
	{
		_parent->transform.transformChildren.remove(&transform);
		_parent->_children.remove(this);
	}
	//Logger::LogError("Gameobject", name, "destroyed");

}



void GameObject::SetName(std::string name)
{
	if (name.length() > 0)
	{
		this->name = name;
		_parent = nullptr;
		_layer = RenderingLayers::DEFAULT;
	}
}

void GameObject::FlagToBeDestroyed()
{
//	SetActive(false);
	_toBeDestroyed = true;

	for (auto it = std::begin(_children); it != std::end(_children); it++)
		{
		(*it)->FlagToBeDestroyed();
		}
	
}

void GameObject::OnAddToScene(Scene& scene)
{
	for (auto it = std::begin(_components); it != std::end(_components); it++)
	{
		(*it)->OnGameObjectAddedToScene(this);
	}


	for (auto it = std::begin(_children); it != std::end(_children); it++)
		{
		(*it)->OnAddToScene(scene);
		}
	
}

void GameObject::SetIsSelfManaged(bool sm, bool includeChildren)
{

	_isSelfManaged = sm;

	if (includeChildren == true)
	{
		for (auto it = std::begin(_children); it != std::end(_children); it++)
		{
			(*it)->SetIsSelfManaged(sm, includeChildren);
		}
	}
}

void GameObject::SetActive(bool active, bool includeChildren)
{
	_isActive = active;

	for (auto it = std::begin(_components); it != std::end(_components); it++)
	{
		(*it)->SetActive(active);
	}

	if (includeChildren == true)
	{
		for (auto it = std::begin(_children); it != std::end(_children); it++)
		{
			(*it)->SetActive(active,includeChildren);
		}
	}
}

void GameObject::SetIsStatic(bool st, bool includeChildren)
{
	_isStatic = st;

	if (includeChildren == true)
	{
		for (auto it = std::begin(_children); it != std::end(_children); it++)
		{
			(*it)->SetIsStatic(st, includeChildren);
		}
	}
}

void GameObject::SetLayer(unsigned int layer, bool includeChildren)
{
	if (layer == 0)
		_layer = 0;
	else
	_layer |= layer;

	if (includeChildren == true)
	{
		for (auto it = std::begin(_children); it != std::end(_children); it++)
		{
			(*it)->SetLayer(layer, includeChildren);
		}
	}
}

void GameObject::SetParent(GameObject *parent)
{
	if (parent != this)
	{
		if(parent !=nullptr)
		_parent = parent;
		else
		{
			if (_parent != nullptr)
			{
				_parent->transform.transformChildren.remove(&transform);
			}
		}
	}
}

void GameObject::FlashColor(float r, float g, float b)
{
	ApplyColor(r,g,b);
	colorTimer = 0.1f;
	flashing = 1;
}

void GameObject::LoadCollidersFromFile(std::string absolutePathToFile)
{
	std::vector<ColliderInfo> t = FileUtils::ReadColliderFile("Assets\\Colliders\\Bench.txt");

	for (int i = 0; i < t.size(); i++)
	{
		if (t[i].type == "BC")
		{
			BoxCollider* bc = new BoxCollider();
			bc->enableRender = t[i].render;
			bc->transform.SetPosition(t[i].p);
			bc->transform.SetScale(t[i].s);
			bc->transform.SetRotation(t[i].r);
			AddComponent(bc);
		}
		else if (t[i].type == "SC")
		{
			SphereCollider* sc = new SphereCollider();
			sc->enableRender = t[i].render;
			sc->transform.SetPosition(t[i].p);
			sc->transform.SetScale(t[i].s.x, t[i].s.x, t[i].s.x);
			AddComponent(sc);
		}


		// Uncomment this to see the lamba in action
		// If "collisionCallback" is reassigned to a lambda, the OnCollision method will be overridden
		// This can be used to have different methods callbacks for different colliders.

		/*bc->collisionCallback = [](GameObject* g) {
			Logger::LogInfo("Greetings, I'm a lambda callback and I collided against", g->GetName());
		};*/

	}
}



std::string GameObject::GetName() const
{
	return this->name;
}

bool GameObject::GetActive() const
{
	return _isActive;
}

bool GameObject::GetToBeDestroyed() const
{
	return _toBeDestroyed;
}


unsigned int GameObject::GetLayer() const
{
	return _layer;
}

GameObject* GameObject::GetParent() const
{
	return _parent;
}

void GameObject::AddChild(GameObject* child)
{
	if (child != this)
	{
		bool found = 0;
		for (auto it = _children.begin(); it != _children.end(); it++)
		{
			found = (*it) == child;
		}

		if (!found)
		{			
			child->SetParent(this);
			child->transform.parent = &transform;
			_children.push_back(child);
			transform.transformChildren.push_back(&child->transform);
			transform.UpdateHierarchy();
		}
	}

}

Component* GameObject::AddComponent(std::unique_ptr<Component>& component)
{
	bool found = false;

	for (auto it = _components.begin(); it != _components.end(); it++)
	{
		found = (*it) == component;
	}

	if (!found)
	{
		Component* toRet = component.get();
		toRet->SetParent(this);
		toRet->OnAttach(this);
		_components.push_back(std::move(component));
		return toRet;
	}
	return nullptr;

}

Component* GameObject::AddComponent(Component* component)
{
	bool found = false;

	for (auto it = _components.begin(); it != _components.end(); it++)
	{
		found = (*it).get() == component;
	}

	if (!found)
	{
		std::unique_ptr<Component> unique = std::unique_ptr<Component>(component);
		unique->SetParent(this);
		unique->OnAttach(this);
		_components.push_back(std::move(unique));
		return component;
	}
	return nullptr;

}


void GameObject::RemoveChild(std::string childName)
{
	if (HasChild(childName) == true)
	{
		GetChild(childName)->SetParent(nullptr);
		_children.remove_if([&](GameObject* gameObject) {return gameObject->GetName() == childName; });
	}
}

void GameObject::RemoveComponent(std::string componentName)
{

	
	
}

void GameObject::RemoveComponentInChild(std::string childName, std::string componentName)
{
	if (HasChild(childName) == true)
	{
		GetChild(childName)->RemoveComponent(componentName);
	}
}

GameObject* GameObject::GetChild(std::string childName) const
{
	std::list<GameObject*>::const_iterator it;
	it = std::find_if(std::begin(_children), std::end(_children), [&](GameObject* gameObject) -> GameObject* {if (gameObject->GetName() == childName){ return gameObject; } else { return nullptr; }});

	if (it != std::end(_children))
	{
		return *it;
	}
	else
	{
		return nullptr;
	}
}


std::list<GameObject*>& GameObject::GetChildList()
{
	return _children;
}


bool GameObject::HasChild(std::string childName) const
{
	std::list<GameObject*>::const_iterator it;
	it = std::find_if(std::begin(_children), std::end(_children), [&](GameObject* child) {return child->GetName() == childName; });

	if (it != std::end(_children))
	{
		return true;
	}
	else
	{
		return false;
	}
}


void GameObject::Start()
{
	auto itc = _components.begin();
	for (; itc != _components.end(); itc++)
		if ((*itc)->GetActive() == true)
			(*itc)->Start();
}

void GameObject::Update()
{
	auto it = _children.begin();
	for (; it != _children.end(); it++)
		if ((*it)->GetActive() == true)
			(*it)->Update();

	auto itc = _components.begin();
	for (; itc != _components.end(); itc++)
		if ((*itc)->GetActive() == true)
			(*itc)->Update();
}

void GameObject::EngineUpdate()
{


	auto it = _children.begin();
	for (; it != _children.end(); it++)
		(*it)->EngineUpdate();

	auto itc = _components.begin();
	for (; itc != _components.end(); itc++)
		(*itc)->EngineUpdate();
}

void GameObject::LateUpdate()
{


	auto it = _children.begin();
	for (; it != _children.end(); it++)
		(*it)->LateUpdate();

	/*auto itc = _components.begin();
	for (; itc != _components.end(); itc++)
		(*itc)->LateUpdate();*/
}



void GameObject::PrintHierarchy()
{
	std::string o = "\n";
	PrintHierarchy(0, o);
	Logger::LogInfo("{}", o);
}

void GameObject::PrintHierarchy(int indentation, std::string& output)
{
	for (int i = 0; i < indentation; i++)
		output += "...";

	output += GetName();

	auto it = _children.begin();

	for (; it != _children.end(); it++)
	{
		output += "\n";
		(*it)->PrintHierarchy(indentation + 1, output);
	}
}

GameObject* GameObject::GetRoot()
{
	if (_parent == nullptr)
		return this;
	else
	{
		return _parent->GetRoot();
	}
}

void GameObject::ApplyColor(float r, float g, float b)
{
	/*Renderer* rend = (GetComponentByType<Renderer>("Renderer"));

	if (rend != nullptr)
	{
		rend->GetMaterial(MaterialType::DEFAULT).SetColor(r, g, b);
		rend->GetMaterial(MaterialType::NOLIGHT).SetColor(r, g, b);
		rend->GetMaterial(MaterialType::COLORONLY).SetColor(r, g, b);
		//Logger::LogInfo("Applied material!");
	}

	auto it = _children.begin();

	for (; it != _children.end(); it++)
	{
		(*it)->ApplyColor(r,g,b);
	}*/
}


void GameObject::ApplyMaterial(Material mat, MaterialType mt)

{
	Renderer* r = (GetComponentByType<Renderer>("Renderer"));	

	if (r != nullptr)
	{
		r->SetMaterial(mat, mt);
		
		//Logger::LogInfo("Applied material!");
	}

	auto it = _children.begin();

	for (; it != _children.end(); it++)
	{
		(*it)->ApplyMaterial(mat, mt);
	}
}
