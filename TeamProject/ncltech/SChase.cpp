#include "SChase.h"
#include <ncltech\Scene.h>

SChase::SChase() {
	GroundHeight = 1.0f;
	iterator = 9;
}

void SChase::ForceCalculator(SoloAI* Arb) { //here is where you would put the logic behind the state
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

		SetStateBool(Arb);

		iterator = 0;
	}

	MagAINodeDist = (ChaseNode - AIPosition).Length();

	Arb->DirectionVector = Arb->DirectionCalculation(ChaseNode, AIPosition);
	Arb->RotationCalculation(ChaseNode);
	Arb->ForwardBackwardCalculation(MagAINodeDist);

	//cout << Arb->statebool << endl;

	if (Arb->statebool) {
		CheckTriggersScore(Arb);
	}

	else {
		CheckTriggersDefend(Arb);
	}
}

void SChase::CheckTriggersScore(SoloAI* Arb) {
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

void SChase::CheckTriggersDefend(SoloAI* Arb) {
	Arb->SetState(4);
}

void SChase::SetStateBool(SoloAI* Arb) {
	Vector3 ballgoalvec, goalgoalvec;
	float ballgoallength, goalgoallength;

	ballgoalvec = BallPosition - FriendlyGoalPosition;
	ballgoallength = ballgoalvec.Length();

	goalgoalvec = EnemyGoalPosition - FriendlyGoalPosition;
	goalgoallength = goalgoalvec.Length();

	//cout << ballgoallength << " " << (goalgoallength) << endl;

	if (ballgoallength >= goalgoallength * 0.4) {
		Arb->statebool = true;
	}

	if (ballgoallength < goalgoallength * 0.35) {
		Arb->statebool = false;
	}
}

//Chase == 1
//Dribble == 2

Vector3 SChase::NodeCalculation(SoloAI* Arb) {
	Vector3 node, EnemyGoalBallVec;

	EnemyGoalBallVec = BallPosition - EnemyGoalPosition;
	EnemyGoalBallVec.Normalise();

	node = BallPosition + (EnemyGoalBallVec * 10);

	return node;
}