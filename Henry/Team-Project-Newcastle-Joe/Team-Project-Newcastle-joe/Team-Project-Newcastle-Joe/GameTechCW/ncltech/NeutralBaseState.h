#pragma once

#include "NeutralAI.h"
#include <nclgl\Window.h>

class NeutralBaseState { //base state from which all substates of AI inherit
public:
	NeutralBaseState() {};
	~NeutralBaseState(){};

	virtual void ForceCalculator(NeutralAI* Arb) = 0;
	virtual void CheckTriggers(NeutralAI* Arb) = 0;
};
