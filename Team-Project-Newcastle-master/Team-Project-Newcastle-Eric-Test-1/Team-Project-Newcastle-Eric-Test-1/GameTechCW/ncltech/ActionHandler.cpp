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
		m_scene->FindGameObject("car")->Physics()->SetPosition(m_scene->FindGameObject("car")->Physics()->GetPosition() + Vector3(-2.f, 0.f, 0.f));
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_J)) {
		m_scene->FindGameObject("car")->Physics()->SetPosition(m_scene->FindGameObject("car")->Physics()->GetPosition() + Vector3(0.f, 0.f, 2.f));
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_K)) {
		m_scene->FindGameObject("car")->Physics()->SetPosition(m_scene->FindGameObject("car")->Physics()->GetPosition() + Vector3(2.f, 0.f, 0.f));
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_L)) {
		m_scene->FindGameObject("car")->Physics()->SetPosition(m_scene->FindGameObject("car")->Physics()->GetPosition() + Vector3(0.f, 0.f, -2.f));
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_9)) {
		m_scene->FindGameObject("car")->Physics()->SetPosition(m_scene->FindGameObject("car")->Physics()->GetPosition() + Vector3(0.f, 2.f, 0.f));
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_0)) {
		m_scene->FindGameObject("car")->Physics()->SetPosition(m_scene->FindGameObject("car")->Physics()->GetPosition() + Vector3(0.f, -2.f, 0.f));
	}

	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_T)) {
		m_scene->lightList.at(0).SetPosition(m_scene->lightList.at(0).GetPosition() + Vector3(-2.0f, 0, 0));
		//m_scene->FindGameObject("light")->Physics()->SetPosition(m_scene->lightList.at(0).GetPosition());
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_H)) {
		m_scene->lightList.at(0).SetPosition(m_scene->lightList.at(0).GetPosition() + Vector3(0, 0, 2.0f));
		//m_scene->FindGameObject("light")->Physics()->SetPosition(m_scene->lightList.at(0).GetPosition());
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_G)) {
		m_scene->lightList.at(0).SetPosition(m_scene->lightList.at(0).GetPosition() + Vector3(2.0f, 0, 0));
		//m_scene->FindGameObject("light")->Physics()->SetPosition(m_scene->lightList.at(0).GetPosition());
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_F)) {
		m_scene->lightList.at(0).SetPosition(m_scene->lightList.at(0).GetPosition() + Vector3(0, 0, -2.0f));
		//m_scene->FindGameObject("light")->Physics()->SetPosition(m_scene->lightList.at(0).GetPosition());
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_N)) {
		m_scene->lightList.at(0).SetPosition(m_scene->lightList.at(0).GetPosition() + Vector3(0, -2.0f,0 ));
		//m_scene->FindGameObject("light")->Physics()->SetPosition(m_scene->lightList.at(0).GetPosition());
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_M)) {
		m_scene->lightList.at(0).SetPosition(m_scene->lightList.at(0).GetPosition() + Vector3(0, 2.0f,0));
		//m_scene->FindGameObject("light")->Physics()->SetPosition(m_scene->lightList.at(0).GetPosition());
	}
}

void ActionHandler::Update(float dt) {
	ControllerHandle();
	(m_scene->m_RootParticleList->GetChildren())[0]->SetSourcePosition(m_scene->FindGameObject("car")->Physics()->GetPosition());
}