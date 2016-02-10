#pragma once
#include "ActionHandler.h"

Player::Player(const std::string& name) : SimpleMeshObject(name) {}

void Player::OnUpdateObject(float dt) {
	//ControllerHandle();
}

void ActionHandler::SetDefaultScene(Scene* scene) {
	m_scene = scene;
}

void ActionHandler::ControllerHandle() {
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_I)) {
		m_scene->FindGameObject("car")->Physics()->
			SetForce(m_scene->FindGameObject("car")->Physics()->GetForce() + Vector3(-2.f, 0.f, 0.f));
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_J)) {
		m_scene->FindGameObject("car")->Physics()->SetForce(m_scene->FindGameObject("car")->Physics()->GetForce() + Vector3(0.f, 0.f, 2.f));
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_K)) {
		m_scene->FindGameObject("car")->Physics()->SetForce(m_scene->FindGameObject("car")->Physics()->GetForce() + Vector3(2.f, 0.f, 0.f));
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_L)) {
		m_scene->FindGameObject("car")->Physics()->SetForce(m_scene->FindGameObject("car")->Physics()->GetForce() + Vector3(0.f, 0.f, -2.f));
	}

	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_T)) {
		m_scene->lightList.at(0).SetPosition(m_scene->lightList.at(0).GetPosition() + Vector3(-2.0f, 0, 0));
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_H)) {
		m_scene->lightList.at(0).SetPosition(m_scene->lightList.at(0).GetPosition() + Vector3(0, 0, 2.0f));
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_G)) {
		m_scene->lightList.at(0).SetPosition(m_scene->lightList.at(0).GetPosition() + Vector3(2.0f, 0, 0));
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_F)) {
		m_scene->lightList.at(0).SetPosition(m_scene->lightList.at(0).GetPosition() + Vector3(0, 0, -2.0f));
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_N)) {
		m_scene->lightList.at(0).SetPosition(m_scene->lightList.at(0).GetPosition() + Vector3(0, -2.0f,0 ));
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_M)) {
		m_scene->lightList.at(0).SetPosition(m_scene->lightList.at(0).GetPosition() + Vector3(0, 2.0f,0));
	}
}

void ActionHandler::Update(float dt) {
	ControllerHandle();
	//(m_scene->m_RootParticleList->GetChildren())[0]->SetSourcePosition(m_scene->FindGameObject("car")->Physics()->GetPosition());
}