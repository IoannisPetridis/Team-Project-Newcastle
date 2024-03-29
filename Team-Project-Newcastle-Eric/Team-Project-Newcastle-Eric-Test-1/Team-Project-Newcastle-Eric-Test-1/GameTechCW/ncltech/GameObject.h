/******************************************************************************
Class:GameObject
Implements:
Author: Rich Davison	<richard.davison4@newcastle.ac.uk> and YOU!
Description: This is the base class for all of the objects in your game - the
player character, enemies, pickups etc would all be derived classes of the
GameObject.

This class 'wraps up' all of the communication between the subsystems of your
game - it has a renderer component (The SceneNode you are used to using), a
'physics' component (The PhysicsNode you've been introduced to in this code
download), and eventually you'll add a 'sound' component, in the short sound
workshop in semester 2.

The sub systems handle the updating of the 'sub components' of a GameEntity,
so in the Update function of this class will just be the 'gameplay' specific
type functionality (has the player picked up some health / has he shot an enemy
and so forth).

-_-_-_-_-_-_-_,------,
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""

*//////////////////////////////////////////////////////////////////////////////
#pragma once
#include <nclgl\Matrix4.h>
#include "PhysicsObject.h"
#include <vector>

class Scene;
class PhysicsEngine;

class GameObject
{
	//This are the only class that can manually set the world transform
	friend class Scene;
	friend class MyScene;
	friend class ActionHandler;

public:
	GameObject(const std::string& name = "");
	~GameObject();

	PhysicsObject*		Physics() { return m_PhysicsObject; }
	void	SetPhysicsObj(PhysicsObject* obj) { m_PhysicsObject = obj; }

	const std::string&	GetName()			{ return m_Name; }
	std::vector<GameObject*>& GetChildren() { return m_Children; }
	
	GameObject*			FindGameObject(const std::string& name);
	void				AddChildObject(GameObject* child);


	void			SetLocalTransform(const Matrix4& transform)			{ m_LocalTransform = transform; }
	const Matrix4&  GetLocalTransform()									{ return m_LocalTransform; }


	void			SetColour(const Vector4& colour)	{ m_Colour = colour; }
	const Vector4&	GetColour()							{ return m_Colour; }

	void			SetBoundingRadius(float radius)		{ m_BoundingRadius = radius; }
	float			GetBoundingRadius()					{ return m_BoundingRadius; }

	void SetScene(Scene* scene) { m_Scene = scene; }
	void RemoveFromScene();

protected:
	virtual void OnRenderObject()				{};				//Handles OpenGL calls to Render the object
	virtual void OnUpdateObject(float dt)		{};				//Override to handle things like AI etc on update loop

protected:
	std::string					m_Name;
	Scene*						m_Scene;
	GameObject*					m_Parent;
	std::vector<GameObject*>	m_Children;

	PhysicsObject*				m_PhysicsObject;

	Vector4						m_Colour;
	float						m_BoundingRadius;	//For Frustum Culling
	Matrix4						m_LocalTransform;
	Matrix4						m_WorldTransform;
};