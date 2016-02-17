#include "Dribble.h"
#include <ncltech\Scene.h>

Dribble::Dribble() {
	

}

void Dribble::ForceCalculator(NeutralAI* Arb) { //here is where you would put the logic behind the state
	Vector3 DirectionVector;

	Arb->SetColour(Vector4(1.0f, 0.0f, 0.0f, 1.0f));

	BallPosition = Arb->scene->FindGameObject("Ball")->Physics()->GetPosition();
	EnemyGoalPosition = Arb->scene->FindGameObject("EnemyGoal")->Physics()->GetPosition();
	FriendlyGoalPosition = Arb->scene->FindGameObject("FriendlyGoal")->Physics()->GetPosition();
	AIPosition = Arb->Physics()->GetPosition();

	DribbleNode = NodeCalculation(Arb);
	DirectionVector = DirectionCalculation(Arb, DribbleNode);

	Arb->Physics()->SetForce(DirectionVector * 30);

	CheckTriggers(Arb); 
}

void Dribble::CheckTriggers(NeutralAI* Arb) {
	Vector3 AINodeVec;
	float MagDistAINode;

	AINodeVec = DribbleNode - AIPosition;
	MagDistAINode = AINodeVec.LengthSquared();

	if (MagDistAINode > 100) { //puts AI to off state on keypress (3 integer denotes off state)
	Arb->SetState(1);
	}

}

//Chase == 1
//Dribble == 2

Vector3 Dribble::NodeCalculation(NeutralAI* Arb) {
	Vector3 node;

	node = Arb->scene->FindGameObject("Ball")->Physics()->GetPosition();

	return node;
}

Vector3 Dribble::DirectionCalculation(NeutralAI* Arb, Vector3 node) {
	Vector3 directionvector;

	directionvector = node - AIPosition;
	directionvector.Normalise();

	return directionvector;
}