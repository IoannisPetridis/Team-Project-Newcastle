#pragma once

#include <ncltech\SoloBaseState.h>
#include "Scene.h"

class SDefend : public SoloBaseState { // home state, rests above tardis when player far away
public:
	SDefend(SoloAI* Arb);
	~SDefend(){};

	void CheckTriggersDefend(SoloAI* Arb) override;
	void CheckTriggersScore(SoloAI* Arb) override;
	void ForceCalculator(SoloAI* Arb) override;
	Vector3 NodeCalculation(SoloAI* Arb);
	void FriendlyGoalPositionCalculation(SoloAI* Arb);

	void SetStateBool(SoloAI* Arb);

private:
	Vector3 AIPosition, FriendlyGoalPosition, EnemyGoalPosition, BallPosition, DefendNode;
	float GroundHeight, ballwidthmove;
	int iterator;
};