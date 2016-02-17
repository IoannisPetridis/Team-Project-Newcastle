#include "Defend.h"
#include <ncltech\Scene.h>

void Defend::ForceCalculator(DefensiveAI* Arb) { //here is where you would put the logic behind the state
	Vector3 DefendNode, DirectionVector;
	float DistGoalBall;

	Arb->SetColour(Vector4(0.0f, 1.0f, 0.0f, 1.0f));

	AIPosition = Arb->Physics()->GetPosition();
	BallPosition = Arb->scene->FindGameObject("Ball")->Physics()->GetPosition();
	GoalPosition = Arb->scene->FindGameObject("FriendlyGoal")->Physics()->GetPosition();

	DefendNode = NodeCalculation(Arb);
	DirectionVector = DirectionCalculation(Arb, DefendNode);

	Arb->Physics()->SetForce(DirectionVector * 5);
	
	CheckTriggers(Arb); //check state triggers every frame to make sure the state does not need to be changed
}

void Defend::CheckTriggers(DefensiveAI* Arb) {
	float MagDistBallGoal;
	MagDistBallGoal = (GoalPosition - BallPosition).LengthSquared();

	if (MagDistBallGoal > 750) {//if turned off returns to home state, which will then trigger guard state instantly if appropriate
		Arb->SetState(2);
	}

	if (MagDistBallGoal < 200) {
		Arb->SetState(3);
	}
}

//Defend = 1
//Patrol = 2
//Punt = 3
//Off = 4

Vector3 Defend::NodeCalculation(DefensiveAI* Arb) {
	Vector3 GoalBallVec, defendnode;
	float DistGoalBall;

	GoalBallVec = BallPosition - GoalPosition;
	DistGoalBall = GoalBallVec.Length();
	GoalBallVec.Normalise();

	defendnode = GoalBallVec * DistGoalBall * 0.2;

	return defendnode;
}

Vector3 Defend::DirectionCalculation(DefensiveAI* Arb, Vector3 node) {
	Vector3 directionvector;
	directionvector = node - AIPosition;
	directionvector.Normalise();

	return directionvector;
}