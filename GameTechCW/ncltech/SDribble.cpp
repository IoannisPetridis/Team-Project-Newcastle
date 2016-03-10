#include "SDribble.h"
#include <ncltech\Scene.h>
#include "AssetsManager.h"

SDribble::SDribble(SoloAI* Arb) {
	GroundHeight = 1.0f;
	iterator = 9;
	Arb->jump = false;
}
//called every frame, sets variables, calculates the node its trying to get to, and calls functions to move it there, also checks triggers to state change
void SDribble::ForceCalculator(SoloAI* Arb) { //here is where you would put the logic behind the state
	float MagAINodeDist;

	Arb->forward = 0;
	Arb->reverse = 0;

	++iterator;
	//cout << "dribble" << endl;
	if (iterator == 10) {
		BallPosition = Arb->scene->FindGameObject("ball")->Physics()->GetPosition();
		EnemyGoalPosition = Arb->scene->FindGameObject("EnemyGoal")->Physics()->GetPosition();
		FriendlyGoalPosition = Arb->scene->FindGameObject("FriendlyGoal")->Physics()->GetPosition();
		AIPosition = Arb->Physics()->GetPosition();

		DribbleNode = NodeCalculation(Arb);
		DribbleNode.y = GroundHeight;

		SetStateBool(Arb);

		iterator = 0;
	}

	MagAINodeDist = (DribbleNode - AIPosition).Length();

	Arb->JumpCalculation(BallPosition);
	Arb->DirectionVector = Arb->DirectionCalculation(DribbleNode, AIPosition);
	Arb->RotationCalculation(DribbleNode);

	//cout << Arb->left << Arb->right << endl;

	if (Arb->left == 0 && Arb->right == 0) {
		Arb->Charge();
	}

	//cout << Arb->statebool << endl;

	if (Arb->statebool) {
		CheckTriggersScore(Arb);
	}

	else {
		CheckTriggersDefend(Arb);
	}
}

//if in defend higher state check defend triggers
void SDribble::CheckTriggersScore(SoloAI* Arb) {
	Vector3 AINodeVec, AIGoalVec, BallGoalVec;
	float MagDistAINode, ailength, balllength;

	AIGoalVec = AIPosition - FriendlyGoalPosition;
	ailength = AIGoalVec.LengthSquared();
	BallGoalVec = BallPosition - FriendlyGoalPosition;
	balllength = BallGoalVec.LengthSquared();

	AINodeVec = DribbleNode - AIPosition;
	MagDistAINode = AINodeVec.LengthSquared();

	if (ailength >= balllength + 700) { //puts AI to off state on keypress (3 integer denotes off state)
		Arb->SetState(3);
		return;
	}

	if (MagDistAINode > 500) {
		Arb->SetState(1);
	}

}

//if in score higher state check triggers
void SDribble::CheckTriggersDefend(SoloAI* Arb) {
	Arb->SetState(4);
}

//decides which higher state the ai should be in (defensive or trying to score)
void SDribble::SetStateBool(SoloAI* Arb) {
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

	if (ballgoallength < goalgoallength * 0.35 && !AssetsManager::Player_1->GetInvisible()) {
		Arb->statebool = false;
	}
}

//Chase == 1
//Dribble == 2

//calculates the position of the node it is trying to get too
Vector3 SDribble::NodeCalculation(SoloAI* Arb) {
	Vector3 node, goalballdirvec;

	goalballdirvec = BallPosition - EnemyGoalPosition /*- BallPosition*/;
	goalballdirvec.Normalise();

	node = BallPosition + (goalballdirvec * 3.0f);

	return node;
}
