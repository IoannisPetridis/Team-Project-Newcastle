#pragma once

#include <ncltech\DefensiveBaseState.h>
#include "Scene.h"

class Defend : public DefensiveBaseState { // home state, rests above tardis when player far away
public:
	Defend();
	~Defend(){};

	void CheckTriggers(DefensiveAI* Arb) override;
	void ForceCalculator(DefensiveAI* Arb) override;
	Vector3 NodeCalculation(DefensiveAI* Arb);
	void FriendlyGoalPositionCalculation(DefensiveAI* Arb);

private:
	Vector3 AIPosition, FriendlyGoalPosition, EnemyGoalPosition, BallPosition, DefendNode;
	float GroundHeight, ballwidthmove;
	int iterator;
};