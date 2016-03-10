#pragma once

#include <ncltech\AggressiveBaseState.h>

//class ArbitraryAI;

class Confused : public AggressiveBaseState { //guard state, trying to block player from tardis
public:
	Confused(AggressiveAI* Arb);
	~Confused() {};

	void CheckTriggers(AggressiveAI* Arb) override;
	void ForceCalculator(AggressiveAI* Arb) override;
	Vector3 NodeCalculation(AggressiveAI* Arb);

private:
	Vector3 AIPosition, EnemyGoalPosition, BallPosition, EnemyPlayer1Position, EnemyPlayer2Position, EnemyPlayer3Position, ConfusedNode;
	float GroundHeight;
	int iterator;
};