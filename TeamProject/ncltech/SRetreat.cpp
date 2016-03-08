#include "SRetreat.h"
#include <ncltech\Scene.h>

SRetreat::SRetreat() {
	GroundHeight = 1.0f;
	iterator = 9;
}

void SRetreat::ForceCalculator(SoloAI* Arb) { //here is where you would put the logic behind the state
	float MagAINodeDist;

	++iterator;
	//cout << "retreat" << endl;
	if (iterator == 10) {
		BallPosition = Arb->scene->FindGameObject("ball")->Physics()->GetPosition();
		EnemyGoalPosition = Arb->scene->FindGameObject("EnemyGoal")->Physics()->GetPosition();
		FriendlyGoalPosition = Arb->scene->FindGameObject("FriendlyGoal")->Physics()->GetPosition();
		AIPosition = Arb->Physics()->GetPosition();

		RetreatNode = NodeCalculation(Arb);
		RetreatNode.y = GroundHeight;

		//cout << RetreatNode << endl;

		SetStateBool(Arb);

		iterator = 0;
	}

	MagAINodeDist = (RetreatNode - AIPosition).Length();

	Arb->DirectionVector = Arb->DirectionCalculation(RetreatNode, AIPosition);
	Arb->RotationCalculation(RetreatNode);
	Arb->ForwardBackwardCalculation(MagAINodeDist);

	//cout << Arb->statebool << endl;

	if (Arb->statebool) {
		CheckTriggersScore(Arb);
	}

	else {
		CheckTriggersDefend(Arb);
	}
}

void SRetreat::CheckTriggersScore(SoloAI* Arb) {
	Vector3 AIGoalVec, BallGoalVec;
	float ailength, balllength;

	AIGoalVec = AIPosition - FriendlyGoalPosition;
	ailength = AIGoalVec.LengthSquared();
	BallGoalVec = BallPosition - FriendlyGoalPosition;
	balllength = BallGoalVec.LengthSquared();

	//cout << ailength << " " << balllength << endl;

	if (ailength <= balllength) { //puts AI to off state on keypress (3 integer denotes off state)
		Arb->SetState(1);
	}
}


void SRetreat::CheckTriggersDefend(SoloAI* Arb) {
	Arb->SetState(4);
}

void SRetreat::SetStateBool(SoloAI* Arb) {
	Vector3 ballgoalvec, goalgoalvec;
	float ballgoallength, goalgoallength;

	ballgoalvec = BallPosition - FriendlyGoalPosition;
	ballgoallength = ballgoalvec.Length();

	goalgoalvec = EnemyGoalPosition - FriendlyGoalPosition;
	goalgoallength = goalgoalvec.Length();

	//cout << ballgoallength << " " << (goalgoallength ) << endl;

	if (ballgoallength >= goalgoallength * 0.4) {
		Arb->statebool = true;
	}

	if (ballgoallength < goalgoallength * 0.35) {
		Arb->statebool = false;
	}
}

//Chase == 1
//Dribble == 2

Vector3 SRetreat::NodeCalculation(SoloAI* Arb) {
	Vector3 node, ballgoalvec;
	float balllength;
	int randno;
	randno = rand() % 50 - 50;

	ballgoalvec = BallPosition - FriendlyGoalPosition;
	balllength = (ballgoalvec.Length()) * 0.5;

	node = FriendlyGoalPosition + Vector3(balllength, 0.0f, randno);

	return node;
}