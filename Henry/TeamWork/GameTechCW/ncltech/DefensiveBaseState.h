#pragma once

#include "DefensiveAI.h"
#include <nclgl\Window.h>

class DefensiveBaseState { //base state from which all substates of AI inherit
	friend class ActionHandler;
public:
	DefensiveBaseState() {};
	~DefensiveBaseState(){};

	virtual void ForceCalculator(DefensiveAI* Arb) = 0;
	virtual void CheckTriggers(DefensiveAI* Arb) = 0;
};
