#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "SimpleMeshObject.h"
#include "AssetsManager.h"
#include "../nclgl/Window.h"
#include "NCLDebug.h"

class ActionHandler : public TSingleton<ActionHandler> {
	friend class TSingleton < ActionHandler>;
public:
	ActionHandler();
	
	void SetDefaultScene(Scene* scene);

	void ControllerHandle_Force(Player* P, KeyboardKeys key, Vector3 force, float& timer);
	void ControllerHandle_Torque(Player* P, KeyboardKeys key, Vector3 force, float& timer);
	void ControllerHandle_Ori(Player* P, KeyboardKeys key, Vector3 Axis, float degree);
	void ControllerHandle_Jump(Player* P, KeyboardKeys key);
	void Flip(Player* P);
	
	void AIPort();

	Scene* GetScene() const { return m_scene; }

	void Update(float dt);
	void ControlUpdate(int mode);

protected:
	Scene* m_scene;
	
	float timer[3];

	bool Inair;
	bool doubleJump;

	GameTimer engine_timer;
};
