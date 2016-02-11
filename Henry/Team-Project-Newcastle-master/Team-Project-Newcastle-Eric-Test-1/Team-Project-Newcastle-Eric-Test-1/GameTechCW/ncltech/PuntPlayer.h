#pragma once

#include <ncltech\AggressiveBaseState.h>

//class ArbitraryAI;

class PuntPlayer : public AggressiveBaseState{ //guard state, trying to block player from tardis
public:
	PuntPlayer();
	~PuntPlayer() {};

	void CheckTriggers(AggressiveAI* Arb) override;
	void ForceCalculator(AggressiveAI* Arb) override;

private:
	//Scene* m_scene;

	float MagDistBallGoal;

	Vector3 PatrolNode, AIPosition;
};