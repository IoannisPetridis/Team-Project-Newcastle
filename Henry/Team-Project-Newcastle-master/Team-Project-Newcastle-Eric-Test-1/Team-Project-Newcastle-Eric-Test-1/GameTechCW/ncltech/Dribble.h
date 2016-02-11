#pragma once

#include <ncltech\NeutralBaseState.h>

//class ArbitraryAI;

class Dribble : public NeutralBaseState { //guard state, trying to block player from tardis
public:
	Dribble();
	~Dribble() {};

	void CheckTriggers(NeutralAI* Arb) override;
	void ForceCalculator(NeutralAI* Arb) override;

private:
	//Scene* m_scene;

	float MagDistBallGoal;

	Vector3 PatrolNode, AIPosition;
};