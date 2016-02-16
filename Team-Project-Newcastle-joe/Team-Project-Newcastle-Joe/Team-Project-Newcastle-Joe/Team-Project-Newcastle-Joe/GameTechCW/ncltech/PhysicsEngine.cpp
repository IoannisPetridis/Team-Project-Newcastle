#pragma once
#include "PhysicsEngine.h"
#include "GameObject.h"
#include "CollisionDetection.h"
#include "AssetsManager.h"

#include <nclgl\Window.h>

PhysicsEngine::PhysicsEngine()
{
	m_IsPaused			= true;
	m_Gameover			= false;
	m_UpdateTimestep	= 1.0f / 60.f;
	m_UpdateAccum		= 0.0f;
	m_Gravity			=  Vector3(0.0f, -9.81f, 0.0f);
	m_DampingFactor		= 1.0f;
	CollisionDetectionDis = 400.0f;

	DEBUGDRAW_CONSTRAINTS = false;
	DEBUGDRAW_MANIFOLDS = false;
	DEBUGDRAW_COLLISIONVOLUMES = false;
}

PhysicsEngine::~PhysicsEngine()
{
	for (PhysicsObject* obj : m_PhysicsObjects)
	{
		delete obj;
	}
	m_PhysicsObjects.clear();

	for (Constraint* c : m_Constraints)
	{
		delete c;
	}
	m_Constraints.clear();

	for (Manifold* m : m_Manifolds)
	{
		delete m;
	}
	m_Manifolds.clear();
}

void PhysicsEngine::AddPhysicsObject(PhysicsObject* obj)
{
	m_PhysicsObjects.push_back(obj);
}

void PhysicsEngine::RemovePhysicsObject(PhysicsObject* obj)
{
	auto found_loc = std::find(m_PhysicsObjects.begin(), m_PhysicsObjects.end(), obj);

	if (found_loc != m_PhysicsObjects.end())
	{
		m_PhysicsObjects.erase(found_loc);
	}
}

void PhysicsEngine::Update(float deltaTime)
{
	m_UpdateAccum += deltaTime;	//deltatime is actually time duration, updatetimestep is the preset time step
	while (m_UpdateAccum >= m_UpdateTimestep)
	{
		m_UpdateAccum -= m_UpdateTimestep;
		if (!m_IsPaused) UpdatePhysics();
	}
	//this controls the physicsengine refresh frequency based on the rendering engine
}


void PhysicsEngine::UpdatePhysics()
{
	for (Manifold* m : m_Manifolds)
	{
		delete m;
	}
	m_Manifolds.clear();

	//Check for collisions
	OctreeBuild();
	BroadPhaseCollisions();
	NarrowPhaseCollisions();

	//Solve collision constraints
	SolveConstraints();

	//Update movement
	UpdatePhysicsObjects();
}

void PhysicsEngine::DebugRender()
{
	//#if DEBUGDRAW_MANIFOLDS
	if (DEBUGDRAW_MANIFOLDS) {
		for (Manifold* m : m_Manifolds)
		{
			m->DebugDraw();
		}
	}
	//#endif

//#if DEBUGDRAW_CONSTRAINTS
	if (DEBUGDRAW_CONSTRAINTS) {
		for (Constraint* c : m_Constraints)
		{
			c->DebugDraw();
		}
	}
//#endif

//#if DEBUGDRAW_COLLISIONVOLUMES
	if (DEBUGDRAW_COLLISIONVOLUMES) {
		for (PhysicsObject* obj : m_PhysicsObjects)
		{
			if (obj->GetCollisionShape() != NULL)
			{
				obj->GetCollisionShape()->DebugDraw(obj);
			}
		}
	}
//#endif
}


void PhysicsEngine::UpdatePhysicsObjects()
{
	for (PhysicsObject* obj : m_PhysicsObjects)
	{
		UpdatePhysicsObject(obj);
	}
}

void PhysicsEngine::UpdatePhysicsObject(PhysicsObject* obj)
{
	//disable gravity, position and velocity update to put object at rest
	if (!obj->m_Enabled) {
		if (obj->m_InvMass > 0.00001f)	obj->m_LinearVelocity += m_Gravity * m_UpdateTimestep;
	}

	//semi-implicit euler integration
	if (obj->update_con) {
		obj->m_LinearVelocity += obj->m_Force * obj->m_InvMass * m_UpdateTimestep;
		obj->m_LinearVelocity = obj->m_LinearVelocity * m_DampingFactor;
		obj->m_Position += obj->m_LinearVelocity * m_UpdateTimestep;
	}
	
	//Verlet Integration
	//{
	//	if (obj->verletPos.size() == 0) {
	//		obj->m_LinearVelocity += obj->m_Force * obj->m_InvMass;
	//		obj->m_LinearVelocity = obj->m_LinearVelocity * m_DampingFactor;
	//		obj->m_Position += obj->m_LinearVelocity * m_UpdateTimestep;

	//		obj->verletPos.push_back(obj->m_Position);
	//		obj->verletAcc.push_back(obj->m_Force * obj->m_InvMass);
	//	}
	//	else {
	//		obj->verletPos.push_back(obj->m_Position);
	//		obj->verletAcc.push_back(obj->m_Force * obj->m_InvMass);

	//		obj->m_Position = obj->m_Position + obj->m_Position
	//			- obj->verletPos[obj->verletPos.size() - 2]
	//			+ obj->verletAcc[obj->verletAcc.size() - 1]
	//			* m_UpdateTimestep * m_UpdateTimestep;
	//	}
	//}

	//angular rotation
	Vector3 angularAccel = obj->m_InvInertia * obj->m_Torque;
	obj->m_AngularVelocity = obj->m_AngularVelocity * m_DampingFactor;
	obj->m_Orientation = obj->m_Orientation + obj->m_Orientation *
		(obj->m_AngularVelocity * m_UpdateTimestep * 0.5f);
	obj->m_Orientation.Normalise();

	obj->m_wsTransformInvalidated = true;
}

void PhysicsEngine::BroadPhaseCollisions()
{
	m_BroadphaseCollisionPairs.clear();

	PhysicsObject *objA, *objB;

	m_Collision = false;

	//This is a brute force broadphase, basically compiling a list to check every object against every other object
	for (size_t i = 0; i < m_PhysicsObjects.size() - 1; ++i)
	{
		for (size_t j = i + 1; j < m_PhysicsObjects.size(); ++j)
		{
			objA = m_PhysicsObjects[i];
			objB = m_PhysicsObjects[j];
			if (objA->name.substr(0, 6) == "ground" && objB->name.substr(0, 6) == "ground"){
			}
			else{
				//Check they both have collision shapes
				if (objA->GetCollisionShape() != NULL
					&& objB->GetCollisionShape() != NULL)
				{
					//check if objA is a child of objB
					if (OctreeCheck(objB, objA)) {
						CollisionPair cp;
						cp.objectA = objA;
						cp.objectB = objB;
						m_BroadphaseCollisionPairs.push_back(cp);
					}
				}

			}
		}
	}
}

void PhysicsEngine::NarrowPhaseCollisions()
{
	if (m_BroadphaseCollisionPairs.size() > 0)
	{
		CollisionData coldata;
		CollisionShape *shapeA, *shapeB;


		for (CollisionPair& cp : m_BroadphaseCollisionPairs)
		{
			shapeA = cp.objectA->GetCollisionShape();
			shapeB = cp.objectB->GetCollisionShape();

			if (CollisionDetection::Instance()->CheckCollision(cp.objectA, cp.objectB, shapeA, shapeB, &coldata))
			{

			
					if (cp.objectA->IsEnabled()) { cp.objectA->ToggleEnable(); }
					if (cp.objectB->IsEnabled()) { cp.objectB->ToggleEnable(); }

					bool okA = cp.objectA->m_OnCollisionCallback(cp.objectB);
					bool okB = cp.objectB->m_OnCollisionCallback(cp.objectA);

					cp.objectA->verletVel.push_back(cp.objectA->GetLinearVelocity());
					cp.objectB->verletVel.push_back(cp.objectB->GetLinearVelocity());

					if (okA && okB)
					{
						if (cp.objectA->name.substr(0, 6) != "ground" && cp.objectB->name.substr(0, 6) != "ground") {


							//	cout << "Collision Between :" << cp.objectA->name.substr(0, 6) << endl;
							cp.collisionstate = true;
							CollidedPair.push_back(cp);


						}
						else {
							CollidedPair_Ground.push_back(cp);
						}

						Manifold* manifold = new Manifold(cp.objectA, cp.objectB);
						if (CollisionDetection::Instance()->BuildCollisionManifold(cp.objectA, cp.objectB, shapeA, shapeB, coldata, manifold))
						{
							m_Manifolds.push_back(manifold);
						}
						else
						{
							delete manifold;
						}
					}

					//traversable
					//Set opposite force which is proportional to respective body friction
					//to cancel incoming velocity of projectile
					//consume up all gravity when projectile is inside tardis
					else {
						if (cp.objectA->name == "TS" || cp.objectB->name == "TS") {
							if (okA) {
								Vector3 gravity = m_Gravity *
									(1 / cp.objectA->GetInverseMass());
								cp.objectA->SetForce(
									-cp.objectA->GetLinearVelocity()
									* cp.objectB->GetFriction() - gravity
									);
							}
							if (okB) {
								Vector3 gravity = m_Gravity *
									(1 / cp.objectB->GetInverseMass());
								cp.objectB->SetForce(
									-cp.objectB->GetLinearVelocity()
									* cp.objectA->GetFriction() - gravity);
							}
						}
					}
					//complete

				}
			}
		}
	}


void PhysicsEngine::SolveConstraints()
{
	for (Manifold* m : m_Manifolds) {
		m->PreSolverStep(m_UpdateTimestep);
	}

	for (Constraint* c : m_Constraints) {
		c->PreSolverStep(m_UpdateTimestep);
	}

	for (size_t i = 0; i < SOLVER_ITERATIONS; ++i) {
		for (Manifold* m : m_Manifolds) {
			m->ApplyImpulse();
		}
		
		for (Constraint* c : m_Constraints)
		{
			c->ApplyImpulse();
		}
	}
}


//build up the relation between the parent node and child node
//based upon their relative distance difference
void PhysicsEngine::OctreeBuild() {
	for (auto obj : m_PhysicsObjects) {
		OctreeStr* str = new OctreeStr;
		Octrees.push_back(str);
		str->parent = obj;

		for (auto sub : m_PhysicsObjects) {
			if (sub != obj) {
				//if the object is ground, then always deem it as a child for another object
				if (sub->name == "ground"){
						str->children.push_back(sub);
					}
				else{
					if ((sub->GetPosition() - obj->GetPosition()).Length() 
						< CollisionDetectionDis) {
						str->children.push_back(sub);
					}
				}
			}
		}
	}
}

//check if objB is a child of objA, if not then return false declining
//the narrowphase proceding
bool PhysicsEngine::OctreeCheck(PhysicsObject* objA, PhysicsObject* objB) {
	for (auto sub : Octrees) {
		if (sub->parent == objA) {
			for (auto child : sub->children) {
				if (child == objB) {
					return true;
				}
			}
			return false;
		}
	}
}