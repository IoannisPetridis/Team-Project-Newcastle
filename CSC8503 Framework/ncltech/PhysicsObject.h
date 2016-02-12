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
#include <nclgl\Quaternion.h>
#include <nclgl\Matrix3.h>
#include "CollisionShape.h"
#include <functional>

class PhysicsEngine;

class PhysicsObject
{
	friend class PhysicsEngine;
	friend class GameObject; //Just to allow construction 

public:
	PhysicsObject();
	~PhysicsObject();

	//<--------- GETTERS ------------->
	bool				IsEnabled()				const 	{ return m_Enabled; }

	float				GetFriction()			const 	{ return m_Friction; }
	float				GetElasticity()			const 	{ return m_Elasticity; }
	const Vector3&		GetPosition()			const 	{ return m_Position; }
	const Vector3&		GetLinearVelocity()		const 	{ return m_LinearVelocity; }
	const Vector3&		GetForce()				const 	{ return m_Force; }
	float				GetInverseMass()		const 	{ return m_InvMass; }

	const Quaternion&	GetOrientation()		const 	{ return m_Orientation; }
	const Vector3&		GetAngularVelocity()	const 	{ return m_AngularVelocity; }
	const Vector3&		GetTorque()				const 	{ return m_Torque; }
	const Matrix3&		GetInverseInertia()		const 	{ return m_InvInertia; }

	CollisionShape*		GetCollisionShape()		const 	{ return m_colShape; }

	const Matrix4& GetWorldSpaceTransform()     const;

	inline GameObject *GetParent(){ return m_Parent; } //get the game object parent of this physics object



	//<--------- SETTERS ------------->
	void SetFriction(float friction)				{ m_Friction = friction; }
	void SetElasticity(float Elasticity)				{ m_Elasticity = Elasticity; }

	void SetPosition(const Vector3& v)				{ m_Position = v;	m_wsTransformInvalidated = true; }

	void SetLinearVelocity(const Vector3& v)		{ m_LinearVelocity = v; }
	//for verlet
	//void SetLinearVelocity(const Vector3& v)		{ m_LinearVelocity = v; m_LastPosition = m_Position - m_LinearVelocity / 60.f; }
	
	void SetForce(const Vector3& v)					{ m_Force = v; }
	void SetInverseMass(const float& v)				{ m_InvMass = v; }

	void SetOrientation(const Quaternion& v)		{ m_Orientation = v; m_wsTransformInvalidated = true; }
	void SetAngularVelocity(const Vector3& v)		{ m_AngularVelocity = v; }
	void SetTorque(const Vector3& v)				{ m_Torque = v; }
	void SetInverseInertia(const Matrix3& v)		{ m_InvInertia = v; }

	void SetCollisionShape(CollisionShape* colShape)	{ m_colShape = colShape; }

	bool GetIsGlobal() { return isGlobal; }
	void SetIsGlobal(bool in) { isGlobal=in; }

	bool GetIsWake() { return isWake; }
	void SetIsWake(bool in) { isWake = in; }

	bool GetIsTardis() { return isTardis; }
	void SetIsTardis(bool in) { isTardis = in; }

	bool GetIsAI() { return isAI; }
	void SetIsAI(bool in) { isAI = in; }

	float GetFade() { return fade; }
	void SetFade(float in) { fade = in; }

	void SetIsAlreadyHit(bool in) { isAlreadyHit = in; }
	bool GetIsAlreadyHit() { return isAlreadyHit; }

	void SetIsAlreadyHitProtect(bool in) { isAlreadyHitProtect = in; }
	bool GetIsAlreadyHitProtect() { return isAlreadyHitProtect; }

	void SetIsProtectedBall(bool in) { protectedBall = in; }
	bool GetIsProtectedBall() { return protectedBall; }

	void SetOnCollisionCallback(std::function<bool(PhysicsObject*)> onCollisionFunction) { m_OnCollisionCallback = onCollisionFunction; }

protected:
	GameObject*			m_Parent;

	bool				m_Enabled;

	mutable bool		m_wsTransformInvalidated;
	mutable Matrix4		m_wsTransform;

	float				m_Friction;
	float				m_Elasticity;
	//<---------LINEAR-------------->
	Vector3		m_Position;
	//for verlet
	//Vector3		m_LastPosition;
	Vector3		m_LinearVelocity;
	Vector3		m_Force;
	float		m_InvMass;
	float		oldVel;
	Vector3		oldPos;
	//<----------ANGULAR-------------->
	Quaternion  m_Orientation;
	Vector3		m_AngularVelocity;
	Vector3		m_Torque;
	Matrix3     m_InvInertia;


	//<----------COLLISION------------>
	CollisionShape* m_colShape;
	std::function<bool(PhysicsObject*)> m_OnCollisionCallback;  //Returns true to process the collision, false to ignore
	bool isGlobal = false;
	bool isWake=true;
	bool isTardis = false;
	bool isAlreadyHit = true;
	float fade;
	bool isAI = false;
	bool protectedBall = false;
	bool isAlreadyHitProtect = false;
};