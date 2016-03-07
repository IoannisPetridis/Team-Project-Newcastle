#pragma once
#include "ActionHandler.h"

ActionHandler::ActionHandler() {
	timersize = 6;
	
	for (int i = 0; i < timersize; i++) {
		timer[i] = -1.0f;
	}
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
		NCLDebug::Log(Vector3(1.0f, 1.0f, 0.0f), "Speed: " + std::to_string(timer));
		P->Physics()->SetForce(force * timer);

		force.Normalise();
		NCLDebug::DrawThickLine(P->Physics()->GetPosition(), P->Physics()->GetPosition() + force,
			0.02, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (!Window::GetKeyboard()->KeyHeld(key)
		&& timer > 0.0f) {
		NCLDebug::Log(Vector3(1.0f, 1.0f, 0.0f), "enter");
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

void ActionHandler::ControllerHandle_Jump(Player* P, KeyboardKeys key, Vector3 force, float& timer, float& energybar) {
	engine_timer.GetTimedMS();
	if (Window::GetKeyboard()->KeyHeld(key)) {
		if (timer == -1.0f) {
			timer = 3.0f;
		}
		timer += engine_timer.GetTimedMS() * 200.0f;
		timer = min(timer, 8.0f);
		NCLDebug::Log(Vector3(1.0f, 1.0f, 0.0f), "timer: " + std::to_string(timer));
		P->Physics()->SetForce(force * timer);

		force.Normalise();
		NCLDebug::DrawThickLine(P->Physics()->GetPosition(), P->Physics()->GetPosition() + force,
			0.02, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (!Window::GetKeyboard()->KeyHeld(key)
		&& timer > 0.0f) {
		NCLDebug::Log(Vector3(1.0f, 1.0f, 0.0f), "enter");
		P->Physics()->SetForce(Vector3(0.0f, 0.0f, 0.0f));
		timer = -1.0f;
	}

}

void ActionHandler::Update(float dt) {
	{
		//Keyboard Control
		ControllerHandle_Force(AssetsManager::Player_1, KEYBOARD_I,
		AssetsManager::Player_1->front_normal * 150.0f, timer[0]);

		ControllerHandle_Ori(AssetsManager::Player_1, KEYBOARD_J,
			Vector3(0.0f, 1.0f, 0.0f), 2.0f);

		ControllerHandle_Force(AssetsManager::Player_1, KEYBOARD_K,
			AssetsManager::Player_1->Rear_normal * 150.0f, timer[2]);

		ControllerHandle_Ori(AssetsManager::Player_1, KEYBOARD_L,
			Vector3(0.0f, 1.0f, 0.0f), -2.0f);

		ControllerHandle_Ori(AssetsManager::Player_1, KEYBOARD_U,
			Vector3(1.0f, 0.0f, 0.0f), 2.0f);

		ControllerHandle_Ori(AssetsManager::Player_1, KEYBOARD_O,
			Vector3(1.0f, 0.0f, 0.0f), -2.0f);

		if (Vector3::Dot(AssetsManager::Player_1->Top_normal, Vector3(0.0f, 1.0f, 0.0f))
			> 0)
		ControllerHandle_Jump(AssetsManager::Player_1, KEYBOARD_SPACE,
			AssetsManager::Player_1->Top_normal * 100.0f, timer[1], timer[3]);
		else if (Vector3::Dot(AssetsManager::Player_1->Top_normal, Vector3(0.0f, 1.0f, 0.0f))
			< 0)
			ControllerHandle_Jump(AssetsManager::Player_1, KEYBOARD_SPACE,
			AssetsManager::Player_1->Bottom_normal * 100.0f, timer[1], timer[3]);
		else {
			if (Vector3::Dot(AssetsManager::Player_1->Right_normal, Vector3(0.0f, 1.0f, 0.0f))
				<= 0)
				ControllerHandle_Jump(AssetsManager::Player_1, KEYBOARD_SPACE,
				AssetsManager::Player_1->Right_normal * 100.0f, timer[1], timer[3]);
			else
				ControllerHandle_Jump(AssetsManager::Player_1, KEYBOARD_SPACE,
				AssetsManager::Player_1->Left_normal * 100.0f, timer[1], timer[3]);
		}
	}


	//respawn
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_3)) {
		AssetsManager::Player_1->Physics()->SetPosition(Vector3(0.0f, 5.0f, 0.0f));
		AssetsManager::Player_1->Physics()->SetForce(Vector3(0.0f, 0.0f, 0.0f));
		AssetsManager::Player_1->Physics()->SetLinearVelocity(Vector3(0.0f, 0.0f, 0.0f));
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_T)) {
		m_scene->lightList.at(1).SetPosition(m_scene->lightList.at(1).GetPosition() + Vector3(-2.0f, 0, 0));
		//m_scene->FindGameObject("light")->Physics()->SetPosition(m_scene->lightList.at(0).GetPosition());
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_H)) {
		m_scene->lightList.at(1).SetPosition(m_scene->lightList.at(1).GetPosition() + Vector3(0, 0, 2.0f));
		//m_scene->FindGameObject("light")->Physics()->SetPosition(m_scene->lightList.at(0).GetPosition());
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_G)) {
		m_scene->lightList.at(1).SetPosition(m_scene->lightList.at(1).GetPosition() + Vector3(2.0f, 0, 0));
		//m_scene->FindGameObject("light")->Physics()->SetPosition(m_scene->lightList.at(0).GetPosition());
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_F)) {
		m_scene->lightList.at(1).SetPosition(m_scene->lightList.at(1).GetPosition() + Vector3(0, 0, -2.0f));
		//m_scene->FindGameObject("light")->Physics()->SetPosition(m_scene->lightList.at(0).GetPosition());
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_N)) {
		m_scene->lightList.at(1).SetPosition(m_scene->lightList.at(1).GetPosition() + Vector3(0, -2.0f, 0));
		//m_scene->FindGameObject("light")->Physics()->SetPosition(m_scene->lightList.at(0).GetPosition());
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_M)) {
		m_scene->lightList.at(1).SetPosition(m_scene->lightList.at(1).GetPosition() + Vector3(0, 2.0f, 0));
		//m_scene->FindGameObject("light")->Physics()->SetPosition(m_scene->lightList.at(0).GetPosition());
	}

	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_F1))
	{
		cout << m_scene->lightList.at(1).GetPosition();
	}

	//spawn partical
	(m_scene->m_RootParticleList->GetChildren())[0]->SetSourcePosition(m_scene->FindGameObject("car")->Physics()->GetPosition());
	
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_8)) {
		(m_scene->m_RootParticleList->GetChildren())[0]->TrigleOnOff();
		cout << (m_scene->m_RootParticleList->GetChildren())[0]->getIsOn()<<endl;
		(m_scene->m_RootParticleList->GetChildren())[1]->TrigleOnOff();
	}

	AssetsManager::Player_1->IDPlayerFaces();

	Window::GetWindow().ShowOSPointer(false);
	Window::GetWindow().LockMouseToWindow(true);
}

void ActionHandler::ControlUpdate(int mode) {
	if (mode == 1) 
	AssetsManager::Camera_Entity->Physics()
		->SetPosition(m_scene->m_Camera->GetPosition());
	if (mode == 2)
		m_scene->m_Camera->SetPosition(
		AssetsManager::Camera_Entity->Physics()->GetPosition());
}
