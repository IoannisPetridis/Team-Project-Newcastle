#pragma once

#include <ncltech\AggressiveBaseState.h>

//class ArbitraryAI;

class PuntPlayer : public AggressiveBaseState{ //guard state, trying to block player from tardis
public:
	PuntPlayer(AggressiveAI* Arb);
	PuntPlayer() {};
	~PuntPlayer() {};

	void CheckTriggers(AggressiveAI* Arb) override;
	void ForceCalculator(AggressiveAI* Arb) override;
	Vector3 NodeCalculation(AggressiveAI* Arb);
	//Vector3 DirectionCalculation(AggressiveAI* Arb, Vector3 node);

private:
	float GroundHeight;
	Vector3 AIPosition, EnemyGoalPosition, BallPosition, EnemyPlayer1Position, EnemyPlayer2Position, EnemyPlayer3Position, PuntPlayerNode;
};