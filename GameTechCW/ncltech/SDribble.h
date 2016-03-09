#pragma once

#include <ncltech\SoloBaseState.h>

//class ArbitraryAI;

class SDribble : public SoloBaseState { //guard state, trying to block player from tardis
public:
	SDribble(SoloAI* Arb);
	~SDribble() {};

	void CheckTriggersScore(SoloAI* Arb) override;
	void CheckTriggersDefend(SoloAI* Arb) override;
	void ForceCalculator(SoloAI* Arb) override;
	Vector3 NodeCalculation(SoloAI* Arb);

	void SetStateBool(SoloAI* Arb);

private:
	Vector3 EnemyGoalPosition, FriendlyGoalPosition, BallPosition, AIPosition, DribbleNode;
	float GroundHeight;
	int iterator;
};