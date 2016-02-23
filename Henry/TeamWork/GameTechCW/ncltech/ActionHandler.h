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

	void ControllerHandle_Force(SimpleMeshObject* P, KeyboardKeys key, Vector3 force, float& timer, bool AI);
	void ControllerHandle_Torque(SimpleMeshObject* P, KeyboardKeys key, Vector3 force, float& timer);
	void ControllerHandle_Ori(SimpleMeshObject* P, KeyboardKeys key, Vector3 Axis, float degree, bool AI);
	void ControllerHandle_Jump(SimpleMeshObject* P, KeyboardKeys key);
	void Flip(SimpleMeshObject* P);
	
	//return 1 for blue scoring, 2 for red scoring
	int ScoreCheck();

	void AIUpdates();
	void AIControllerTemp();
	void AIPort();

	Scene* GetScene() const { return m_scene; }

	void Update(float dt);
	void ControlUpdate(int mode);

protected:
	Scene* m_scene;
	
	float timer[3];
	float AAItimer[3];
	float NAItimer[3];
	float DAItimer[3];

	bool Inair;
	bool doubleJump;

	GameTimer engine_timer;
};
