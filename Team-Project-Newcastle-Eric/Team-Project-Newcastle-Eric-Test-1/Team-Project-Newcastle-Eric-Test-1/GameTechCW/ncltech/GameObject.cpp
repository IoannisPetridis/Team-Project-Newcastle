#include "GameObject.h"
#include "PhysicsEngine.h"

GameObject::GameObject(const std::string& name)
{
	m_Scene = NULL;
	m_Parent = NULL;
	m_Name = name;

	m_Colour = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoundingRadius = 1.f;

	m_LocalTransform.ToIdentity();
	m_WorldTransform.ToIdentity();

	m_PhysicsObject = new PhysicsObject();	//initilize the physics object

	PhysicsEngine::Instance()->AddPhysicsObject(m_PhysicsObject);	//add to physics list
}

GameObject::~GameObject()
{
}

GameObject*			GameObject::FindGameObject(const std::string& name)
{
	//Has this object got the same name?
	if (GetName().compare(name) == 0)
	{
		return this;
	}

	//Recursively search ALL child objects and return the first one matching the given name
	for (auto child : m_Children)
	{
		//Has the object in question got the same name?
		GameObject* cObj = child->FindGameObject(name);
		if (cObj != NULL)
		{
			return cObj;
		}
	}

	//Object not found with the given name
	return NULL;
}

void				GameObject::AddChildObject(GameObject* child)
{
	m_Children.push_back(child);
	child->m_Parent = this;
	child->m_Scene = this->m_Scene;
}

void	GameObject::RemoveFromScene() {
	this->m_Parent = NULL;
	this->m_Scene = NULL;
}
