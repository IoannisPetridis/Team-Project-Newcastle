#pragma once

#include <ncltech\BaseState.h>

class HomeState : public BaseState { // home state, rests above tardis when player far away
public:
	HomeState();
	~HomeState(){};

	void CheckTriggers(ArbitraryAI* Arb) override;
	void ForceCalculator(ArbitraryAI* Arb) override;

private:
	int example;
};