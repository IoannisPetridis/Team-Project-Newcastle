#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "SimpleMeshObject.h"
#include "AssetsManager.h"
#include "../nclgl/Window.h"
#include "NCLDebug.h"
#include "Audio.h"
#include "PowerUps.h"

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
	void ResetGame();

	int GetBluescore(){ return BlueScore; }
	int GetRedscore(){ return RedScore; }
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
	float powerupspawntimer = 0;

	bool Inair;
	bool doubleJump;


	GameTimer engine_timer;
};
