#pragma once

#include <ncltech\NeutralBaseState.h>

//class ArbitraryAI;

class Dribble : public NeutralBaseState { //guard state, trying to block player from tardis
public:
	Dribble(NeutralAI* Arb);
	~Dribble() {};

	void CheckTriggers(NeutralAI* Arb) override;
	void ForceCalculator(NeutralAI* Arb) override;
	Vector3 NodeCalculation(NeutralAI* Arb);

private:
	Vector3 EnemyGoalPosition, FriendlyGoalPosition, BallPosition, AIPosition, DribbleNode;
	float GroundHeight;
	int iterator;
};