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

#include "AggressiveAI.h"
#include "Block.h"
#include "PuntPlayer.h"

AggressiveAI::AggressiveAI(const std::string& name, Scene* m_scene) : SimpleMeshObject(name) {

	//Next lines create the physical and graphical representation of the object you want your AI to be (just like for any other GameObject


	SetMesh(AssetsManager::Cube(), false);
	SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	SetColour(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	SetBoundingRadius(80.0f * 80.f);
	Physics()->name = name.c_str();
	Physics()->SetInverseMass(0.2f);
	Physics()->SetPosition(Vector3(30.0f, 5.0f, 60.0f));
	Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));

	scene = m_scene;

	currentState = new Block(); //sets the initial current state for the first frame (actually instantiates the state when the state is changed, so you dont have inactive states instantiated and sitting in memory doing nothing, ie rather than creating all states at startup and just changing the pointed, create and delkete states as they are used
}

AggressiveAI::~AggressiveAI() {

}

void AggressiveAI::OnUpdateObject(float dt) {
	//Physics()->SetPause(false); 

	//currentState->ForceCalculator(this); //every frame call the ForceCalculator method of currentState 
}

void AggressiveAI::SetState(int setStateEnum) { //sets the state of the AI (when you call setstate you pass it an integer, and depending on which integer is passed a different state is chosen to be instantiated.
	delete currentState;

	if (setStateEnum == 1) {
		currentState = new Block();
	}

	if (setStateEnum == 2) {
		currentState = new PuntPlayer(this);
	}
}

void AggressiveAI::UpdateAI() {
	currentState->ForceCalculator(this);
}