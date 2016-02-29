/******************************************************************************
Class: PhysicsEngine
Implements:
Author: Rich Davison <richard.davison4@newcastle.ac.uk> and YOU!
Description:
A very simple physics engine class, within which to implement the
material introduced in the Game Technologies module. This is just a rough
skeleton of how the material could be integrated into the existing codebase -
it is still entirely up to you how the specifics should work. Now C++ and
graphics are out of the way, you should be starting to get a feel for class
structures, and how to communicate data between systems.

It is worth poinitng out that the PhysicsEngine is constructed and destructed
manually using static functions. Why? Well, we probably only want a single
physics system to control the entire state of our game world, so why allow
multiple systems to be made? So instead, the constructor / destructor are
hidden, and we 'get' a single instance of a physics system with a getter.
This is known as a 'singleton' design pattern, and some developers don't like
it - but for systems that it doesn't really make sense to have multiples of,
it is fine!

		(\_/)
		( '_')
	 /""""""""""""\=========     -----D
	/"""""""""""""""""""""""\
....\_@____@____@____@____@_/

*//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "TSingleton.h"
#include "PhysicsObject.h"
#include "Constraint.h"
#include "Manifold.h"
#include <vector>
#include <algorithm>
#include <mutex>


#define SOLVER_ITERATIONS 20

#define FALSE	0
#define TRUE	1

struct CollisionPair	//Forms the output of the broadphase collision detection
{
	PhysicsObject* objectA;
	PhysicsObject* objectB;
};

struct OctreeStr
{
	PhysicsObject*	parent;
	std::vector<PhysicsObject*> children;
};

class PhysicsEngine : public TSingleton<PhysicsEngine>
{
	friend class TSingleton < PhysicsEngine > ;
public:

	//Add/Remove Physics Objects
	void AddPhysicsObject(PhysicsObject* obj);
	void RemovePhysicsObject(PhysicsObject* obj);

	//Add Constraints
	void AddConstraint(Constraint* c) { m_Constraints.push_back(c); }
	
	//Update Physics Engine
	void Update(float deltaTime);			//Remember DeltaTime is 'seconds' since last update not milliseconds
	
	//NEWNEWNEW
	void Feedback();				//feedback collision data before actually resolve and integration 

	//Debug draw all physics objects, manifolds and constraints
	void DebugRender();

	//Getters / Setters 
	bool IsPaused()						{ return m_IsPaused; }
	void SetPaused(bool paused)			{ m_IsPaused = paused; }

	bool IsGameover()					{ return m_Gameover; }
	void SetGameover(bool go)			{ m_Gameover = go; }

	void SetUpdateTimestep(float updateTimestep) { m_UpdateTimestep = updateTimestep; }
	float GetUpdateTimestep()			{ return m_UpdateTimestep; }

	const Vector3& GetGravity()			{ return m_Gravity; }
	void SetGravity(const Vector3& g)	{ m_Gravity = g; }

	float GetDampingFactor()			{ return m_DampingFactor; }
	void  SetDampingFactor(float d)		{ m_DampingFactor = d; }

	float GetDeltaTime()				{ return m_UpdateTimestep; }

	float GetCollisionDetectionDis()	{ return CollisionDetectionDis; }
	void  SetCollisionDetectionDis(float n)	{ CollisionDetectionDis = n; }

	//check if there is a collision between objA and objB, if there is, 
	//return true
	bool CheckCollision(PhysicsObject* obja, PhysicsObject* objb);
	std::vector<CollisionPair> m_BroadphaseCollisionPairs;

	//return a copy of narrowphase collision pair list exclude ground to ground collision
	std::vector<CollisionPair>* GetVPair() { return &VPairList; }
	std::vector<CollisionPair> GetCPair() { return CPairList; }

	//Clear all per-frame data
	void PhysicsEngineClear();

	void toggledebugdraw() {
		DEBUGDRAW_CONSTRAINTS = !DEBUGDRAW_CONSTRAINTS;
		DEBUGDRAW_MANIFOLDS = !DEBUGDRAW_MANIFOLDS;
		DEBUGDRAW_COLLISIONVOLUMES = !DEBUGDRAW_COLLISIONVOLUMES;
	}

protected:
	PhysicsEngine();
	~PhysicsEngine();

	//The actual time-independant update function
	void UpdatePhysics();

	//Handles broadphase collision detection
	void BroadPhaseCollisions();

	//Handles narrowphase collision detection
	void NarrowPhaseCollisions();
	void NarrowPhaseCollisionsBatch(size_t batch_start, size_t batch_end); //<--- The worker function for multithreading

	//Updates all physics objects position, orientation, velocity etc (default method uses symplectic euler integration)
	void UpdatePhysicsObjects();	
	void UpdatePhysicsObjectsBatch(size_t batch_start, size_t batch_end);  //<--- The worker function for multithreading
	void UpdatePhysicsObject(PhysicsObject* obj);						   //<--- The actual code to update the given physics object
	
	//Solves all engine constraints (constraints and manifolds)
	void SolveConstraints();

	//Octree
	//not Really an Octree, just a revised distance dependent grouping algorithm
	void OctreeBuild();
	bool OctreeCheck(PhysicsObject* objA, PhysicsObject* objB);
	float CollisionDetectionDis;
	
protected:
	void ClearCPair() { CPairList.clear(); }

protected:
	bool		m_IsPaused;
	bool		m_Gameover;
	bool		m_Collision;

	std::vector<CollisionPair> CPairList;
	std::vector<CollisionPair> VPairList;

	float		m_UpdateTimestep, m_UpdateAccum;
	
	Vector3		m_Gravity;
	float		m_DampingFactor;

	//std::vector<CollisionPair> m_BroadphaseCollisionPairs;

	std::vector<PhysicsObject*> m_PhysicsObjects;

	std::vector<Constraint*>	m_Constraints;			// Misc constraints between pairs of objects
	
	std::vector<Manifold*>		m_Manifolds;			// Contact constraints between pairs of objects

	std::mutex					m_ManifoldsMutex;

	bool DEBUGDRAW_CONSTRAINTS;
	bool DEBUGDRAW_MANIFOLDS;
	bool DEBUGDRAW_COLLISIONVOLUMES;

	//Octree
	std::vector<OctreeStr*>			Octrees;
};