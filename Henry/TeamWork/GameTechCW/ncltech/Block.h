#pragma once

#include <ncltech\AggressiveBaseState.h>

//class ArbitraryAI;

class Block : public AggressiveBaseState { //guard state, trying to block player from tardis
public:
	Block();
	~Block() {};

	void CheckTriggers(AggressiveAI* Arb) override;
	void ForceCalculator(AggressiveAI* Arb) override;
	Vector3 NodeCalculation(AggressiveAI* Arb);

private:
	Vector3 AIPosition, EnemyGoalPosition, BallPosition, EnemyPlayer1Position, EnemyPlayer2Position, EnemyPlayer3Position, BlockNode;
	float GroundHeight;
	int iterator;
};