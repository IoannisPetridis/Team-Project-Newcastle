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
	Vector3 DirectionCalculation(DefensiveAI* Arb, Vector3 node);
	void ControlInputCalculation(DefensiveAI* Arb, Vector3 directionvector, Vector3 defendnode);

private:
	Vector3 AIPosition, GoalPosition, BallPosition;
	float GroundHeight;

};