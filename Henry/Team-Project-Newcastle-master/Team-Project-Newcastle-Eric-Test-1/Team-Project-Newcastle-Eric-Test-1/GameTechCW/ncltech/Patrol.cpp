#include "Patrol.h"
#include <ncltech\Scene.h>

Patrol::Patrol(/*Scene* scene*/) {
	//m_scene = scene;

	PatrolNode = Vector3(5.0f, 0.0f, 5.0f); //Need an initial node point to move towards, will be the same point every time the state is triggered
	AIPosition = Vector3(0.0f, 0.0f, 0.0f);
}

void Patrol::ForceCalculator(DefensiveAI* Arb) { //here is where you would put the logic behind the state

	Vector3 PatrolPoint, BallPosition, GoalPosition, DirectionVector, AIDistPatrolNode;
	float MagDistAIPatrolNode;

	Arb->SetColour(Vector4(1.0f, 0.0f, 0.0f, 1.0f));

	BallPosition = Vector3(50.0f, 50.0f, 50.0f); //For temporary work, real location should be the position of the ball
	GoalPosition = Vector3(0.0f, 0.0f, 0.0f); //For temporary work, real location should be position of the goal
	PatrolPoint = GoalPosition + Vector3(5.0f, 0.0f, 5.0f);

	AIPosition = Arb->Physics()->GetPosition();

	AIDistPatrolNode = PatrolNode - AIPosition; //Used for IF statement when it is decided if a new patrol node needs to be calculated
	MagDistAIPatrolNode = AIDistPatrolNode.LengthSquared();

	if (MagDistAIPatrolNode < 3) { //Very close to current node, so must calculate new node randomly
		//Forsee problems with this if 0 gravity is in effect, no z change, means patrol pattern would be on ground despite 0g effect
		int A, B;
		A = rand() % 10 - 10;
		B = rand() % 10;
		PatrolNode = Vector3(A, 0.0f, B);

		DirectionVector = (PatrolNode - AIPosition);
		DirectionVector.Normalise();

		Arb->Physics()->SetForce(DirectionVector * 15);
	}

	else { //Not close to current node, set force on AI in direction of current node
		DirectionVector = (PatrolNode - AIPosition);
		DirectionVector.Normalise();

		Arb->Physics()->SetForce(DirectionVector * 15);
	}

	MagDistBallGoal = (GoalPosition - BallPosition).LengthSquared();
	CheckTriggers(Arb); //check state triggers every frame to make sure the state does not need to be changed
}

void Patrol::CheckTriggers(DefensiveAI* Arb) {
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_Q)) { //puts AI to off state on keypress (3 integer denotes off state)
		Arb->SetState(3);
	}       

	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_E)) { //puts AI to off state on keypress (3 integer denotes off state)
		Arb->SetState(1);
	}

	//this is a trigger i had in my coursework, just a distance threshold triggering state change
	//else if (tardisDistanceFromCameraMag >= 225) {
	//	newState = 1;//home state
	//	Arb->SetState(newState);
	//}
}