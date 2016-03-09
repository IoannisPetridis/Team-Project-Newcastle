#pragma once

#include <ncltech\NeutralBaseState.h>

//class ArbitraryAI;

class Chase : public NeutralBaseState { //guard state, trying to block player from tardis
public:
	Chase(NeutralAI* Arb);
	~Chase() {};

	void CheckTriggers(NeutralAI* Arb) override;
	void ForceCalculator(NeutralAI* Arb) override;
	Vector3 NodeCalculation(NeutralAI* Arb);

private:
	Vector3 EnemyGoalPosition, FriendlyGoalPosition, BallPosition, AIPosition, ChaseNode;
	float GroundHeight;
	int iterator;
};