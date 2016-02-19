#include "Defend.h"

Defend::Defend() {
	GroundHeight = 1.0f;
}

void Defend::ForceCalculator(DefensiveAI* Arb) { //here is where you would put the logic behind the state
	Vector3 DefendNode, DirectionVector;

	AIPosition = Arb->Physics()->GetPosition();
	BallPosition = Arb->scene->FindGameObject("ball")->Physics()->GetPosition() * Vector3(1.0f, 0.0f, 1.0f);
	GoalPosition = Arb->scene->FindGameObject("FriendlyGoal")->Physics()->GetPosition();

	DefendNode = NodeCalculation(Arb);
	DefendNode.y = GroundHeight;
	DirectionVector = DirectionCalculation(Arb, DefendNode);

	//ControlInputCalculation(Arb, DirectionVector, DefendNode);

	Arb->Physics()->SetForce(DirectionVector * 30);

	CheckTriggers(Arb); //check state triggers every frame to make sure the state does not need to be changed
}

void Defend::CheckTriggers(DefensiveAI* Arb) {
	float MagDistBallGoal;
	MagDistBallGoal = (GoalPosition - BallPosition).LengthSquared();

	if (MagDistBallGoal > 1050) {
		Arb->SetState(2);
	}

	if (MagDistBallGoal < 400) {
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

	defendnode = GoalPosition + (GoalBallVec * DistGoalBall * 0.2);

	return defendnode;
}

Vector3 Defend::DirectionCalculation(DefensiveAI* Arb, Vector3 node) {
	Vector3 directionvector;

	directionvector = node - AIPosition;
	directionvector.Normalise();

	return directionvector;
}

//void Defend::ControlInputCalculation(DefensiveAI* Arb, Vector3 directionvector, Vector3 defendnode) {
//	float dotproduct, cosineangle;
//
//	dotproduct = Vector3::Dot(directionvector, Arb->GetFrontNormal());
//	cosineangle = dotproduct / (directionvector.Length());
//}