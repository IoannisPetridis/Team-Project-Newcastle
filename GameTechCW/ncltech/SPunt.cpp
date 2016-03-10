#include "SPunt.h"
#include "AssetsManager.h"

SPunt::SPunt(SoloAI* Arb) {
	GroundHeight = 1.0f;
	iterator = 9;
	Arb->jump = false;
}
//called every frame, sets variables, calculates the node its trying to get to, and calls functions to move it there, also checks triggers to state change
void SPunt::ForceCalculator(SoloAI* Arb) {
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

		SetStateBool(Arb);

		iterator = 0;
	}

	MagAINodeDist = (PuntNode - AIPosition).Length();

	Arb->JumpCalculation(BallPosition);
	Arb->DirectionVector = Arb->DirectionCalculation(PuntNode, AIPosition);
	Arb->RotationCalculation(PuntNode);

	if (Arb->left == 0 && Arb->right == 0) {
		Arb->Charge();
	}

	if (Arb->statebool) {
		CheckTriggersScore(Arb);
	}

	else {
		CheckTriggersDefend(Arb);
	}
}

//if in defend higher state check defend triggers
void SPunt::CheckTriggersDefend(SoloAI* Arb) {
	float MagDistBallGoal, MagGoalDists;

	MagDistBallGoal = (FriendlyGoalPosition - BallPosition).Length();
	MagGoalDists = (FriendlyGoalPosition - EnemyGoalPosition).Length();

	if (MagDistBallGoal > (MagGoalDists * 0.3)) {
		Arb->SetState(4);
	}
}

//if in score higher state check triggers
void SPunt::CheckTriggersScore(SoloAI* Arb) {
	Arb->SetState(1);
}

//decides which higher state the ai should be in (defensive or trying to score)
void SPunt::SetStateBool(SoloAI* Arb) {
	Vector3 ballgoalvec, goalgoalvec;
	float ballgoallength, goalgoallength;

	ballgoalvec = BallPosition - FriendlyGoalPosition;
	ballgoallength = ballgoalvec.Length();

	goalgoalvec = EnemyGoalPosition - FriendlyGoalPosition;
	goalgoallength = goalgoalvec.Length();

	//cout << ballgoallength << " " << (goalgoallength) << endl;

	if (ballgoallength >= goalgoallength * 0.4 || AssetsManager::Player_1->GetInvisible()) {
		Arb->statebool = true;
	}

	if (ballgoallength < goalgoallength * 0.35 && !AssetsManager::Player_1->GetInvisible()) {
		Arb->statebool = false;
	}
}

//calculates the position of the node it is trying to get too
Vector3 SPunt::NodeCalculation(SoloAI* Arb) {
	Vector3 node, goalballdirvec;

	goalballdirvec = FriendlyGoalPosition - BallPosition;
	goalballdirvec.Normalise();

	node = BallPosition + (goalballdirvec * 3.0f);

	return node;
}

