#include "PuntPlayer.h"
#include <ncltech\Scene.h>

PuntPlayer::PuntPlayer(AggressiveAI* Arb) {
	GroundHeight = 1.0f;
	AIPosition = Arb->scene->FindGameObject("AggressiveAI")->Physics()->GetPosition();
	BallPosition = Arb->scene->FindGameObject("ball")->Physics()->GetPosition();
	EnemyPlayer1Position = Arb->scene->FindGameObject("car")->Physics()->GetPosition();

	PuntPlayerNode = NodeCalculation(Arb);
	PuntPlayerNode.y = GroundHeight;
}

void PuntPlayer::ForceCalculator(AggressiveAI* Arb) {
	Vector3 DirectionVector;

	Arb->SetColour(Vector4(0.0f, 0.0f, 1.0f, 1.0f));

	DirectionVector = DirectionCalculation(Arb, PuntPlayerNode);

	Arb->Physics()->SetForce(DirectionVector * 50.0f);
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

	node = EnemyPlayer1Position + AIPlayerVec * 10;

	return node;
}

Vector3 PuntPlayer::DirectionCalculation(AggressiveAI* Arb, Vector3 node) {
	Vector3 directionvector, AIPosition;

	AIPosition = Arb->Physics()->GetPosition();

	directionvector = node - AIPosition;
	directionvector.Normalise();

	return directionvector;
}
