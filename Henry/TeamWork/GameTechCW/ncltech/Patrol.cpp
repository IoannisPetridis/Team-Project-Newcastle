#include "Patrol.h"

Patrol::Patrol(DefensiveAI* Arb) {
	{
		Vector3 PPVector;

		GroundHeight = 1.0f;

		FriendlyGoalPosition = Arb->scene->FindGameObject("FriendlyGoal")->Physics()->GetPosition();
		EnemyGoalPosition = Arb->scene->FindGameObject("EnemyGoal")->Physics()->GetPosition();
		PPVector = Arb->DirectionCalculation(EnemyGoalPosition, FriendlyGoalPosition);

		PatrolPoint = (FriendlyGoalPosition + (PPVector * 12.0) + Vector3(0.0f, 0.0f, 5.0f));
		PatrolPoint.y = GroundHeight;
		PatrolNode = PatrolPoint;
		iterator = 9;
	}
}

void Patrol::ForceCalculator(DefensiveAI* Arb) { //here is where you would put the logic behind the state
	Vector3 AIDistPatrolNode;
	float MagAINodeDist;

	++iterator;

	if (iterator == 10) {
		AIPosition = Arb->Physics()->GetPosition();
		BallPosition = Arb->scene->FindGameObject("ball")->Physics()->GetPosition() * Vector3(1.0f, 0.0f, 1.0f);

		PatrolNode = NodeCalculation(Arb);

		CheckTriggers(Arb); //check state triggers every frame to make sure the state does not need to be changed
		iterator = 0;
	}

	MagAINodeDist = (PatrolNode - AIPosition).Length();

	Arb->DirectionVector = Arb->DirectionCalculation(PatrolNode, AIPosition);
	Arb->RotationCalculation(PatrolNode);
	Arb->ForwardBackwardCalculation(MagAINodeDist);
}

void Patrol::CheckTriggers(DefensiveAI* Arb) {
	float MagDistBallGoal, MagGoalDists;

	MagDistBallGoal = (FriendlyGoalPosition - BallPosition).Length();
	MagGoalDists = (FriendlyGoalPosition - EnemyGoalPosition).Length() * 0.4f;

	if (MagDistBallGoal < MagGoalDists) {
		Arb->SetState(1);
	}
}

//Defend = 1
//Patrol = 2
//Punt = 3
//Off = 4

Vector3 Patrol::NodeCalculation(DefensiveAI* Arb) {
	Vector3 AIPatrolNodeVec;
	float MagAIPatrolNodeVec;

	AIPatrolNodeVec = PatrolNode - AIPosition; //Used for IF statement when it is decided if a new patrol node needs to be calculated
	MagAIPatrolNodeVec = AIPatrolNodeVec.LengthSquared();
	//cout << MagAIPatrolNodeVec << endl;

	if (MagAIPatrolNodeVec < 3) {
		int A, B;
		A = PatrolPoint.x + (rand() % 10 - 10);
		B = PatrolPoint.z + (rand() % 10 - 10);
		PatrolNode = Vector3(A, PatrolPoint.y, B);

		//cout << A << " " << B << endl;

		return PatrolNode;
	}

	else { //Not close to current node, set force on AI in direction of current node
		return PatrolNode;
	}
}
