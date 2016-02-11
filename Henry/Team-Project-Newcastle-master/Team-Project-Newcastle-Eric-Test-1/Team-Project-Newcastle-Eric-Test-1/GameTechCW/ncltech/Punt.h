#pragma once

#include <ncltech\BaseState.h>

//class ArbitraryAI;

class Punt : public BaseState { //guard state, trying to block player from tardis
public:
	Punt();
	~Punt() {};

	void CheckTriggers(DefensiveAI* Arb) override;
	void ForceCalculator(DefensiveAI* Arb) override;

private:
	//Scene* m_scene;

	float MagDistBallGoal;

	Vector3 PatrolNode, AIPosition;
};