#pragma once

#include <ncltech\BaseState.h>

//class ArbitraryAI;

class Patrol : public BaseState { //guard state, trying to block player from tardis
public:
	Patrol();
	~Patrol() {};

	void CheckTriggers(DefensiveAI* Arb) override;
	void ForceCalculator(DefensiveAI* Arb) override;

private:
	//Scene* m_scene;

	float MagDistBallGoal;

	Vector3 PatrolNode, AIPosition;
};