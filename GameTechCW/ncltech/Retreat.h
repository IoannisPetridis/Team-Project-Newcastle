#pragma once

#include <ncltech\NeutralBaseState.h>

//class ArbitraryAI;

class Retreat : public NeutralBaseState { //guard state, trying to block player from tardis
public:
	Retreat(NeutralAI* Arb);
	~Retreat() {};

	void CheckTriggers(NeutralAI* Arb) override;
	void ForceCalculator(NeutralAI* Arb) override;
	Vector3 NodeCalculation(NeutralAI* Arb);

private:
	Vector3 EnemyGoalPosition, FriendlyGoalPosition, BallPosition, AIPosition, RetreatNode;
	float GroundHeight;
	int iterator;
};