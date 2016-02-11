#pragma once

#include <ncltech\AggressiveBaseState.h>

//class ArbitraryAI;

class Block : public AggressiveBaseState { //guard state, trying to block player from tardis
public:
	Block();
	~Block() {};

	void CheckTriggers(AggressiveAI* Arb) override;
	void ForceCalculator(AggressiveAI* Arb) override;

private:
	//Scene* m_scene;

	float MagDistBallGoal;

	Vector3 PatrolNode, AIPosition;
};