#pragma once
#include "ActionHandler.h"


//Player::Player(const std::string& name) : SimpleMeshObject(name) {}


void ActionHandler::SetDefaultScene(Scene* scene) {
	m_scene = scene;
}

void ActionHandler::ControllerHandle() {

}

void ActionHandler::Update(float dt) {
	ControllerHandle();
}