#pragma once

#include "DefensiveAI.h"
#include <nclgl\Window.h>

class BaseState { //base state from which all substates of AI inherit
public:
	BaseState() {};
	~BaseState(){};

	virtual void ForceCalculator(DefensiveAI* Arb) = 0;
	virtual void CheckTriggers(DefensiveAI* Arb) = 0;
};
