#pragma once

#include <ncltech\BaseState.h>

//class ArbitraryAI;

class Punt : public BaseState { //guard state, trying to block player from tardis
public:
	Punt(){};
	~Punt() {};

	void CheckTriggers(DefensiveAI* Arb) override;
	void ForceCalculator(DefensiveAI* Arb) override;
	Vector3 NodeCalculation(DefensiveAI* Arb);
	Vector3 DirectionCalculation(DefensiveAI* Arb, Vector3 node);

private:

};