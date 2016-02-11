#include "OffState.h"
#include <ncltech\Scene.h>

void OffState::ForceCalculator(DefensiveAI* Arb) { //here is where you would put the logic behind the state

	Arb->SetColour(Vector4(0.0f, 0.0f, 0.0f, 1.0f));

	//Arb->Physics()->SetForce(Vector3(0.0f, 0.0f, 0.0f)); //for every frame of OnUpdate object we want to give the object a force, just as a force is given to all objects during their normal process in the physics update loop

	CheckTriggers(Arb); //check state triggers every frame to make sure the state does not need to be changed
}

void OffState::CheckTriggers(DefensiveAI* Arb) {
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_Q)) {//if turned off returns to home state, which will then trigger guard state instantly if appropriate
		Arb->SetState(2);
	}
}