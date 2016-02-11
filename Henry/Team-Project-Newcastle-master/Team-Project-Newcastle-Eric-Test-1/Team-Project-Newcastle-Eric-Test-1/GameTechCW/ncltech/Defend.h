#pragma once

#include <ncltech\BaseState.h>

class Defend : public BaseState { // home state, rests above tardis when player far away
public:
	Defend(){};
	~Defend(){};

	void CheckTriggers(DefensiveAI* Arb) override;
	void ForceCalculator(DefensiveAI* Arb) override;

private:
	//Scene* m_scene;
};