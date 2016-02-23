#include "Punt.h"

Punt::Punt() {
	GroundHeight = 1.0f;
}

void Punt::ForceCalculator(DefensiveAI* Arb) {
	Vector3 PuntNode;
	float MagAINodeDist;

	AIPosition = Arb->Physics()->GetPosition();
	BallPosition = Arb->scene->FindGameObject("ball")->Physics()->GetPosition() * Vector3(1.0f, 0.0f, 1.0f);
	AIBallVec = BallPosition - AIPosition;
	MagAIBallDist = AIBallVec.Length();
	AIBallVec.Normalise();

	PuntNode = NodeCalculation(Arb);
	PuntNode.y = GroundHeight;

	MagAINodeDist = (PuntNode - AIPosition).Length();

	Arb->DirectionVector = Arb->DirectionCalculation(PuntNode, AIPosition);
	Arb->RotationCalculation(PuntNode);
	Arb->ForwardBackwardCalculation(MagAINodeDist);

	//cout << "punt" << endl;

	CheckTriggers(Arb);
}

void Punt::CheckTriggers(DefensiveAI* Arb) {

	if (MagAIBallDist < 5) {//if turned off returns to home state, which will then trigger guard state instantly if appropriate
		Arb->SetState(1);
	}
}

//Defend = 1
//Patrol = 2
//Punt = 3
//Off = 4

Vector3 Punt::NodeCalculation(DefensiveAI* Arb) {
	Vector3 node, AIBallVec;

	node = Arb->scene->FindGameObject("ball")->Physics()->GetPosition() + (AIBallVec * 50);

	return node;
}

//Vector3 Punt::DirectionCalculation(DefensiveAI* Arb, Vector3 node) {
//	Vector3 directionvector, AIPosition;
//
//	AIPosition = Arb->Physics()->GetPosition();
//
//	directionvector = node - AIPosition;
//	directionvector.Normalise();
//
//	return directionvector;
//}
