/******************************************************************************
Class: PhysicsObject
Implements:
Author: Rich Davison	<richard.davison4@newcastle.ac.uk>, Pieran Marris<p.marris@newcastle.ac.uk>
Description: This class represents the physical properties of your game's
entities - their position, orientation, mass, collision volume, and so on.

		(\_/)								-_-_-_-_-_-_-_,------,
		( '_')								_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
	 /""""""""""""\=========     -----D		-_-_-_-_-_-_-~|__( ^ .^) /
	/"""""""""""""""""""""""\				_-_-_-_-_-_-_-""  ""
....\_@____@____@____@____@_/			

*//////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Quaternion.h"
#include "Matrix3.h"
#include "CollisionShape.h"
#include <functional>

class PhysicsEngine;
class GameObject;

class PhysicsObject
{
	friend class PhysicsEngine;
	friend class GameObject; //Just to allow construction 

public:
	PhysicsObject();
	~PhysicsObject();

	//<--------- GETTERS ------------->
	bool				IsEnabled()				const 	{ return m_Enabled; }
	void				ToggleEnable()			{ m_Enabled = !m_Enabled; }

	float				GetFriction()			const 	{ return m_Friction; }

	const GLMVector3&		GetPosition()			const 	{ return m_Position; }
	const GLMVector3&		GetLinearVelocity()		const 	{ return m_LinearVelocity; }
	const GLMVector3&		GetForce()				const 	{ return m_Force; }
	float				GetInverseMass()		const 	{ return m_InvMass; }

	const Quaternion&	GetOrientation()		const 	{ return m_Orientation; }
	const GLMVector3&		GetAngularVelocity()	const 	{ return m_AngularVelocity; }
	const GLMVector3&		GetTorque()				const 	{ return m_Torque; }
	const GLMMatrix3&		GetInverseInertia()		const 	{ return m_InvInertia; }

	CollisionShape*		GetCollisionShape()		const 	{ return m_colShape; }

	const GLMMatrix4& GetWorldSpaceTransform()     const;

	//<--------- SETTERS ------------->
	void SetFriction(float friction)				{ m_Friction = friction; }

	void SetPosition(const GLMVector3& v)				{ m_Position = v;	m_wsTransformInvalidated = true; }
	void SetLinearVelocity(const GLMVector3& v)		{ m_LinearVelocity = v; }
	void SetForce(const GLMVector3& v)					{ m_Force = v; }
	void SetInverseMass(const float& v)				{ m_InvMass = v; }

	void SetOrientation(const Quaternion& v)		{ m_Orientation = v; m_wsTransformInvalidated = true; }
	void SetAngularVelocity(const GLMVector3& v)		{ m_AngularVelocity = v; }
	void SetTorque(const GLMVector3& v)				{ m_Torque = v; }
	void SetInverseInertia(const GLMMatrix3& v)		{ m_InvInertia = v; }

	void SetCollisionShape(CollisionShape* colShape)	{ m_colShape = colShape; }


	void SetOnCollisionCallback(std::function<bool(PhysicsObject*)> onCollisionFunction) { m_OnCollisionCallback = onCollisionFunction; }


	//<--------- Additional Variables ------------->
	std::vector<GLMVector3> verletPos;
	std::vector<GLMVector3> verletAcc;
	std::vector<GLMVector3> verletVel;
	std::vector<bool> colarch;

	bool update_con;
	int score_counter;
	std::string name;

protected:
	GameObject*			m_Parent;


	bool				m_Enabled;

	mutable bool		m_wsTransformInvalidated;
	mutable GLMMatrix4		m_wsTransform;

	float				m_Friction;

	//<---------LINEAR-------------->
	GLMVector3		m_Position;
	GLMVector3		m_LinearVelocity;
	GLMVector3		m_Force;
	float		m_InvMass;

	//<----------ANGULAR-------------->
	Quaternion  m_Orientation;
	GLMVector3		m_AngularVelocity;
	GLMVector3		m_Torque;
	GLMMatrix3     m_InvInertia;

	//<----------COLLISION------------>
	CollisionShape* m_colShape;
	std::function<bool(PhysicsObject*)> m_OnCollisionCallback;  //Returns true to process the collision, false to ignore
	
};