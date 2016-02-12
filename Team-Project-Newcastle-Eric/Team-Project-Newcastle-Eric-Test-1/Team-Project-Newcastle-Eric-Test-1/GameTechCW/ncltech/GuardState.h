#pragma once

#include <ncltech\BaseState.h>

//class ArbitraryAI;

class GuardState : public BaseState { //guard state, trying to block player from tardis
public:
	GuardState();
	~GuardState(){};

	void CheckTriggers(ArbitraryAI* Arb) override;
	void ForceCalculator(ArbitraryAI* Arb) override;

private:
	int example;

};