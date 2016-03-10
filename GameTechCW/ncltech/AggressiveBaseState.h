#pragma once

#include "AggressiveAI.h"
#include <nclgl\Window.h>

class AggressiveBaseState { //base state from which all substates of AI inherit
public:
	AggressiveBaseState() {};
	~AggressiveBaseState(){};

	virtual void ForceCalculator(AggressiveAI* Arb) = 0;
	virtual void CheckTriggers(AggressiveAI* Arb) = 0;
};
