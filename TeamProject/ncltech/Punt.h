#pragma once

#include <ncltech\DefensiveBaseState.h>

//class ArbitraryAI;

class Punt : public DefensiveBaseState { //guard state, trying to block player from tardis
public:
	Punt();
	~Punt() {};

	void CheckTriggers(DefensiveAI* Arb) override;
	void ForceCalculator(DefensiveAI* Arb) override;
	Vector3 NodeCalculation(DefensiveAI* Arb);
	/*Vector3 DirectionCalculation(DefensiveAI* Arb, Vector3 node);
	void ControlInputCalculation(DefensiveAI* Arb, Vector3 directionvector, Vector3 puntnode);*/

private:
	Vector3 AIPosition, BallPosition, AIBallVec, PuntNode, FriendlyGoalPosition, EnemyGoalPosition;
	float GroundHeight, MagAIBallDist;
	int iterator;
};