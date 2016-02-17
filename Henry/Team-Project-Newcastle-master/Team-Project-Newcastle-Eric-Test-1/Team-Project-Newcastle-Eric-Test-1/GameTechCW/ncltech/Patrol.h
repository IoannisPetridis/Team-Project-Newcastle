#pragma once

#include <ncltech\BaseState.h>
#include "Scene.h"

//class ArbitraryAI;

class Patrol : public BaseState { //guard state, trying to block player from tardis
public:
	Patrol(DefensiveAI* Arb);
	~Patrol() {};

	void CheckTriggers(DefensiveAI* Arb) override;
	void ForceCalculator(DefensiveAI* Arb) override;
	Vector3 NodeCalculation(DefensiveAI* Arb);
	Vector3 DirectionCalculation(DefensiveAI* Arb, Vector3 node1, Vector3 node2);
	void InstantiatePatrolPoint(DefensiveAI* Arb);

private:
	//float MagDistBallGoal;
	Vector3 PatrolPoint, PatrolNode, BallPosition, FriendlyGoalPosition, AIPosition;
};