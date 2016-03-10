#include "Defend.h"
#include "Math.h"
#include "NCLDebug.h"

#define PI 3.14159265
#define E 2.71828

Defend::Defend(DefensiveAI* Arb) {
	GroundHeight = 1.0f;
	iterator = 9;
	Arb->jump = false;
}

//called every frame, sets variables, calculates the node its trying to get to, and calls functions to move it there, also checks triggers to state change
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



//checks state change triggers
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


//calculates the position of the node it is trying to get too
Vector3 Defend::NodeCalculation(DefensiveAI* Arb) {
	Vector3 GoalBallVec, defendnode;
	float DistGoalBall;

	GoalBallVec = BallPosition - FriendlyGoalPosition;
	DistGoalBall = GoalBallVec.Length();
	GoalBallVec.Normalise();

	defendnode = FriendlyGoalPosition + (GoalBallVec * DistGoalBall * 0.4);

	return defendnode;
}

//caluclates the position to defend, moves dynamically with ball so ai defends left side of goal if ball is near the left side
void Defend::FriendlyGoalPositionCalculation(DefensiveAI* Arb) {
	float arenawidth, ballwidthposition, goalwidth, ballwidthpercentage;

	arenawidth = 200;
	goalwidth = 100;
	ballwidthposition = BallPosition.z;

	ballwidthpercentage = ballwidthposition / arenawidth;

	ballwidthmove = 150 * ballwidthpercentage;
}

