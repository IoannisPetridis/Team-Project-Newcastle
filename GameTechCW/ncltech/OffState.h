#pragma once

#include <ncltech\BaseState.h>

class OffState : public BaseState { //returns to position above tardis and pauses when triggered
public:
	OffState();
	~OffState(){};

	void CheckTriggers(ArbitraryAI* Arb) override;
	void ForceCalculator(ArbitraryAI* Arb) override;

private:
	int example;

};