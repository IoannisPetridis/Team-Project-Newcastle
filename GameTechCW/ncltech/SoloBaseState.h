#pragma once

#include "SoloAI.h"
#include <nclgl\Window.h>

class SoloBaseState { //base state from which all substates of AI inherit
public:
	SoloBaseState() {};
	~SoloBaseState(){};

	virtual void ForceCalculator(SoloAI* Arb) = 0;
	virtual void CheckTriggersScore(SoloAI* Arb) = 0;
	virtual void CheckTriggersDefend(SoloAI* Arb) = 0;
};
