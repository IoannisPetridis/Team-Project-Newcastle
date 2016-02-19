#include "Punt.h"

Punt::Punt() {
	GroundHeight = 1.0f;
}

void Punt::ForceCalculator(DefensiveAI* Arb) {
	Vector3 PuntNode, DirectionVector;

	Arb->SetColour(Vector4(0.0f, 0.0f, 1.0f, 1.0f));

	PuntNode = NodeCalculation(Arb);
	PuntNode.y = GroundHeight;
	DirectionVector = DirectionCalculation(Arb, PuntNode);

	Arb->Physics()->SetForce(DirectionVector * 50.0f);
	CheckTriggers(Arb);
}

void Punt::CheckTriggers(DefensiveAI* Arb) {
	Vector3 AIBallVec;
	float MagDistAIBall;

	AIBallVec = Arb->scene->FindGameObject("ball")->Physics()->GetPosition() - Arb->Physics()->GetPosition();
	MagDistAIBall = AIBallVec.LengthSquared();

	//cout << MagDistAIBall << endl;

	if (MagDistAIBall < 30) {//if turned off returns to home state, which will then trigger guard state instantly if appropriate
		Arb->SetState(1);
	}
}

//Defend = 1
//Patrol = 2
//Punt = 3
//Off = 4

Vector3 Punt::NodeCalculation(DefensiveAI* Arb) {
	Vector3 node;

	node = Arb->scene->FindGameObject("ball")->Physics()->GetPosition();

	return node;
}

Vector3 Punt::DirectionCalculation(DefensiveAI* Arb, Vector3 node) {
	Vector3 directionvector, AIPosition;

	AIPosition = Arb->Physics()->GetPosition();

	directionvector = node - AIPosition;
	directionvector.Normalise();

	return directionvector;
}
