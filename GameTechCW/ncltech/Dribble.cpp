#include "Dribble.h"
#include <ncltech\Scene.h>

Dribble::Dribble() {
	GroundHeight = 1.0f;
	iterator = 9;
}

void Dribble::ForceCalculator(NeutralAI* Arb) { //here is where you would put the logic behind the state
	float MagAINodeDist;

	++iterator;

	if (iterator == 10) {
		BallPosition = Arb->scene->FindGameObject("ball")->Physics()->GetPosition();
		EnemyGoalPosition = Arb->scene->FindGameObject("EnemyGoal")->Physics()->GetPosition();
		FriendlyGoalPosition = Arb->scene->FindGameObject("FriendlyGoal")->Physics()->GetPosition();
		AIPosition = Arb->Physics()->GetPosition();

		DribbleNode = NodeCalculation(Arb);
		DribbleNode.y = GroundHeight;

		iterator = 0;
	}

	MagAINodeDist = (DribbleNode - AIPosition).Length();

	Arb->DirectionVector = Arb->DirectionCalculation(DribbleNode, AIPosition);
	Arb->RotationCalculation(DribbleNode);
	Arb->ForwardBackwardCalculation(MagAINodeDist);

	CheckTriggers(Arb);
}

void Dribble::CheckTriggers(NeutralAI* Arb) {
	Vector3 AINodeVec;
	float MagDistAINode;

	AINodeVec = DribbleNode - AIPosition;
	MagDistAINode = AINodeVec.LengthSquared();

	if (MagDistAINode > 100) {
		Arb->SetState(1);
	}

}

//Chase == 1
//Dribble == 2

Vector3 Dribble::NodeCalculation(NeutralAI* Arb) {
	Vector3 node, goalballdirvec;

	goalballdirvec = BallPosition - EnemyGoalPosition;
	goalballdirvec.Normalise();

	node = BallPosition + (goalballdirvec * 3.0f);

	return node;
}

Vector3 Dribble::DirectionCalculation(NeutralAI* Arb, Vector3 node) {
	Vector3 directionvector;

	directionvector = node - AIPosition;
	directionvector.Normalise();

	return directionvector;
}