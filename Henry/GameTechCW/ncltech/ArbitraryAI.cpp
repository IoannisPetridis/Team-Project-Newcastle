#include <nclgl/OBJMesh.h>
#include <ncltech\SimpleMeshObject.h>
#include <ncltech\PhysicsEngine.h>
#include <ncltech\AssetsManager.h>
#include <ncltech\NCLDebug.h>
#include <ncltech\DistanceConstraint.h>
#include <ncltech\CuboidCollisionShape.h>
#include <ncltech\SphereCollisionShape.h>
#include <ncltech\Scene.h>

#include "ArbitraryAI.h"
#include "HomeState.h"
#include "GuardState.h"
#include "OffState.h"

ArbitraryAI::ArbitraryAI(const std::string& name, Camera* cameraInstance, const int& radius) : SimpleMeshObject(name) {

	camera = cameraInstance; //i kept in the camera pointer as i imagine most of our AI's will use camera position eventually 

	//Next lines create the physical and graphical representation of the object you want your AI to be (just like for any other GameObject

	SetMesh(AssetsManager::Sphere(), false);
	SetLocalTransform(Matrix4::Scale(Vector3(0.3f, 0.3f, 0.3f)));
	SetColour(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	SetBoundingRadius(1.0f);
	Physics()->SetInverseMass(1.0f);
	Physics()->SetForce(Vector3(0.0f, 9.81f, 0.0f));
	Physics()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	Physics()->SetCollisionShape(new SphereCollisionShape(0.3f));
	Physics()->SetInverseInertia(Physics()->GetCollisionShape()->BuildInverseInertia(1.0f));

	//1 == home state, 2 == guard state

	currentState = new OffState(); //sets the initial current state for the first frame (actually instantiates the state when the state is changed, so you dont have inactive states instantiated and sitting in memory doing nothing, ie rather than creating all states at startup and just changing the pointed, create and delkete states as they are used
}

ArbitraryAI::~ArbitraryAI() {

}

void ArbitraryAI::OnUpdateObject(float dt) {
	//Physics()->SetPause(false); 

	currentState->ForceCalculator(this); //every frame call the ForceCalculator method of currentState 
}

void ArbitraryAI::SetState(int setStateEnum) { //sets the state of the AI (when you call setstate you pass it an integer, and depending on which integer is passed a different state is chosen to be instantiated.
	delete currentState;

	if (setStateEnum == 1) {
		currentState = new HomeState();
	}

	if (setStateEnum == 2) {
		currentState = new GuardState();
	}

	else if (setStateEnum == 3) {
		currentState = new OffState();
	}
}