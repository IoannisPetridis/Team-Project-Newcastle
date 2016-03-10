#include "Confused.h"
#include <ncltech\Scene.h>
#include "AssetsManager.h"

Confused::Confused(AggressiveAI* Arb) {
	GroundHeight = 1.0f;
	iterator = 9;

	Arb->forward = 0;
	Arb->reverse = 0;
	Arb->left = 0;
	Arb->right = 0;

	EnemyPlayer1Position = Arb->scene->FindGameObject("car")->Physics()->GetPosition();
}

//called every frame, sets variables, calculates the node its trying to get to, and calls functions to move it there, also checks triggers to state change
void Confused::ForceCalculator(AggressiveAI* Arb) { //here is where you would put the logic behind the state
	float MagAINodeDist;

	++iterator;

	if (iterator == 10) {
		AIPosition = Arb->Physics()->GetPosition();

		ConfusedNode = NodeCalculation(Arb);
		ConfusedNode.y = GroundHeight;

		iterator = 0;
	}

	MagAINodeDist = (ConfusedNode - AIPosition).Length();

	Arb->DirectionVector = Arb->DirectionCalculation(ConfusedNode, AIPosition);
	Arb->RotationCalculation(ConfusedNode);
	Arb->ForwardBackwardCalculation(MagAINodeDist);

	CheckTriggers(Arb);
}

//checks state change triggers
void Confused::CheckTriggers(AggressiveAI* Arb) {
	if (!AssetsManager::Player_1->GetInvisible()) {
		Arb->SetState(1);
	}
}

//calculates the position of the node it is trying to get too
Vector3 Confused::NodeCalculation(AggressiveAI* Arb) {
	Vector3 confusednode;

	confusednode = EnemyPlayer1Position ;

	return confusednode;
}



