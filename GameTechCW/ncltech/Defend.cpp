#include "Defend.h"
#include "Math.h"
#include "NCLDebug.h"

#define PI 3.14159265
#define E 2.71828

Defend::Defend() {
	GroundHeight = 1.0f;
	iterator = 9;
}

void Defend::ForceCalculator(DefensiveAI* Arb) { //here is where you would put the logic behind the state
	float MagAINodeDist;

	++iterator;

	if (iterator == 10) {

		//cout << "defend" << endl;

		AIPosition = Arb->Physics()->GetPosition();
		BallPosition = Arb->scene->FindGameObject("ball")->Physics()->GetPosition() * Vector3(1.0f, 0.0f, 1.0f);

		//
		FriendlyGoalPositionCalculation(Arb);

		//FriendlyGoalPosition = Arb->scene->FindGameObject("FriendlyGoal")->Physics()->GetPosition() + Vector3(0.0f, 0.0f, ballwidthmove);

		//cout << ballwidthmove << endl;

		FriendlyGoalPosition = Vector3(190.0f, 2.0f, 0.0f) + Vector3(0.0f, 0.0f, ballwidthmove);

		//

		Arb->scene->FindGameObject("FriendlyGoal")->Physics()->SetPosition(FriendlyGoalPosition);

		EnemyGoalPosition = Arb->scene->FindGameObject("EnemyGoal")->Physics()->GetPosition();

		DefendNode = NodeCalculation(Arb);
		DefendNode.y = GroundHeight;

		iterator = 0;
	}

	MagAINodeDist = (DefendNode - AIPosition).Length();

	Arb->DirectionVector = Arb->DirectionCalculation(DefendNode, AIPosition);
	Arb->RotationCalculation(DefendNode);
	Arb->ForwardBackwardCalculation(MagAINodeDist);

	//cout << "defend" << endl;
	CheckTriggers(Arb);
}

void Defend::CheckTriggers(DefensiveAI* Arb) {
	float MagDistBallGoal, MagGoalDists;

	MagDistBallGoal = (FriendlyGoalPosition - BallPosition).Length();
	MagGoalDists = (FriendlyGoalPosition - EnemyGoalPosition).Length();

	if (MagDistBallGoal > (MagGoalDists * 0.45)) {
		Arb->SetState(2);
	}

	if (MagDistBallGoal < (MagGoalDists * 0.15)) {
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

	GoalBallVec = BallPosition - FriendlyGoalPosition;
	DistGoalBall = GoalBallVec.Length();
	GoalBallVec.Normalise();

	defendnode = FriendlyGoalPosition + (GoalBallVec * DistGoalBall * 0.2);

	return defendnode;
}

void Defend::FriendlyGoalPositionCalculation(DefensiveAI* Arb) {
	float arenawidth, ballwidthposition, goalwidth, ballwidthpercentage;

	arenawidth = 200;
	goalwidth = 100;
	ballwidthposition = BallPosition.z;

	ballwidthpercentage = ballwidthposition / arenawidth;

	ballwidthmove = 150 * ballwidthpercentage;
}

