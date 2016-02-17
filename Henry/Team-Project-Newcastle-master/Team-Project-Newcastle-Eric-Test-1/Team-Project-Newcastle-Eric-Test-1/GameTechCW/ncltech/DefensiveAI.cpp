#pragma once 

#include <nclgl/OBJMesh.h>
#include <ncltech\SimpleMeshObject.h>
#include <ncltech\PhysicsEngine.h>
#include <ncltech\AssetsManager.h>
#include <ncltech\NCLDebug.h>
#include <ncltech\DistanceConstraint.h>
#include <ncltech\CuboidCollisionShape.h>
#include <ncltech\SphereCollisionShape.h>
//#include <ncltech\PyramidCollisionShape.h>
#include <ncltech\Scene.h>

#include "DefensiveAI.h"
#include "Defend.h"
#include "Patrol.h"
#include "Punt.h"
#include "OffState.h"

DefensiveAI::DefensiveAI(const std::string& name, Scene* m_scene) : SimpleMeshObject(name) {

	//camera = cameraInstance; //i kept in the camera pointer as i imagine most of our AI's will use camera position eventually 

	//Next lines create the physical and graphical representation of the object you want your AI to be (just like for any other GameObject

	/*SetMesh(AssetsManager::Sphere(), false);
	SetLocalTransform(Matrix4::Scale(Vector3(0.3f, 0.3f, 0.3f)));
	SetColour(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	SetBoundingRadius(1.0f);
	Physics()->SetInverseMass(1.0f);
	Physics()->SetForce(Vector3(0.0f, 9.81f, 0.0f));
	Physics()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	Physics()->SetCollisionShape(new SphereCollisionShape(0.3f));
	Physics()->SetInverseInertia(Physics()->GetCollisionShape()->BuildInverseInertia(1.0f));*/

	SetMesh(AssetsManager::Cube(), false);
	SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	SetColour(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	SetBoundingRadius(80.0f * 80.f);
	Physics()->name = name.c_str();
	Physics()->SetInverseMass(1.0f);
	Physics()->SetPosition(Vector3(5.0f, 0.0f, 10.0f));
	Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));

	//1 == home state, 2 == guard state

	scene = m_scene;

	currentState = new Defend(); //sets the initial current state for the first frame (actually instantiates the state when the state is changed, so you dont have inactive states instantiated and sitting in memory doing nothing, ie rather than creating all states at startup and just changing the pointed, create and delkete states as they are used

}

DefensiveAI::~DefensiveAI() {

}

void DefensiveAI::OnUpdateObject(float dt) {
	//Physics()->SetPause(false); 

	currentState->ForceCalculator(this); //every frame call the ForceCalculator method of currentState 
}

void DefensiveAI::SetState(int setStateEnum) { //sets the state of the AI (when you call setstate you pass it an integer, and depending on which integer is passed a different state is chosen to be instantiated.
	delete currentState;

	if (setStateEnum == 1) {
		currentState = new Defend();
	}

	if (setStateEnum == 2) {
		currentState = new Patrol(this);
	}

	if (setStateEnum == 3) {
		currentState = new Punt();
	}

	else if (setStateEnum == 4) {
		currentState = new OffState();
	}
}

