#include "Chase.h"
#include <ncltech\Scene.h>

Chase::Chase(NeutralAI* Arb) {
	GroundHeight = 1.0f;
	iterator = 9;
	Arb->jump = false;
}

//called every frame, sets variables, calculates the node its trying to get to, and calls functions to move it there, also checks triggers to state change
void Chase::ForceCalculator(NeutralAI* Arb) { //here is where you would put the logic behind the state
	float MagAINodeDist;

	++iterator;
	//cout << "chase" << endl;
	if (iterator == 10) {
		BallPosition = Arb->scene->FindGameObject("ball")->Physics()->GetPosition();
		EnemyGoalPosition = Arb->scene->FindGameObject("EnemyGoal")->Physics()->GetPosition();
		FriendlyGoalPosition = Arb->scene->FindGameObject("FriendlyGoal")->Physics()->GetPosition();
		AIPosition = Arb->Physics()->GetPosition();

		ChaseNode = NodeCalculation(Arb);
		ChaseNode.y = GroundHeight;


		iterator = 0;
	}

	MagAINodeDist = (ChaseNode - AIPosition).Length();

	Arb->DirectionVector = Arb->DirectionCalculation(ChaseNode, AIPosition);
	Arb->RotationCalculation(ChaseNode);
	Arb->ForwardBackwardCalculation(MagAINodeDist);

	CheckTriggers(Arb);
}


//checks state change triggers
void Chase::CheckTriggers(NeutralAI* Arb) {
	Vector3 AINodeVec, AIGoalVec, BallGoalVec;
	float MagDistAINode, ailength, balllength;

	AIGoalVec = AIPosition - FriendlyGoalPosition;
	ailength = AIGoalVec.LengthSquared();
	BallGoalVec = BallPosition - FriendlyGoalPosition;
	balllength = BallGoalVec.LengthSquared();

	AINodeVec = ChaseNode - AIPosition;
	MagDistAINode = AINodeVec.LengthSquared();

	if (ailength >= balllength + 700) { //puts AI to off state on keypress (3 integer denotes off state)
		Arb->SetState(3);
		return;
	}

	if (MagDistAINode < 100) { //puts AI to off state on keypress (3 integer denotes off state)
		Arb->SetState(2);
	}
}

//Chase == 1
//Dribble == 2

//calculates the position of the node it is trying to get too
Vector3 Chase::NodeCalculation(NeutralAI* Arb) {
	Vector3 node, EnemyGoalBallVec;

	EnemyGoalBallVec = BallPosition - EnemyGoalPosition;
	EnemyGoalBallVec.Normalise();

	node = BallPosition + (EnemyGoalBallVec * 10);

	return node;
}
