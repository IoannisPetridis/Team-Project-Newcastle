#include "Defend.h"
#include <ncltech\Scene.h>

void Defend::ForceCalculator(DefensiveAI* Arb) { //here is where you would put the logic behind the state
	Vector3 BallPosition, AIPosition, GoalPosition, DefendNode, DirGoalBall, DirAIDefNode;
	float DistGoalBall;

	Arb->SetColour(Vector4(0.0f, 1.0f, 0.0f, 1.0f));

	BallPosition = Vector3(20.0f, 0.0f, 20.0f);
	GoalPosition = Vector3(0.0f, 0.0f, 0.0f);
	AIPosition = Arb->Physics()->GetPosition();

	DirGoalBall = BallPosition - GoalPosition;
	DistGoalBall = DirGoalBall.Length();
	DirGoalBall.Normalise();

	DefendNode = DirGoalBall * DistGoalBall * 0.2;

	DirAIDefNode = DefendNode - AIPosition;
	DirAIDefNode.Normalise();

	Arb->Physics()->SetForce(DirAIDefNode * 15);

	CheckTriggers(Arb); //check state triggers every frame to make sure the state does not need to be changed
}

void Defend::CheckTriggers(DefensiveAI* Arb) {
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_Q)) { //puts AI to off state on keypress (3 integer denotes off state)
		Arb->SetState(3);
	}

	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_E)) {//if turned off returns to home state, which will then trigger guard state instantly if appropriate
		Arb->SetState(2);
	}

}