#include <nclgl/OBJMesh.h>
#include <ncltech\SimpleMeshObject.h>
#include <ncltech\PhysicsEngine.h>
#include <ncltech\AssetsManager.h>
#include <ncltech\NCLDebug.h>
#include <ncltech\DistanceConstraint.h>
#include <ncltech\CuboidCollisionShape.h>
#include <ncltech\SphereCollisionShape.h>
#include <ncltech\Scene.h>

#include "Player.h"

Player::Player(const std::string& name, Camera* cameraInstance) : SimpleMeshObject(name) {
	camera = cameraInstance;
}

void Player::OnUpdateObject(float dt) {
	Vector3 cameraMove = Vector3(0.0f, 0.0f, 0.0f);

	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_I)) {
		FindGameObject("car")->Physics()->SetForce(Vector3(-10.f, 0.f, 0.f));
		cameraMove = cameraMove + Vector3(0.1f, 0.0f, 0.0f);
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_J)) {
		FindGameObject("car")->Physics()->SetForce(Vector3(0.f, 0.f, 10.f));
		cameraMove = cameraMove + Vector3(0.0f, 0.0f, -0.1f);
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_K)) {
		FindGameObject("car")->Physics()->SetForce(Vector3(10.f, 0.f, 0.f));
		cameraMove = cameraMove + Vector3(-0.1f, 0.0f, 0.0f);
	}
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_L)) {
		FindGameObject("car")->Physics()->SetForce(Vector3(0.f, 0.f, -10.f));
		cameraMove = cameraMove + Vector3(0.0f, 0.0f, 0.1f);
	}

	camera->SetPosition();
}