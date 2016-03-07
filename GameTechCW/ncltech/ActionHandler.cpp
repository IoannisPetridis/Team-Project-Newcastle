#pragma once
#include "ActionHandler.h"

ActionHandler::ActionHandler() {	
	timer[0] = -1.0f;
	timer[1] = -1.0f;
	timer[2] = 0.0f;

	NAItimer[0] = -1.0f;
	NAItimer[1] = -1.0f;
	NAItimer[2] = 0.0f;

	AAItimer[0] = -1.0f;
	AAItimer[1] = -1.0f;
	AAItimer[2] = 0.0f;

	DAItimer[0] = -1.0f;
	DAItimer[1] = -1.0f;
	DAItimer[2] = 0.0f;

	Gametimer = 70.0f;
	BlueScore = 0;
	RedScore = 0;

	Inair = false;
	doubleJump = false;

	GameOver = false;
}

int ActionHandler::ScoreCheck() {
	if (m_scene->m_RootGameObject->FindGameObject("ball")) {
		Vector3 pos = m_scene->m_RootGameObject->FindGameObject("ball")->Physics()->GetPosition();
		if ((pos.x < -200.0f) &&
			(pos.z > -50.0f && pos.z < 50.0f) &&
			(pos.y > 0.0f && pos.z < 40.0f)) {
			//NCLDebug::Log(Vector3(1.0f, 0.0f, 0.0f),
			//	"Red Score");

			RedScore++;

			m_scene->m_RootGameObject->FindGameObject("ball")
				->Physics()->SetPosition(Vector3(0.0f, 10.0f, 0.0f));

			FMOD_VECTOR pos = { 0.0f, 0.f, 0.f };
			Audio::AddSound(pos, pos, Audio::channel4, Audio::Goal, 1.0f);
			AssetsManager::Player_1->Physics()->SetPosition(Vector3(10.0f, 10.0f, 10.0f));

			return 1;
		}

		if ((pos.x > 200.0f) &&
			(pos.z > -50.0f && pos.z < 50.0f) &&
			(pos.y > 0.0f && pos.z < 40.0f)) {
			//NCLDebug::Log(Vector3(1.0f, 0.0f, 0.0f),
			//	"Blue Score");

			BlueScore++; 

			FMOD_VECTOR pos = { 0.0f, 0.f, 0.f };
			Audio::AddSound(pos, pos, Audio::channel4, Audio::Goal, 1.0f);
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

void ActionHandler::ControllerHandle_Force(SimpleMeshObject* P, KeyboardKeys key, Vector3 force, float& timer, bool AI) {
	engine_timer.GetTimedMS();
	if (Window::GetKeyboard()->KeyHeld(key) || AI) {
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
		&& timer > 0.0f && !AI) {
		//NCLDebug::Log(Vector3(1.0f, 1.0f, 0.0f), "enter");
		P->Physics()->SetForce(Vector3(0.0f, 0.0f, 0.0f));
		timer = -1.0f;
	}
}

void ActionHandler::ControllerHandle_Ori(SimpleMeshObject* P, KeyboardKeys key, Vector3 Axis, float degree, bool AI) {
	if (Window::GetKeyboard()->KeyHeld(key) || AI) {
		Quaternion rot = P->Physics()->GetOrientation() *
			Quaternion::AxisAngleToQuaterion(Axis, degree);
		P->Physics()->SetOrientation(rot);
	}
}

void ActionHandler::ControllerHandle_Jump(SimpleMeshObject* P, KeyboardKeys key) {
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
			P->Physics()->SetLinearVelocity(P->Physics()->GetLinearVelocity() + P->GetLeftNormal() * 10.0f);
			doubleJump = true;
		}
		else if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_D)) {
			P->Physics()->SetLinearVelocity(P->Physics()->GetLinearVelocity() + P->GetRightNormal() * 10.0f);
			doubleJump = true;
		}
		else if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_W)) {
			P->Physics()->SetLinearVelocity(P->Physics()->GetLinearVelocity() + P->GetFrontNormal() * 10.0f);
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

void ActionHandler::Flip(SimpleMeshObject *P) {
	float Top_factor = Vector3::Dot(P->GetTopNormal(), Vector3(0.0f, 1.0f, 0.0f));
	float Top_angle = acos(Top_factor) * 180.0f / PI;
	if (Top_angle >= 90.0f) {
		P->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0.0f, 90.0f, 0.0f));
	}
}

void ActionHandler::Update(float dt) {
	
	if (Gametimer >= 0) {
		Gametimer -= dt;
	}
	if (Gametimer < 0) {
		Gametimer = 0.0f;
		GameOver = true;
		PhysicsEngine::Instance()->SetPaused(true);
		Audio::channel1->setPaused(false);
		NCLDebug::DrawTextClipSpace(Vector4(0.0f, 0.0f, 0.0f, 1.0f),
			32.0f,
			"Game Over!",
			TEXTALIGN_LEFT,
			Vector4(1.0, 1.0, 1.0, 1.0));

	}

	{
		AssetsManager::Player_1->NormalCal();

		Flip(AssetsManager::Player_1);
		//Keyboard Control
		ControllerHandle_Force(AssetsManager::Player_1, KEYBOARD_W,
		AssetsManager::Player_1->front_normal * 150.0f, timer[0], 0);

		ControllerHandle_Ori(AssetsManager::Player_1, KEYBOARD_A,
			Vector3(0.0f, 1.0f, 0.0f), 2.0f, 0);

		ControllerHandle_Force(AssetsManager::Player_1, KEYBOARD_S,
			AssetsManager::Player_1->Rear_normal * 150.0f, timer[1], 0);

		ControllerHandle_Ori(AssetsManager::Player_1, KEYBOARD_D,
			Vector3(0.0f, 1.0f, 0.0f), -2.0f, 0);

		ControllerHandle_Jump(AssetsManager::Player_1, KEYBOARD_SPACE);
	}

	//AI

	AIUpdates();
	

	//spawn partical
	(m_scene->m_RootParticleList->GetChildren())[0]->SetDirection(AssetsManager::Player_1->front_normal);
	(m_scene->m_RootParticleList->GetChildren())[0]->SetSourcePosition(AssetsManager::Player_1->Physics()->GetPosition() +
		AssetsManager::Player_1->Physics()->GetOrientation().ToMatrix3() * Vector3(0, 0, 1));

	Window::GetWindow().ShowOSPointer(false);
	Window::GetWindow().LockMouseToWindow(true);


	//HUD stats

	if (!PhysicsEngine::Instance()->GetDebug()){
		NCLDebug::DrawTextClipSpace(Vector4(-0.75f, 0.9f, 0.0f, 1.0f),
			32.0f,
			"Blue Team Score : " + std::to_string(BlueScore),
			TEXTALIGN_LEFT,
			Vector4(1.0, 1.0, 1.0, 1.0));
		NCLDebug::DrawTextClipSpace(Vector4(-0.1f, 0.9f, 0.0f, 1.0f),
			32.0f,
			std::to_string(Gametimer).substr(0, 5),
			TEXTALIGN_LEFT,
			Vector4(1.0, 1.0, 1.0, 1.0));
		NCLDebug::DrawTextClipSpace(Vector4(0.15f, 0.9f, 0.0f, 1.0f),
			32.0f,
			"Red Team Score : " + std::to_string(RedScore),
			TEXTALIGN_LEFT,
			Vector4(1.0, 1.0, 1.0, 1.0));
	}

}

void ActionHandler::AIUpdates() {
	AssetsManager::DefensiveAI->UpdateAI();
	AssetsManager::AggressiveAI->UpdateAI();
	AssetsManager::NeutralAI->UpdateAI();
	AIControllerTemp();
}

void ActionHandler::AIControllerTemp() {
	{
		if (AssetsManager::NeutralAI->left) {
			ControllerHandle_Ori(AssetsManager::NeutralAI, KEYBOARD_A, Vector3(0.0f, 1.0f, 0.0f), 2.0f, 1);
		}

		if (AssetsManager::NeutralAI->right) {
			ControllerHandle_Ori(AssetsManager::NeutralAI, KEYBOARD_D, Vector3(0.0f, 1.0f, 0.0f), -2.0f, 1);
		}

		if (AssetsManager::NeutralAI->forward) {
			ControllerHandle_Force(AssetsManager::NeutralAI, KEYBOARD_W, AssetsManager::NeutralAI->GetFrontNormal() * 150.0f, NAItimer[0], 1);
		}

		if (AssetsManager::NeutralAI->reverse) {
			ControllerHandle_Force(AssetsManager::NeutralAI, KEYBOARD_S, AssetsManager::NeutralAI->GetRearNormal() * 150.0f, NAItimer[1], 1);
		}

		if (!AssetsManager::NeutralAI->forward && !AssetsManager::NeutralAI->reverse) {
			AssetsManager::NeutralAI->Physics()->SetForce(Vector3(0.0f, 0.0f, 0.0f));
		}
	}

	{
		if (AssetsManager::DefensiveAI->left) {
			ControllerHandle_Ori(AssetsManager::DefensiveAI, KEYBOARD_A, Vector3(0.0f, 1.0f, 0.0f), 2.0f, 1);
		}

		if (AssetsManager::DefensiveAI->right) {
			ControllerHandle_Ori(AssetsManager::DefensiveAI, KEYBOARD_D, Vector3(0.0f, 1.0f, 0.0f), -2.0f, 1);
		}

		if (AssetsManager::DefensiveAI->forward) {
			ControllerHandle_Force(AssetsManager::DefensiveAI, KEYBOARD_W, AssetsManager::DefensiveAI->GetFrontNormal() * 150.0f, DAItimer[0], 1);
		}

		if (AssetsManager::DefensiveAI->reverse) {
			ControllerHandle_Force(AssetsManager::DefensiveAI, KEYBOARD_S, AssetsManager::DefensiveAI->GetRearNormal() * 150.0f, DAItimer[1], 1);
		}

		if (!AssetsManager::DefensiveAI->forward && !AssetsManager::DefensiveAI->reverse) {
			AssetsManager::DefensiveAI->Physics()->SetForce(Vector3(0.0f, 0.0f, 0.0f));
		}
	}

	{
		if (AssetsManager::AggressiveAI->left) {
			ControllerHandle_Ori(AssetsManager::AggressiveAI, KEYBOARD_A, Vector3(0.0f, 1.0f, 0.0f), 2.0f, 1);
		}

		if (AssetsManager::AggressiveAI->right) {
			ControllerHandle_Ori(AssetsManager::AggressiveAI, KEYBOARD_D, Vector3(0.0f, 1.0f, 0.0f), -2.0f, 1);
		}

		if (AssetsManager::AggressiveAI->forward) {
			ControllerHandle_Force(AssetsManager::AggressiveAI, KEYBOARD_W, AssetsManager::AggressiveAI->GetFrontNormal() * 150.0f, AAItimer[0], 1);
		}

		if (AssetsManager::AggressiveAI->reverse) {
			ControllerHandle_Force(AssetsManager::AggressiveAI, KEYBOARD_S, AssetsManager::AggressiveAI->GetRearNormal() * 150.0f, AAItimer[1], 1);
		}

		if (!AssetsManager::AggressiveAI->forward && !AssetsManager::AggressiveAI->reverse) {
			AssetsManager::AggressiveAI->Physics()->SetForce(Vector3(0.0f, 0.0f, 0.0f));
		}
	}
}
