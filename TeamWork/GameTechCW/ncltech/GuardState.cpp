#include "GuardState.h"

GuardState::GuardState() {}

void GuardState::ForceCalculator(ArbitraryAI* Arb) { //here is where you would put the logic behind the state

	Arb->Physics()->SetForce(Vector3(0.0f, 0.0f, 0.0f)); //for every frame of OnUpdate object we want to give the object a force, just as a force is given to all objects during their normal process in the physics update loop

	CheckTriggers(Arb); //check state triggers every frame to make sure the state does not need to be changed
}

void GuardState::CheckTriggers(ArbitraryAI* Arb) {
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_K)) { //puts AI to off state on keypress (3 integer denotes off state)
		Arb->SetState(3);
	}

	//this is a trigger i had in my coursework, just a distance threshold triggering state change
	//else if (tardisDistanceFromCameraMag >= 225) {
	//	newState = 1;//home state
	//	Arb->SetState(newState);
	//}
}