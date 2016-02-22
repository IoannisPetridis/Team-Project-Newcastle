#pragma once
#include "ActionHandler.h"

ActionHandler::ActionHandler() {	
	timer[0] = -1.0f;
	timer[1] = -1.0f;
	timer[2] = 0.0f;

	Inair = false;
	doubleJump = false;
}

int ActionHandler::ScoreCheck() {
	if (m_scene->m_RootGameObject->FindGameObject("ball")) {
		Vector3 pos = m_scene->m_RootGameObject->FindGameObject("ball")->Physics()->GetPosition();
		if ((pos.x < -200.0f) &&
			(pos.z > -50.0f && pos.z < 50.0f) &&
			(pos.y > 0.0f && pos.z < 40.0f)) {
			NCLDebug::Log(Vector3(1.0f, 0.0f, 0.0f),
				"Red Score");

			m_scene->m_RootGameObject->FindGameObject("ball")
				->Physics()->SetPosition(Vector3(0.0f, 10.0f, 0.0f));
			AssetsManager::Player_1->Physics()->SetPosition(Vector3(10.0f, 10.0f, 10.0f));

			return 1;
		}

		if ((pos.x > 200.0f) &&
			(pos.z > -50.0f && pos.z < 50.0f) &&
			(pos.y > 0.0f && pos.z < 40.0f)) {
			NCLDebug::Log(Vector3(1.0f, 0.0f, 0.0f),
				"Blue Score");

			m_scene->m_RootGameObject->FindGameObject("ball")
				->Physics()->SetPosition(Vector3(0.0f, 10.0f, 0.0f));
			AssetsManager::Player_1->Physics()->SetPosition(Vector3(10.0f, 10.0f, 10.0f));
			return 2;
		}
	}

	else return 0;
}

void ActionHandler::SetDefaultScene(Scene* scene) {
	m_scene = scene;
}

void ActionHandler::ControllerHandle_Force(Player* P, KeyboardKeys key, Vector3 force, float& timer) {	
	engine_timer.GetTimedMS();
	if (Window::GetKeyboard()->KeyHeld(key)) {
		if (timer == -1.0f) {
			timer = 2.0f;
		}
		timer += engine_timer.GetTimedMS() * 100.0f;
		timer = min(timer, 8.0f);
		//NCLDebug::Log(Vector3(1.0f, 1.0f, 0.0f), "Speed: " + std::to_string(timer));
		P->Physics()->SetForce(force * timer);

		force.Normalise();
		//NCLDebug::DrawThickLine(P->Physics()->GetPosition(), P->Physics()->GetPosition() + force,
			//0.02, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (!Window::GetKeyboard()->KeyHeld(key)
		&& timer > 0.0f) {
		//NCLDebug::Log(Vector3(1.0f, 1.0f, 0.0f), "enter");
		P->Physics()->SetForce(Vector3(0.0f, 0.0f, 0.0f));
		timer = -1.0f;
	}
}

void ActionHandler::ControllerHandle_Ori(Player* P, KeyboardKeys key, Vector3 Axis,float degree) {
	if (Window::GetKeyboard()->KeyHeld(key)) {
		Quaternion rot = P->Physics()->GetOrientation() *
			Quaternion::AxisAngleToQuaterion(Axis, degree);
		P->Physics()->SetOrientation(rot);
	}
}

void ActionHandler::ControllerHandle_Jump(Player* P, KeyboardKeys key) {
	//check collision with ground
	vector<GameObject*> Glist = m_scene->ReadGroundList();
	
	for (auto& m : Glist) {
		if (PhysicsEngine::Instance()->CheckCollision(P->Physics(), m->Physics())) 
		{
			Inair = false;
			doubleJump = false;
			break;
		}
	}

	//Second Jump
	if (Inair && !doubleJump) {
		if (Window::GetKeyboard()->KeyTriggered(key)){
			P->Physics()->SetLinearVelocity(P->Physics()->GetLinearVelocity() + Vector3(0.0f, 10.0f, 0.0f));
			doubleJump = true;
		}
		else if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_A)) {
			P->Physics()->SetLinearVelocity(P->Physics()->GetLinearVelocity() + P->Left_normal * 10.0f);
			doubleJump = true;
		}
		else if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_D)) {
			P->Physics()->SetLinearVelocity(P->Physics()->GetLinearVelocity() + P->Right_normal * 10.0f);
			doubleJump = true;
		}
		else if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_W)) {
			P->Physics()->SetLinearVelocity(P->Physics()->GetLinearVelocity() + P->front_normal * 10.0f);
			doubleJump = true;
		}
	}

	//First Jump
	if (!Inair) {
		if (Window::GetKeyboard()->KeyTriggered(key)) {
			Inair = true;
			P->Physics()->SetLinearVelocity(P->Physics()->GetLinearVelocity()
				+ Vector3(0.0f, 10.0f, 0.0f));
		}
	}
}

void ActionHandler::Flip(Player *P) {
	float Top_factor = Vector3::Dot(P->Top_normal, Vector3(0.0f, 1.0f, 0.0f));
	float Top_angle = acos(Top_factor) * 180.0f / PI;
	if (Top_angle >= 90.0f) {
		P->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0.0f, 90.0f, 0.0f));
	}
}

void ActionHandler::Update(float dt) {
	NCLDebug::Log(Vector3(0.0f, 0.0f, 0.0f), std::to_string(AssetsManager::Player_1->Physics()->GetLinearVelocity().Length()));
	
	{
		AssetsManager::Player_1->NormalCal();

		Flip(AssetsManager::Player_1);
		//Keyboard Control
		ControllerHandle_Force(AssetsManager::Player_1, KEYBOARD_W,
		AssetsManager::Player_1->front_normal * 150.0f, timer[0]);

		ControllerHandle_Ori(AssetsManager::Player_1, KEYBOARD_A,
			Vector3(0.0f, 1.0f, 0.0f), 2.0f);

		ControllerHandle_Force(AssetsManager::Player_1, KEYBOARD_S,
			AssetsManager::Player_1->Rear_normal * 150.0f, timer[1]);

		ControllerHandle_Ori(AssetsManager::Player_1, KEYBOARD_D,
			Vector3(0.0f, 1.0f, 0.0f), -2.0f);

		ControllerHandle_Jump(AssetsManager::Player_1, KEYBOARD_SPACE);
	}

	//spawn partical
	(m_scene->m_RootParticleList->GetChildren())[0]->SetDirection(AssetsManager::Player_1->Rear_normal);
	(m_scene->m_RootParticleList->GetChildren())[0]->SetSourcePosition(AssetsManager::Player_1->Physics()->GetPosition() +
		AssetsManager::Player_1->Physics()->GetOrientation().ToMatrix3() * Vector3(0, 0, 1));

	Window::GetWindow().ShowOSPointer(false);
	Window::GetWindow().LockMouseToWindow(true);
}

