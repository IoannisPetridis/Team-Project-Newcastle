#include "Block.h"
#include <ncltech\Scene.h>

Block::Block() {
	GroundHeight = 1.0f;
	iterator = 9;
}

//called every frame, sets variables, calculates the node its trying to get to, and calls functions to move it there, also checks triggers to state change
void Block::ForceCalculator(AggressiveAI* Arb) { //here is where you would put the logic behind the state
	float MagAINodeDist;

	++iterator;

	//cout << "block" << endl;

	if (iterator == 10) {
		AIPosition = Arb->Physics()->GetPosition();
		BallPosition = Arb->scene->FindGameObject("ball")->Physics()->GetPosition();
		EnemyPlayer1Position = Arb->scene->FindGameObject("car")->Physics()->GetPosition();

		BlockNode = NodeCalculation(Arb);
		BlockNode.y = GroundHeight;

		//check state triggers every frame to make sure the state does not need to be changed
		iterator = 0;
	}

	MagAINodeDist = (BlockNode - AIPosition).Length();

	Arb->DirectionVector = Arb->DirectionCalculation(BlockNode, AIPosition);
	Arb->RotationCalculation(BlockNode);
	Arb->ForwardBackwardCalculation(MagAINodeDist);

	CheckTriggers(Arb);
}

//checks state change triggers
void Block::CheckTriggers(AggressiveAI* Arb) {
	Vector3 PlayerBallVec;
	float MagDistPlayerBall;

	PlayerBallVec = Arb->scene->FindGameObject("ball")->Physics()->GetPosition() - Arb->scene->FindGameObject("car")->Physics()->GetPosition();
	MagDistPlayerBall = PlayerBallVec.LengthSquared();

	if (MagDistPlayerBall < 600) {//if turned off returns to home state, which will then trigger guard state instantly if appropriate
		Arb->SetState(2);
	}
}

//calculates the position of the node it is trying to get too
Vector3 Block::NodeCalculation(AggressiveAI* Arb) {
	Vector3 PlayerBallVec, blocknode;
	float DistPlayerBall;

	PlayerBallVec = BallPosition - EnemyPlayer1Position;
	DistPlayerBall = PlayerBallVec.Length();
	PlayerBallVec.Normalise();

	blocknode = EnemyPlayer1Position + (PlayerBallVec * DistPlayerBall * 0.5);

	return blocknode;
}



