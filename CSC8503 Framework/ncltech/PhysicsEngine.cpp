#include "PhysicsEngine.h"
#include "GameObject.h"
#include "CollisionDetection.h"
#include <ncltech\OcTree.h>
#include <nclgl\Window.h>
#include <ncltech\NCLDebug.h>
#include <stdlib.h>
#include <iostream>
#include <mmsystem.h>
#include <windows.h>
#include <../Game Technologies/GameTechNew/MyScene.h>
//#include <../CSC8503 Framework/Game Technologies/Tutorial3 - Solver/MyScene.h>

bool PhysicsEngine::showCollision = false;
bool PhysicsEngine::showConstraints = false;
bool PhysicsEngine::showManifolds = false;
bool PhysicsEngine::showOctree = false;
bool PhysicsEngine::showWake = false;
PhysicsEngine::PhysicsEngine()
{
	m_IsPaused			= true;
	m_UpdateTimestep	= 1.0f / 60.f;
	m_UpdateAccum		= 0.0f;
	m_Gravity			=  Vector3(0.0f, -9.81f, 0.0f);
	m_DampingFactor		= 0.9999f;
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
	m_UpdateAccum += deltaTime;
	while (m_UpdateAccum >= m_UpdateTimestep)
	{
		m_UpdateAccum -= m_UpdateTimestep;
		if (!m_IsPaused) 
			UpdatePhysics();
	}
}


void PhysicsEngine::UpdatePhysics()
{
	for (Manifold* m : m_Manifolds)
	{
		delete m;
	}
	m_Manifolds.clear();

	//Check for collisions
	BroadPhaseCollisions();
	NarrowPhaseCollisions();

	//Solve collision constraints
	SolveConstraints();

	//Update movement
	UpdatePhysicsObjects();
}

void PhysicsEngine::DebugRender()
{
	if (showManifolds)
	{
		for (Manifold* m : m_Manifolds)
		{
			m->DebugDraw();
		}
	}


	if(showConstraints)
	{
		for (Constraint* c : m_Constraints)
		{
			c->DebugDraw();
		}
	}

	if (showCollision)
	{
		for (PhysicsObject* obj : m_PhysicsObjects)
		{
			if (obj->GetCollisionShape() != NULL)
			{
				obj->GetCollisionShape()->DebugDraw(obj);
			}
		}
	}
	
}


void PhysicsEngine::UpdatePhysicsObjects()
{
	for (PhysicsObject* obj : m_PhysicsObjects)
	{
		if (obj->GetIsWake())
		{
			if (showWake)
			{
				obj->GetParent()->SetColour(Vector4(0, 1, 0, 1));
			}
			else
			{
				obj->GetParent()->SetColour(obj->GetParent()->GetOldColour());
			}
			UpdatePhysicsObject(obj);
		}
		else
		{
			if (showWake)
			{
				obj->GetParent()->SetColour(Vector4(1, 1, 1, 1));
			}
			else
			{
				obj->GetParent()->SetColour(obj->GetParent()->GetOldColour());
			}
			
		}
	}
}

void PhysicsEngine::UpdatePhysicsObject(PhysicsObject* obj)
{
		

	
	/**
	TUTORIAL2 CODE - Integrating Physics Objects
	**/

	// Semi - Implicit Euler Intergration
	//using the future velocity


		obj -> m_LinearVelocity += (obj -> m_Force * obj -> m_InvMass) * m_UpdateTimestep;
		//              V n+1    =                        a                 deta t

		if (obj -> m_InvMass > 0.00001f)
		obj -> m_LinearVelocity += m_Gravity * m_UpdateTimestep;
	
		// Technically this is ( m_Gravity / invMass ) * invMass * dt ,
		// hence the check for invMass being zero is still required even
		// though invMass cancels itself out in the gravity equation .
		//m_DampingFactor is air resitant the lower it is the lower the tenal velocity

		

		obj->m_LinearVelocity = obj->m_LinearVelocity * m_DampingFactor;


		//position normal way
		 obj->m_Position += obj->m_LinearVelocity * m_UpdateTimestep;
//nextPosition = Thisposition +         NextVelocity * dt

		////Verlet
		//Vector3 oldPos = obj->m_LastPosition;
		//obj->m_LastPosition = obj->m_Position;
		//obj->m_Position += obj->m_Position - oldPos +(obj->m_Force * obj->m_InvMass)* m_UpdateTimestep * m_UpdateTimestep;
	
		

		//// Explicit Euler Intergration
		////using the old velocity
		//obj->m_LinearVelocity += (obj->m_Force * obj->m_InvMass) * m_UpdateTimestep;
		////              V n+1    =                        a                 deta t

	
	// Angular Rotation
		
		Vector3 angluarAccel = obj -> m_InvInertia * obj -> m_Torque;
		obj -> m_AngularVelocity = obj -> m_AngularVelocity + angluarAccel* m_UpdateTimestep;
	
		obj -> m_AngularVelocity = obj -> m_AngularVelocity * m_DampingFactor;
	
		obj -> m_Orientation = obj -> m_Orientation + obj -> m_Orientation *(obj -> m_AngularVelocity * m_UpdateTimestep *0.5f);
	
		// Quaternion equiv of the above position calculation
		
		obj -> m_Orientation.Normalise();
	
		obj -> m_wsTransformInvalidated = true;
		// inform the physics object that it ’s world space transform
		// is invalid


		//set the object to sleep
		float curVel = obj->m_LinearVelocity.LengthSquared() + obj->m_AngularVelocity.LengthSquared();	
		float diff = curVel - obj->oldVel;
		
		
		Vector3 diffPositionObj = obj->GetPosition() - obj->oldPos;
		
		float maxPos = max(abs(diffPositionObj.x), abs(diffPositionObj.y), abs(diffPositionObj.z));

		if (diff < 0.0001f && curVel < 0.0001f && maxPos < 0.00001f)
		{
			obj->SetIsWake(false);

			if (showWake)
			{
				//obj->m_Parent->SetOldColour(obj->m_Parent->GetColour());
				obj->m_Parent->SetColour(Vector4(1.f, 1.f, 1.0f, 1));
			}
			else
			{
				obj->GetParent()->SetColour(obj->GetParent()->GetOldColour());
			}
		}

		obj->oldVel = curVel;
		obj->oldPos = obj->GetPosition();
}





void PhysicsEngine::BroadPhaseCollisions()
{
	m_BroadphaseCollisionPairs.clear();

	/*PhysicsObject *objA, *objB;
	PhysicsObject** tempPhysicsObjects;
	tempPhysicsObjects = new PhysicsObject*[m_PhysicsObjects.size()];
	int tempPhysicCount = 0;

	PhysicsObject** globalPhysicsObjects;
	globalPhysicsObjects = new PhysicsObject*[10];
	int globalPhysicsCount = 0;

	for (int i = 0; i < m_PhysicsObjects.size();i++)
	{
		if (m_PhysicsObjects[i]->GetCollisionShape() != NULL)
		{
				if (m_PhysicsObjects[i]->GetIsGlobal())
					globalPhysicsObjects[globalPhysicsCount++] = m_PhysicsObjects[i];
				else
					tempPhysicsObjects[tempPhysicCount++] = m_PhysicsObjects[i];
		}
	}*/

	//******    ****    ****  ****
	//	*       *  *    *     *
	//  *       ****    ****  ****
	//  *       *  *	*     *
	//  *       *   *   ****  ****

	//add the  ocTree
	OcTree* Tree = new OcTree();
	vector<PhysicsObject*> physicObjectList;
	vector<PhysicsObject*> referenceObjectList;

	for (int i = 0; i < m_PhysicsObjects.size(); i++)
	{
		//check if it has collision shape or not if true put it in the list
		if (m_PhysicsObjects[i]->GetCollisionShape() != NULL)
		{
			physicObjectList.push_back(m_PhysicsObjects[i]);
		}

		//find AI
		//string xxx = ;
		//bool check = ;
		if (m_PhysicsObjects[i]->GetParent()->GetName().compare("AI") == false)
		{
			AI = m_PhysicsObjects[i]->GetParent();
		}
	}
	//build tree
	Tree->build(physicObjectList, referenceObjectList, 10, 6, Vector3(0, 0, 0), 100, 0);
	//create collisionPair from  tree
	Tree->getCollisionPair(m_BroadphaseCollisionPairs);

		if (showOctree)
		{
			OcTree::showOctree = true;
			Tree->DebugDraw();
		}
		else
		{
			OcTree::showOctree = false;
		}
		//Tree->checkOverlapUpdate(Tree);

	//putPairInBroad(Tree, &m_BroadphaseCollisionPairs);
	

		 
	/*for (size_t i = 0; i < globalPhysicsCount; ++i)
	{
		for (size_t j = 0; j < tempPhysicCount; ++j)
		{
			objA = globalPhysicsObjects[i];
			objB = tempPhysicsObjects[j];

				CollisionPair cp;
				cp.objectA = objA;
				cp.objectB = objB;
				m_BroadphaseCollisionPairs.push_back(cp);
		}
	}*/


	//This is a brute force broadphase, basically compiling a list to check every object against every other object
	//for (size_t i = 0; i < m_PhysicsObjects.size() - 1; ++i)
	//{
	//	for (size_t j = i + 1; j < m_PhysicsObjects.size(); ++j)
	//	{
	//		PhysicsObject* objA = m_PhysicsObjects[i];
	//		PhysicsObject* objB = m_PhysicsObjects[j];

	//		//Check they both have collision shapes
	//		if (objA->GetCollisionShape() != NULL && objB->GetCollisionShape() != NULL)
	//		{
	//			CollisionPair cp;
	//			cp.objectA = objA;
	//			cp.objectB = objB;
	//			m_BroadphaseCollisionPairs.push_back(cp);
	//		}
	//	}
	//}


	//check the wall and floor
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

			if (CollisionDetection::Instance()->CheckCollision(cp.objectA, cp.objectB, shapeA, shapeB, &coldata))//if it collision
			{
				//cout << cp.objectA->GetPosition();
				//cout << cp.objectB->GetPosition();
				//SetPaused(true);
				
				bool okA = cp.objectA->m_OnCollisionCallback(cp.objectB);
				bool okB = cp.objectB->m_OnCollisionCallback(cp.objectA);
				
				if ((cp.objectA->GetIsAI() && !cp.objectB->GetIsTardis() && !cp.objectB->GetIsProtectedBall()) || (cp.objectB->GetIsAI() && !cp.objectA->GetIsTardis() && !cp.objectA->GetIsProtectedBall()))
				{
					PlaySound(TEXT("sound/block.wav"), NULL, SND_ASYNC);
				}

				if ((cp.objectA->GetIsAI() && cp.objectB->GetIsTardis()) || (cp.objectA->GetIsAI() && cp.objectB->GetIsTardis()) || (cp.objectA->GetIsTardis() && cp.objectB->GetIsTardis())||
					(cp.objectA->GetIsProtectedBall() || cp.objectB->GetIsProtectedBall() ))
				{
					if (cp.objectA->GetIsProtectedBall() && !cp.objectB->GetIsAI() && !cp.objectB->GetIsTardis() && !cp.objectA->GetIsGlobal()) //objA is protected sphere
					{
						//Vector3 destination = Vector3(0, 50, 0);
						//GameObject* temp = cp.objectA->GetParent()->FindGameObject("AI");
						//cp.objectA->GetParent()->move(temp, destination);
						Vector3 des = cp.objectA->GetPosition() + coldata.normal * 8.0f;
						NCLDebug::DrawPoint(des, 0.2f, Vector4(0.0f,0.0f,1.0f,1.0f));

						
						float distance = (cp.objectA->GetPosition() - cp.objectB->GetPosition()).Length();

						if ((cp.objectA->GetPosition() - cp.objectB->GetPosition()).Length() > 7.5f && !cp.objectB->GetIsAlreadyHitProtect())
						{
							cp.objectB->SetIsAlreadyHitProtect(true);
							MyScene::move(AI, des);
						}
						//okA = false;
						//okB = false;
					}
					else if (cp.objectB->GetIsProtectedBall() && !cp.objectA->GetIsAI() && !cp.objectA->GetIsTardis() && !cp.objectA->GetIsGlobal())//objB is protected sphere
					{

						Vector3 des = cp.objectB->GetPosition() + coldata.normal * 8.0f;
						NCLDebug::DrawPoint(des, 0.2f, Vector4(0.0f, 0.0f, 1.0f, 1.0f));


						if ((cp.objectB->GetPosition() - cp.objectA->GetPosition()).Length() > 7.5f && !cp.objectA->GetIsAlreadyHitProtect())
						{
							cp.objectA->SetIsAlreadyHitProtect(true);
							MyScene::move(AI, des);
						}
					
						//okA = false;
						//okB = false;
						
						//cp.objectB->GetParent()->move(cp.objectB->GetParent()->FindGameObject("AI"), destination);
					}
					
					okA = false;
					okB = false;
				}
				else
				{
					if (cp.objectA->GetIsTardis() && !cp.objectB->GetIsTardis() ) // A is tardis
					{
					
						if (cp.objectA->GetFade() >= 1 && cp.objectB->GetIsAlreadyHit()) // hit when it fully show
						{
							scoreCount+=1000;
							cout << "HIT " << scoreCount << endl;
							PlaySound(TEXT("sound/Perfect.wav"), NULL, SND_ASYNC);
						}
						else
						{
							if ((cp.objectA->GetFade() < 1.0f) && cp.objectB->GetIsAlreadyHit())
							{
								if (cp.objectA->GetFade() > 0.0f)
								{
								scoreCount += 1000 * cp.objectA->GetFade();
								cp.objectB->SetLinearVelocity(cp.objectB->GetLinearVelocity() - (cp.objectB->GetLinearVelocity()*(cp.objectA->GetFade())));
								}
							}

							okB = false;
						}
						cp.objectB->SetIsAlreadyHit(false);
					}

					if (!cp.objectA->GetIsTardis() && cp.objectB->GetIsTardis())// B is tardis
					{
						cp.objectA->SetIsAlreadyHit(false);
						if (cp.objectB->GetFade() >= 1 && cp.objectA->GetIsAlreadyHit()) // hit when it fully show
						{
							scoreCount +=1000;
							cout << "HIT " << scoreCount << endl;
							PlaySound(TEXT("sound/Perfect.wav"), NULL, SND_ASYNC);
						}
						else
						{
							if ((cp.objectB->GetFade() <1.0f) && cp.objectA->GetIsAlreadyHit())
							{
								if (cp.objectB->GetFade() > 0.0f)
								{
								scoreCount += 1000 * cp.objectB->GetFade();
								cp.objectA->SetLinearVelocity(cp.objectA->GetLinearVelocity() - (cp.objectA->GetLinearVelocity()*cp.objectB->GetFade()));
								}
							}
							okA = false;
						}
						cp.objectA->SetIsAlreadyHit(false);
					}
				}
				

				/*if ((cp.objectA->GetIsTardis() && cp.objectB->GetIsTardis()))
				{
					okA = false;
					okB = false;
				}*/

				if (okA && okB)
				{
					/*Vector3 oldAVelocity = cp.objectA->m_LinearVelocity;
					Vector3 oldAVelcoty = cp.objectA->m_AngularVelocity;

					Vector3 velChange = cp.objectA->m_LinearVelocity - oldAVelocity;
					Vector3 velAChange = cp.objectA->m_AngularVelocity - oldAVelcoty;

					Vector3 oldBVelocity = cp.objectB->m_LinearVelocity;
					Vector3 oldBVelcoty = cp.objectB->m_AngularVelocity;

					Vector3 velChange1 = cp.objectB->m_LinearVelocity - oldBVelocity;
					Vector3 velBChange = cp.objectB->m_AngularVelocity - oldAVelcoty;*/
					if((!cp.objectA->GetLinearVelocity().LengthSquared() < 0.001f && !cp.objectA->GetAngularVelocity().LengthSquared() < 0.001f) || (!cp.objectB->GetLinearVelocity().LengthSquared() < 0.001f && !cp.objectB->GetAngularVelocity().LengthSquared() < 0.001f))
						//&& velChange.LengthSquared() < 0.001f && velAChange.LengthSquared() < 0.001f)
						//&& velChange1.LengthSquared() < 0.001f && velBChange.LengthSquared() < 0.001f)
					{
						if (!cp.objectA->GetIsGlobal())
						cp.objectA->SetIsWake(true);
						//cp.objectA->m_Parent->SetColour(Vector4(0,1,0,1));
					
						if (!cp.objectB->GetIsGlobal())
						cp.objectB->SetIsWake(true);
						//cp.objectB->m_Parent->SetColour(Vector4(0, 1, 0, 1));

					}

					//If both objects are colliding, and both callbacks allow for default collision resolution we will build a full collision manifold
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
			
			}
		}
	}
}

//void PhysicsEngine::moveAI(GameObject* obj, Vector3 des)
//{
//	obj->start = obj->Physics()->GetPosition();
//	obj->end = des;
//	obj->distance = (des - obj->start).Length();
//	obj->direction = des - obj->start;
//	obj->direction.Normalise();
//	obj->isMove = true;
//
//}

void PhysicsEngine::SolveConstraints()
{
	/*
	TUTORIAL 4 CODE - Distance Constraints
	TUTORIAL 9 CODE - Resolving Collision Manifolds
	*/

	/*for (Constraint * c : m_Constraints)
	{
		c -> PreSolverStep(m_UpdateTimestep);
	}
	
	for (size_t i = 0; i < SOLVER_ITERATIONS; ++i)
	{
		for (Constraint * c : m_Constraints)
		{
			c -> ApplyImpulse();
		}
	}*/

	for (Manifold * m : m_Manifolds)
	{
		m -> PreSolverStep(m_UpdateTimestep);
	}
	
	for (Constraint * c : m_Constraints)
	{
		if (c->objA->GetIsWake() || c->objB->GetIsWake())
		{
			c->objA->SetIsWake(true);
			c->objB->SetIsWake(true);
			c->PreSolverStep(m_UpdateTimestep);
		}
		
	}
	
	for (size_t i = 0; i < SOLVER_ITERATIONS; ++i)
	{
		for (Manifold * m : m_Manifolds)
		{
			m -> ApplyImpulse();
		}
		
		for (Constraint * c : m_Constraints)
		{
			if (c->objA->GetIsWake()) //Don't need to check both as the above check will set 'both' to awake if atleast one of them was awake.
			{
				c->ApplyImpulse();
			}
		}
	}

}