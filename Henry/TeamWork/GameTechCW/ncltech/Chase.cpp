#include "Chase.h"
#include <ncltech\Scene.h>

Chase::Chase() {
	GroundHeight = 1.0f;
}

void Chase::ForceCalculator(NeutralAI* Arb) { //here is where you would put the logic behind the state
	float MagAINodeDist;

	BallPosition = Arb->scene->FindGameObject("ball")->Physics()->GetPosition();
	EnemyGoalPosition = Arb->scene->FindGameObject("EnemyGoal")->Physics()->GetPosition();
	FriendlyGoalPosition = Arb->scene->FindGameObject("FriendlyGoal")->Physics()->GetPosition();
	AIPosition = Arb->Physics()->GetPosition();

	ChaseNode = NodeCalculation(Arb);
	ChaseNode.y = GroundHeight;

	MagAINodeDist = (ChaseNode - AIPosition).Length();

	Arb->DirectionVector = Arb->DirectionCalculation(ChaseNode, AIPosition);
	Arb->RotationCalculation(ChaseNode);
	Arb->ForwardBackwardCalculation(MagAINodeDist);

	CheckTriggers(Arb);
}

void Chase::CheckTriggers(NeutralAI* Arb) {
	Vector3 AINodeVec;
	float MagDistAINode;

	AINodeVec = ChaseNode - AIPosition;
	MagDistAINode = AINodeVec.LengthSquared();

	if (MagDistAINode < 100) { //puts AI to off state on keypress (3 integer denotes off state)
		Arb->SetState(2);
	}
}

//Chase == 1
//Dribble == 2

Vector3 Chase::NodeCalculation(NeutralAI* Arb) {
	Vector3 node, EnemyGoalBallVec;

	EnemyGoalBallVec = BallPosition - EnemyGoalPosition;
	EnemyGoalBallVec.Normalise();

	node = BallPosition + (EnemyGoalBallVec * 10);

	return node;
}

Vector3 Chase::DirectionCalculation(NeutralAI* Arb, Vector3 node) {
	Vector3 directionvector;

	directionvector = node - AIPosition;
	directionvector.Normalise();

	return directionvector;
}