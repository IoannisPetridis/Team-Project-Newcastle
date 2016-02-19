#include "Block.h"
#include <ncltech\Scene.h>

Block::Block() {
	GroundHeight = 1.0f;
}

void Block::ForceCalculator(AggressiveAI* Arb) { //here is where you would put the logic behind the state
	Vector3 BlockNode, DirectionVector;

	AIPosition = Arb->Physics()->GetPosition();
	BallPosition = Arb->scene->FindGameObject("ball")->Physics()->GetPosition();
	EnemyPlayer1Position = Arb->scene->FindGameObject("car")->Physics()->GetPosition();

	BlockNode = NodeCalculation(Arb);
	BlockNode.y = GroundHeight;
	DirectionVector = DirectionCalculation(Arb, BlockNode);

	//ControlInputCalculation(Arb, DirectionVector, DefendNode);

	Arb->Physics()->SetForce(DirectionVector * 30);

	CheckTriggers(Arb); //check state triggers every frame to make sure the state does not need to be changed
}

void Block::CheckTriggers(AggressiveAI* Arb) {
	Vector3 PlayerBallVec;
	float MagDistPlayerBall;

	PlayerBallVec = Arb->scene->FindGameObject("ball")->Physics()->GetPosition() - Arb->scene->FindGameObject("car")->Physics()->GetPosition();
	MagDistPlayerBall = PlayerBallVec.LengthSquared();

	if (MagDistPlayerBall < 400) {//if turned off returns to home state, which will then trigger guard state instantly if appropriate
		Arb->SetState(2);
	}
}



Vector3 Block::NodeCalculation(AggressiveAI* Arb) {
	Vector3 PlayerBallVec, blocknode;
	float DistPlayerBall;

	PlayerBallVec = BallPosition - EnemyPlayer1Position;
	DistPlayerBall = PlayerBallVec.Length();
	PlayerBallVec.Normalise();

	blocknode = EnemyPlayer1Position + (PlayerBallVec * DistPlayerBall * 0.5);

	return blocknode;
}

Vector3 Block::DirectionCalculation(AggressiveAI* Arb, Vector3 node) {
	Vector3 directionvector;

	directionvector = node - AIPosition;
	directionvector.Normalise();

	return directionvector;
}

//void Defend::ControlInputCalculation(DefensiveAI* Arb, Vector3 directionvector, Vector3 defendnode) {
//	float dotproduct, cosineangle;
//
//	dotproduct = Vector3::Dot(directionvector, Arb->GetFrontNormal());
//	cosineangle = dotproduct / (directionvector.Length());
//}