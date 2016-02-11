#pragma once

#include <ncltech\BaseState.h>

class OffState : public BaseState { //returns to position above tardis and pauses when triggered
public:
	OffState(){};
	~OffState(){};

	void CheckTriggers(DefensiveAI* Arb) override;
	void ForceCalculator(DefensiveAI* Arb) override;

private:
	//Scene* m_scene;
};