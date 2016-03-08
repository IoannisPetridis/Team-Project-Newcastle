#include "Punt.h"

Punt::Punt() {
	GroundHeight = 1.0f;
	iterator = 9;
}

void Punt::ForceCalculator(DefensiveAI* Arb) {
	float MagAINodeDist;

	++iterator;

	Arb->forward = 0;
	Arb->reverse = 0;

	if (iterator == 10) {

		//cout << "punt" << endl;

		AIPosition = Arb->Physics()->GetPosition();
		FriendlyGoalPosition = Arb->scene->FindGameObject("FriendlyGoal")->Physics()->GetPosition();
		EnemyGoalPosition = Arb->scene->FindGameObject("EnemyGoal")->Physics()->GetPosition();
		BallPosition = Arb->scene->FindGameObject("ball")->Physics()->GetPosition();
		AIBallVec = BallPosition - AIPosition;
		MagAIBallDist = AIBallVec.Length();
		AIBallVec.Normalise();

		PuntNode = NodeCalculation(Arb);
		PuntNode.y = GroundHeight;

		iterator = 0;
	}

	MagAINodeDist = (PuntNode - AIPosition).Length();

	Arb->JumpCalculation(BallPosition);
	Arb->DirectionVector = Arb->DirectionCalculation(PuntNode, AIPosition);
	Arb->RotationCalculation(PuntNode);

	if (Arb->left == 0 && Arb->right == 0) {
		Arb->Charge();
	}

	//Arb->ForwardBackwardCalculation(MagAINodeDist);

	CheckTriggers(Arb);
}

void Punt::CheckTriggers(DefensiveAI* Arb) {
	float MagDistBallGoal, MagGoalDists;

	MagDistBallGoal = (FriendlyGoalPosition - BallPosition).Length();
	MagGoalDists = (FriendlyGoalPosition - EnemyGoalPosition).Length();

	if (MagDistBallGoal > (MagGoalDists * 0.2)) {
		Arb->SetState(1);
	}
}

//Defend = 1
//Patrol = 2
//Punt = 3
//Off = 4

Vector3 Punt::NodeCalculation(DefensiveAI* Arb) {
	Vector3 node, goalballdirvec;

	goalballdirvec = FriendlyGoalPosition - BallPosition;
	goalballdirvec.Normalise();

	node = BallPosition + (goalballdirvec * 3.0f);

	return node;
}

//Vector3 Punt::DirectionCalculation(DefensiveAI* Arb, Vector3 node) {
//	Vector3 directionvector, AIPosition;
//
//	AIPosition = Arb->Physics()->GetPosition();
//
//	directionvector = node - AIPosition;
//	directionvector.Normalise();
//
//	return directionvector;
//}
