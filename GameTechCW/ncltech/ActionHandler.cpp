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

	SAItimer[0] = -1.0f;
	SAItimer[1] = -1.0f;
	SAItimer[2] = 0.0f;

	Gametimer = 120.0f;
	BlueScore = 0;
	RedScore = 0;

	AIChoice = false; // false = 1, true = 3

	Inair = false;
	doubleJump = false;

	GameOver = false;
}

//moves ball to player's location
void ActionHandler::GravityGun(){

	Vector3 ballposition, playerposition, directionvector;
	ballposition = m_scene->m_RootGameObject->FindGameObject("ball")->Physics()->GetPosition();
	playerposition = m_scene->m_RootGameObject->FindGameObject("car")->Physics()->GetPosition();

	directionvector = playerposition - ballposition;
	directionvector.Normalise();

	m_scene->m_RootGameObject->FindGameObject("ball")->Physics()->SetForce(directionvector * 2);
}

//sets force on ball to 0
void ActionHandler::RemoveForce(){
	m_scene->m_RootGameObject->FindGameObject("ball")->Physics()->SetForce(Vector3(0.0f, 0.0f, 0.0f));
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
			FMOD_VECTOR pos = { 0.0f, 0.f, 0.f };
			Audio::AddSound(pos, pos, Audio::channel4, Audio::Goal, 1.0f);

			GameObject* ball = m_scene->m_RootGameObject->FindGameObject("ball");
			ball->Physics()->SetPosition(Vector3(0.0f, 4.5f, 0.0f));
			ball->Physics()->SetLinearVelocity(Vector3(0.0f, 0.0f, 0.0f));
			ball->Physics()->SetAngularVelocity(Vector3(0.0f, 0.0f, 0.0f));
			AssetsManager::Player_1->Physics()->SetPosition(Vector3(-40.0f, 2.0f, 0.0f));
			AssetsManager::Player_1->Physics()->SetLinearVelocity(Vector3(0.0f, 0.0f, 0.0f));
			AssetsManager::Player_1->Physics()->SetAngularVelocity(Vector3(0.0f, 0.0f, 0.0f));

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

			GameObject* ball = m_scene->m_RootGameObject->FindGameObject("ball");
			ball->Physics()->SetPosition(Vector3(0.0f, 4.5f, 0.0f));
			ball->Physics()->SetLinearVelocity(Vector3(0.0f, 0.0f, 0.0f));
			ball->Physics()->SetAngularVelocity(Vector3(0.0f, 0.0f, 0.0f));
			AssetsManager::Player_1->Physics()->SetPosition(Vector3(-40.0f, 2.0f, 0.0f));
			AssetsManager::Player_1->Physics()->SetLinearVelocity(Vector3(0.0f, 0.0f, 0.0f));
			AssetsManager::Player_1->Physics()->SetAngularVelocity(Vector3(0.0f, 0.0f, 0.0f));
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
		P->Physics()->SetForce(force * timer);

		force.Normalise();

	}
	if (!Window::GetKeyboard()->KeyHeld(key)
		&& timer > 0.0f && !AI) {
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

void ActionHandler::ControllerHandle_Jump(SimpleMeshObject* P, KeyboardKeys key, bool AI) {
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
		if (Window::GetKeyboard()->KeyTriggered(key) || AI) {
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
	
	if (Gametimer > 0 && !PhysicsEngine::Instance()->IsPaused()) {
		Gametimer -= dt;
		powerupspawntimer += dt;
	}
	if (Gametimer <= 0) {
		Gametimer = 0.0f;
		GameOver = true;
		PhysicsEngine::Instance()->SetPaused(true);
		Audio::AddSound({ 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, Audio::channel1, Audio::End, 5);
	}
	if (powerupspawntimer > 10){

		PowerUps::RandomPowerUpPosition(AssetsManager::PowerUpBox1);
		PowerUps::RandomPowerUpPosition(AssetsManager::PowerUpBox2);
		PowerUps::RandomPowerUpPosition(AssetsManager::PowerUpBox3);
		PowerUps::RandomPowerUpPosition(AssetsManager::PowerUpBox4);
		PowerUps::RandomPowerUpPosition(AssetsManager::PowerUpBox5);

		powerupspawntimer = 0;
	}

	{
		AssetsManager::Player_1->NormalCal();

		Flip(AssetsManager::Player_1);
		//Keyboard Control
		ControllerHandle_Force(AssetsManager::Player_1, KEYBOARD_W,
		AssetsManager::Player_1->front_normal * 250.0f, timer[0], 0);

		ControllerHandle_Ori(AssetsManager::Player_1, KEYBOARD_A,
			Vector3(0.0f, 1.0f, 0.0f), 2.0f, 0);

		ControllerHandle_Force(AssetsManager::Player_1, KEYBOARD_S,
			AssetsManager::Player_1->Rear_normal * 150.0f, timer[1], 0);

		ControllerHandle_Ori(AssetsManager::Player_1, KEYBOARD_D,
			Vector3(0.0f, 1.0f, 0.0f), -2.0f, 0);

		ControllerHandle_Jump(AssetsManager::Player_1, KEYBOARD_SPACE, 0);
	}

	//AI
	if (AIChoice) {
		if (!AIOffAbility) {
			AIUpdates();
		}
		else {
			AssetsManager::DefensiveAI->Physics()->SetForce(Vector3(0.0f, 0.0f, 0.0f));
			AssetsManager::AggressiveAI->Physics()->SetForce(Vector3(0.0f, 0.0f, 0.0f));
			AssetsManager::NeutralAI->Physics()->SetForce(Vector3(0.0f, 0.0f, 0.0f));
		}
	}

	else {
		if (!AIOffAbility) {
			SoloAIUpdates();
		}
		else {
			AssetsManager::SoloAI->Physics()->SetForce(Vector3(0.0f, 0.0f, 0.0f));
		}
	}
	
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

		float speed = AssetsManager::Player_1->Physics()->GetLinearVelocity().Length();

		NCLDebug::DrawTextClipSpace(Vector4(-0.9f, -0.9f, 0.0f, 1.0f),
			26.0f,
			"Speed : " + std::to_string(speed).substr(0, 5),
			TEXTALIGN_LEFT,
			Vector4(1.0, 1.0, 1.0, 1.0));

		NCLDebug::DrawTextClipSpace(Vector4(0.5f, -0.9f, 0.0f, 1.0f),
			26.0f,
			"PowerUp : " + AssetsManager::Player_1->GetPowerUpState(),
			TEXTALIGN_LEFT,
			Vector4(1.0, 1.0, 1.0, 1.0));
	}

}


//ai every frame updates for 3 ai;'s
void ActionHandler::AIUpdates() {
	AssetsManager::DefensiveAI->UpdateAI();
	AssetsManager::AggressiveAI->UpdateAI();
	AssetsManager::NeutralAI->UpdateAI();
	AIControllerTemp();
}
//ai every frame updates for 1 ai;'s
void ActionHandler::SoloAIUpdates() {
	AssetsManager::SoloAI->UpdateAI();
	SoloAIControllerTemp();
}

//temporary controller for ai's to call the same functions as control the player
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

		if (AssetsManager::NeutralAI->jump) {
			ControllerHandle_Jump(AssetsManager::NeutralAI, KEYBOARD_SPACE, 1);
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

	if (AssetsManager::DefensiveAI->jump) {
		ControllerHandle_Jump(AssetsManager::DefensiveAI, KEYBOARD_SPACE, 1);
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


//temporary function to call player controlelr methods to move the solo aqi
void ActionHandler::SoloAIControllerTemp() {
	{
		if (AssetsManager::SoloAI->left) {
			ControllerHandle_Ori(AssetsManager::SoloAI, KEYBOARD_A, Vector3(0.0f, 1.0f, 0.0f), 2.0f, 1);
		}

		if (AssetsManager::SoloAI->right) {
			ControllerHandle_Ori(AssetsManager::SoloAI, KEYBOARD_D, Vector3(0.0f, 1.0f, 0.0f), -2.0f, 1);
		}

		if (AssetsManager::SoloAI->forward) {
			ControllerHandle_Force(AssetsManager::SoloAI, KEYBOARD_W, AssetsManager::SoloAI->GetFrontNormal() * 150.0f, SAItimer[0], 1);
		}

		if (AssetsManager::SoloAI->reverse) {
			ControllerHandle_Force(AssetsManager::SoloAI, KEYBOARD_S, AssetsManager::SoloAI->GetRearNormal() * 150.0f, SAItimer[1], 1);
		}

		if (AssetsManager::SoloAI->jump) {
			ControllerHandle_Jump(AssetsManager::SoloAI, KEYBOARD_SPACE, 1);
		}

		if (!AssetsManager::SoloAI->forward && !AssetsManager::SoloAI->reverse) {
			AssetsManager::SoloAI->Physics()->SetForce(Vector3(0.0f, 0.0f, 0.0f));
		}
	}
}

void ActionHandler::ResetGame(){

		AssetsManager::Player_1->Physics()->SetPosition(Vector3(10.f, 13.f, 10.f));
		AssetsManager::Player_1->Physics()->SetLinearVelocity(Vector3(0.f, 0.f, 0.f));
		AssetsManager::Player_1->Physics()->SetAngularVelocity(Vector3(0.f, 0.f, 0.f));
		AssetsManager::Player_1->Physics()->SetForce(Vector3(0.f, 0.f, 0.f));


		m_scene->m_RootGameObject->FindGameObject("ball")->Physics()->SetLinearVelocity(Vector3(0.f, 0.f, 0.f));
		m_scene->m_RootGameObject->FindGameObject("ball")->Physics()->SetAngularVelocity(Vector3(0.f, 0.f, 0.f));
		m_scene->m_RootGameObject->FindGameObject("ball")->Physics()->SetForce(Vector3(0.f, 0.f, 0.f));
		m_scene->m_RootGameObject->FindGameObject("ball")->Physics()->SetPosition(Vector3(0.0f, 13.0f, 0.0f));

		PowerUps::RandomPowerUpPosition(AssetsManager::PowerUpBox1);
		PowerUps::RandomPowerUpPosition(AssetsManager::PowerUpBox2);
		PowerUps::RandomPowerUpPosition(AssetsManager::PowerUpBox3);
		PowerUps::RandomPowerUpPosition(AssetsManager::PowerUpBox4);
		PowerUps::RandomPowerUpPosition(AssetsManager::PowerUpBox5);

		powerupspawntimer = 0;

		if (AIChoice){


			AssetsManager::NeutralAI->Physics()->SetLinearVelocity(Vector3(0.f, 0.f, 0.f));
			AssetsManager::NeutralAI->Physics()->SetAngularVelocity(Vector3(0.f, 0.f, 0.f));
			AssetsManager::NeutralAI->Physics()->SetForce(Vector3(0.f, 0.f, 0.f));
			AssetsManager::NeutralAI->Physics()->SetPosition(Vector3(100.0f, 12.0f, 0.0f));


			AssetsManager::DefensiveAI->Physics()->SetLinearVelocity(Vector3(0.f, 0.f, 0.f));
			AssetsManager::DefensiveAI->Physics()->SetAngularVelocity(Vector3(0.f, 0.f, 0.f));
			AssetsManager::DefensiveAI->Physics()->SetForce(Vector3(0.f, 0.f, 0.f));
			AssetsManager::DefensiveAI->Physics()->SetPosition(Vector3(180.0f, 12.0f, 0.0f));


			AssetsManager::AggressiveAI->Physics()->SetLinearVelocity(Vector3(0.f, 0.f, 0.f));
			AssetsManager::AggressiveAI->Physics()->SetAngularVelocity(Vector3(0.f, 0.f, 0.f));
			AssetsManager::AggressiveAI->Physics()->SetForce(Vector3(0.f, 0.f, 0.f));
			AssetsManager::AggressiveAI->Physics()->SetPosition(Vector3(40.0f, 12.0f, 0.0f));

		}
		else{

			AssetsManager::SoloAI->Physics()->SetLinearVelocity(Vector3(0.f, 0.f, 0.f));
			AssetsManager::SoloAI->Physics()->SetAngularVelocity(Vector3(0.f, 0.f, 0.f));
			AssetsManager::SoloAI->Physics()->SetForce(Vector3(0.f, 0.f, 0.f));
			AssetsManager::SoloAI->Physics()->SetPosition(Vector3(30.0f, 15.0f, 60.0f));

		}
		Gametimer = 120.0f;
		RedScore = 0;
		BlueScore = 0;
		PhysicsEngine::Instance()->SetPaused(false);

}