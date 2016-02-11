#pragma once

#include "ArbitraryAI.h"
#include <nclgl\Window.h>

class BaseState { //base state from which all substates of AI inherit
public:
	BaseState() {};
	~BaseState(){};

	virtual void ForceCalculator(ArbitraryAI* Arb);
	virtual void CheckTriggers(ArbitraryAI* Arb);
};
