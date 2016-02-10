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
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_SPACE)) {
		m_scene->FindGameObject("car")->Physics()->SetForce(m_scene->FindGameObject("car")->Physics()->GetForce() + Vector3(0.f, 4.f, 0.f));
	}
}

void ActionHandler::Update(float dt) {
	ControllerHandle();
	(m_scene->m_RootParticleList->GetChildren())[0]->SetSourcePosition(m_scene->FindGameObject("car")->Physics()->GetPosition());

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_2)) {
		m_scene->FindGameObject("car")->Physics()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		m_scene->FindGameObject("car")->Physics()->SetForce(Vector3(0.0f, 0.0f, 0.0f));
		m_scene->FindGameObject("car")->Physics()->SetLinearVelocity(Vector3(0.0f, 0.0f, 0.0f));
	}

}