#pragma once

#include <ncltech\SoloBaseState.h>

//class ArbitraryAI;

class SPunt : public SoloBaseState { //guard state, trying to block player from tardis
public:
	SPunt(SoloAI* Arb);
	~SPunt() {};

	void CheckTriggersDefend(SoloAI* Arb) override;
	void CheckTriggersScore(SoloAI* Arb) override;
	void ForceCalculator(SoloAI* Arb) override;
	Vector3 NodeCalculation(SoloAI* Arb);

	void SetStateBool(SoloAI* Arb);

private:
	Vector3 AIPosition, BallPosition, AIBallVec, PuntNode, FriendlyGoalPosition, EnemyGoalPosition;
	float GroundHeight, MagAIBallDist;
	int iterator;
};