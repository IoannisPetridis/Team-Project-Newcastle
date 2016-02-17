#pragma once

#include <ncltech\BaseState.h>

class Defend : public BaseState { // home state, rests above tardis when player far away
public:
	Defend(){};
	~Defend(){};

	void CheckTriggers(DefensiveAI* Arb) override;
	void ForceCalculator(DefensiveAI* Arb) override;
	Vector3 NodeCalculation(DefensiveAI* Arb);
	Vector3 DirectionCalculation(DefensiveAI* Arb, Vector3 node);

private:

	Vector3 AIPosition, GoalPosition, BallPosition;
	//Scene* m_scene;
};