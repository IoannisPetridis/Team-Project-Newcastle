#include "Patrol.h"

Patrol::Patrol(DefensiveAI* Arb) {
	{
		Vector3 PPVector;

		GroundHeight = 1.0f;

		FriendlyGoalPosition = Arb->scene->FindGameObject("FriendlyGoal")->Physics()->GetPosition();
		EnemyGoalPosition = Arb->scene->FindGameObject("EnemyGoal")->Physics()->GetPosition();
		PPVector = DirectionCalculation(Arb, EnemyGoalPosition, FriendlyGoalPosition);

		PatrolPoint = (FriendlyGoalPosition + (PPVector * 12.0) + Vector3(0.0f, 0.0f, 5.0f));
		PatrolPoint.y = GroundHeight;
		PatrolNode = PatrolPoint;
	}
}

void Patrol::ForceCalculator(DefensiveAI* Arb) { //here is where you would put the logic behind the state
	Vector3 DirectionVector, AIDistPatrolNode;
	float MagDistAIPatrolNode;

	Arb->SetColour(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	Arb->NormalCal();
	AIPosition = Arb->Physics()->GetPosition();
	BallPosition = Arb->scene->FindGameObject("ball")->Physics()->GetPosition() * Vector3(1.0f, 0.0f, 1.0f);

	PatrolNode = NodeCalculation(Arb);
	DirectionVector = DirectionCalculation(Arb, PatrolNode, AIPosition);

	Arb->Physics()->SetForce(DirectionVector * 20);

	CheckTriggers(Arb); //check state triggers every frame to make sure the state does not need to be changed
}

void Patrol::CheckTriggers(DefensiveAI* Arb) {
	float MagDistBallGoal;

	MagDistBallGoal = (FriendlyGoalPosition - BallPosition).LengthSquared();

	cout << MagDistBallGoal << endl;

	if (MagDistBallGoal < 1000) {
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

Vector3 Patrol::DirectionCalculation(DefensiveAI* Arb, Vector3 node1, Vector3 node2) {
	Vector3 directionvector;

	directionvector = node1 - node2;
	directionvector.Normalise();

	return directionvector;
}

void Patrol::ControlInputCalculation(DefensiveAI* Arb, Vector3 directionvector, Vector3 patrolnode) {
	float dotproduct, cosineangle;

	Arb->NormalCal();
	dotproduct = Vector3::Dot(directionvector, Arb->GetFrontNormal());
	cosineangle = dotproduct / (directionvector.Length());

	if (cosineangle > 0) {
		
	}

	if (cosineangle <= 0) {

	}

}