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

#include "NeutralAI.h"
#include "Chase.h"
#include "Dribble.h"
#include "Retreat.h"

NeutralAI::NeutralAI(const std::string& name, Scene* m_scene) : SimpleMeshObject(name) {

	SetMesh(AssetsManager::Cube(), false);
	SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	SetColour(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	SetBoundingRadius(80.0f * 80.f);
	Physics()->name = name.c_str();
	Physics()->SetInverseMass(0.06f);
	Physics()->SetPosition(Vector3(100.0f, 2.0f, 0.0f));
	Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));

	jumpiterator = 500;

	scene = m_scene;

	currentState = new Retreat(this); //sets the initial current state for the first frame (actually instantiates the state when the state is changed, so you dont have inactive states instantiated and sitting in memory doing nothing, ie rather than creating all states at startup and just changing the pointed, create and delkete states as they are used
}

NeutralAI::~NeutralAI() {

}

void NeutralAI::OnUpdateObject(float dt) {
	//Physics()->SetPause(false); 

	//currentState->ForceCalculator(this); //every frame call the ForceCalculator method of currentState 
}

//sets state for new behaviour
void NeutralAI::SetState(int setStateEnum) { //sets the state of the AI (when you call setstate you pass it an integer, and depending on which integer is passed a different state is chosen to be instantiated.
	delete currentState;

	if (setStateEnum == 1) {
		currentState = new Chase(this);
	}

	if (setStateEnum == 2) {
		currentState = new Dribble(this);
	}

	if (setStateEnum == 3) {
		currentState = new Retreat(this);
	}
}

//Chase == 1
//Dribble == 2

//called every frame, different state means different behavioural logic
void NeutralAI::UpdateAI() {
	currentState->ForceCalculator(this);
}

//calculates the direction from position "from" to position "to"
Vector3 NeutralAI::DirectionCalculation(Vector3 to, Vector3 from) {
	Vector3 directionvector;

	directionvector = to - from;
	directionvector.Normalise();

	return directionvector;
}


//calculates if the ai needs to rotate or not, and in which direction
void NeutralAI::RotationCalculation(Vector3 defendnode) {
	float dotproduct, angle;
	Vector3 crossproduct;

	int checkint;

	NormalCal();

	crossproduct = Vector3::Cross(DirectionVector, GetFrontNormal());

	if (crossproduct.y > 0) {
		right = true;
		left = false;
		++rightiterator;
		leftiterator = 0;
	}

	if (crossproduct.y <= 0) {
		right = false;
		left = true;
		++leftiterator;
		rightiterator = 0;
	}

	checkint = rightiterator - leftiterator;

	if (rightiterator == 1 || leftiterator == 1) {
		//cout << "true" << endl;
		right = false;
		left = false;
		return;
	}
}

//used for when the ai doesnt need to worry about max speed
void NeutralAI::Charge() {
	forward = 1;
	reverse = 0;
}



//used for when ai does need to worry about max speed to prevent overshooting, also accounts for sideways velocity to prevent orbiting
void NeutralAI::ForwardBackwardCalculation(float disttonode) {
	float currentforwardspeed, currentbackwardspeed, currentleftspeed, currentrightspeed;
	float maxspeed;

	//cout << disttonode << endl;

	maxspeed = disttonode * 1.3f;

	currentforwardspeed = Vector3::Dot(Physics()->GetLinearVelocity(), GetFrontNormal());
	currentbackwardspeed = Vector3::Dot(Physics()->GetLinearVelocity(), GetRearNormal());
	currentleftspeed = Vector3::Dot(Physics()->GetLinearVelocity(), GetLeftNormal());
	currentrightspeed = Vector3::Dot(Physics()->GetLinearVelocity(), GetRightNormal());

	if (currentleftspeed > (maxspeed * 0.7) || currentrightspeed > (maxspeed * 0.7)) {
		forward = 0;
		reverse = 0;
		return;
	}

	{
		if (currentforwardspeed <= 0.0f) {
			currentforwardspeed = 0;
		}

		if (currentbackwardspeed <= 0.0f) {
			currentbackwardspeed = 0;
		}
	}

	{
		if (currentforwardspeed <= maxspeed) {
			forward = 1;
			reverse = 0;
		}

		if (currentforwardspeed > maxspeed) {
			forward = 0;
			reverse = 1;
		}
	}
}


//Calculates if the ai needs to jump, coutns to 200 before can jump again 
void NeutralAI::JumpCalculation(Vector3 &ballposition) {
	float ballheight, groundheight, ballradius;

	groundheight = 1.0f;
	ballradius = 4.0f;

	ballheight = ballposition.y - groundheight - ballradius;

	//cout << ballheight << endl;

	if (ballheight > 1.5f) {
		//cout << jumpiterator << endl;

		if (jumpiterator > 100) {
			jump = true;
			jumpiterator = 0;
			return;
		}

		++jumpiterator;
		jump = false;
		return;
	}

	else jump = false;
}