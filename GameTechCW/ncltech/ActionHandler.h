#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "SimpleMeshObject.h"
#include "AssetsManager.h"
#include "../nclgl/Window.h"
#include "NCLDebug.h"
#include "Audio.h"

class ActionHandler : public TSingleton<ActionHandler> {
	friend class TSingleton < ActionHandler>;
public:
	ActionHandler();
	
	void SetDefaultScene(Scene* scene);

	void ControllerHandle_Force(SimpleMeshObject* P, KeyboardKeys key, Vector3 force, float& timer, bool AI);
	void ControllerHandle_Torque(SimpleMeshObject* P, KeyboardKeys key, Vector3 force, float& timer);
	void ControllerHandle_Ori(SimpleMeshObject* P, KeyboardKeys key, Vector3 Axis, float degree, bool AI);
	void ControllerHandle_Jump(SimpleMeshObject* P, KeyboardKeys key, bool AI);
	void Flip(SimpleMeshObject* P);
	
	//return 1 for blue scoring, 2 for red scoring
	int ScoreCheck();

	void AIUpdates();
	void SoloAIUpdates();
	void AIControllerTemp();
	void SoloAIControllerTemp();
	void AIPort();


	Scene* GetScene() const { return m_scene; }

	void Update(float dt);
	void ControlUpdate(int mode);

	void GravityGun();
	void RemoveForce();

	bool AIChoice;
	bool AIOffAbility;

	bool GameOver;
	void ResetGame(){

		AssetsManager::Player_1->Physics()->SetPosition(Vector3(10.f, 13.f, 10.f));
		AssetsManager::Player_1->Physics()->SetLinearVelocity(Vector3(0.f, 0.f, 0.f));
		AssetsManager::Player_1->Physics()->SetAngularVelocity(Vector3(0.f, 0.f, 0.f));
		AssetsManager::Player_1->Physics()->SetForce(Vector3(0.f, 0.f, 0.f));

	
		m_scene->m_RootGameObject->FindGameObject("ball")->Physics()->SetLinearVelocity(Vector3(0.f, 0.f, 0.f));
		m_scene->m_RootGameObject->FindGameObject("ball")->Physics()->SetAngularVelocity(Vector3(0.f, 0.f, 0.f));
		m_scene->m_RootGameObject->FindGameObject("ball")->Physics()->SetForce(Vector3(0.f, 0.f, 0.f));
		m_scene->m_RootGameObject->FindGameObject("ball")->Physics()->SetPosition(Vector3(0.0f, 13.0f, 0.0f));

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
		Gametimer = 25.0f;
		RedScore = 0;
		BlueScore = 0;
		PhysicsEngine::Instance()->SetPaused(false);

	}

protected:
	Scene* m_scene;
	float Gametimer;
	int BlueScore;
	int RedScore;
	
	float timer[3];
	float AAItimer[3];
	float NAItimer[3];
	float DAItimer[3];
	float SAItimer[3];

	bool Inair;
	bool doubleJump;


	GameTimer engine_timer;
};
