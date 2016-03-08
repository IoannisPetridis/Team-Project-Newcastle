#include "PuntPlayer.h"
#include <ncltech\Scene.h>

PuntPlayer::PuntPlayer(AggressiveAI* Arb) {
	GroundHeight = 1.0f;
	AIPosition = Arb->scene->FindGameObject("AggressiveAI")->Physics()->GetPosition();
	BallPosition = Arb->scene->FindGameObject("ball")->Physics()->GetPosition();
	EnemyPlayer1Position = Arb->scene->FindGameObject("car")->Physics()->GetPosition();

	PuntPlayerNode = NodeCalculation(Arb);
	PuntPlayerNode.y = GroundHeight;
	iterator = 9;

	Arb->forward = false;
	Arb->reverse = false;
}

void PuntPlayer::ForceCalculator(AggressiveAI* Arb) {
	float MagAINodeDist;

	++iterator;

	//cout << "punt player" << endl;

	MagAINodeDist = (PuntPlayerNode - AIPosition).Length();

	Arb->DirectionVector = Arb->DirectionCalculation(PuntPlayerNode, AIPosition);
	Arb->RotationCalculation(PuntPlayerNode);

	if (Arb->left == 0 && Arb->right == 0) {
		//cout << "true" << endl;
		Arb->Charge();
	}

	/*else {
	cout << "false" << endl;
	Arb->
	}

	Arb->ForwardBackwardCalculation(MagAINodeDist);*/

	CheckTriggers(Arb);

}

void PuntPlayer::CheckTriggers(AggressiveAI* Arb) {
	Vector3 AINodeVec;
	float MagDistAINode;

	AIPosition = Arb->scene->FindGameObject("AggressiveAI")->Physics()->GetPosition();
	AINodeVec = AIPosition - PuntPlayerNode;
	MagDistAINode = AINodeVec.LengthSquared();

	if (MagDistAINode < 100) {//if turned off returns to home state, which will then trigger guard state instantly if appropriate
		Arb->SetState(1);
	}
}

Vector3 PuntPlayer::NodeCalculation(AggressiveAI* Arb) {
	Vector3 node, AIPlayerVec;

	AIPlayerVec = EnemyPlayer1Position - AIPosition;
	AIPlayerVec = AIPlayerVec + Arb->scene->FindGameObject("car")->Physics()->GetLinearVelocity();
	AIPlayerVec.Normalise();

	node = EnemyPlayer1Position /*+ AIPlayerVec*/;

	return node;
}

//Vector3 PuntPlayer::DirectionCalculation(AggressiveAI* Arb, Vector3 node) {
//	Vector3 directionvector, AIPosition;
//
//	AIPosition = Arb->Physics()->GetPosition();
//
//	directionvector = node - AIPosition;
//	directionvector.Normalise();
//
//	return directionvector;
//}
