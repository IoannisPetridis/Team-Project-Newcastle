#pragma once 

#include <nclgl/OBJMesh.h>
#include <ncltech\SimpleMeshObject.h>
#include <ncltech\PhysicsEngine.h>
#include <ncltech\AssetsManager.h>
#include <ncltech\NCLDebug.h>
#include <ncltech\DistanceConstraint.h>
#include <ncltech\CuboidCollisionShape.h>
#include <ncltech\SphereCollisionShape.h>
#include <ncltech\Scene.h>

#include "DefensiveAI.h"
#include "Defend.h"
#include "Patrol.h"
#include "Punt.h"

DefensiveAI::DefensiveAI(const std::string& name, Scene* m_scene) : SimpleMeshObject(name) {

	SetMesh(AssetsManager::Cube(), false);
	SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	SetColour(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	SetBoundingRadius(80.0f * 80.f);
	Physics()->name = name.c_str();
	Physics()->SetInverseMass(0.06f);
	Physics()->SetPosition(Vector3(180.0f, 2.0f, 0.0f));
	Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));

	scene = m_scene;

	currentState = new Patrol(this);

	left = false;
	right = false;
	reverse = false;
	forward = false;
	jump = false;
}

DefensiveAI::~DefensiveAI() {

}

void DefensiveAI::OnUpdateObject(float dt) {
}

//sets state for new behaviour
void DefensiveAI::SetState(int setStateEnum) {
	delete currentState;

	if (setStateEnum == 1) {
		currentState = new Defend(this);
	}

	if (setStateEnum == 2) {
		currentState = new Patrol(this);
	}

	if (setStateEnum == 3) {
		currentState = new Punt(this);
	}
}


//called every frame, different state means different behavioural logic
void DefensiveAI::UpdateAI() {
	currentState->ForceCalculator(this);
}

//calculates the direction from position "from" to position "to"
Vector3 DefensiveAI::DirectionCalculation(Vector3 to, Vector3 from) {
	Vector3 directionvector;

	directionvector = to - from;
	directionvector.Normalise();

	return directionvector;
}

//calculates if the ai needs to rotate or not, and in which direction
void DefensiveAI::RotationCalculation(Vector3 defendnode) {
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
void DefensiveAI::Charge() {
	forward = 1;
	reverse = 0;
}

//used for when ai does need to worry about max speed to prevent overshooting, also accounts for sideways velocity to prevent orbiting
void DefensiveAI::ForwardBackwardCalculation(float disttonode) {
	float currentforwardspeed, currentbackwardspeed, currentleftspeed, currentrightspeed;
	float maxspeed;

	//cout << disttonode << endl;

	maxspeed = disttonode * 1.3f;

	currentforwardspeed = Vector3::Dot(Physics()->GetLinearVelocity(), GetFrontNormal());
	currentbackwardspeed = Vector3::Dot(Physics()->GetLinearVelocity(), GetRearNormal());
	currentleftspeed = Vector3::Dot(Physics()->GetLinearVelocity(), GetLeftNormal());
	currentrightspeed = Vector3::Dot(Physics()->GetLinearVelocity(), GetRightNormal());

	if (currentleftspeed > (maxspeed * 0.5) || currentrightspeed > (maxspeed * 0.5)) {
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
void DefensiveAI::JumpCalculation(Vector3 &ballposition){
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