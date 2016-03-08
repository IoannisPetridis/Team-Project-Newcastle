
#pragma once
//#include <ncltech\GameObject.h>
//#include <ncltech\AssetsManager.h>
//#include <nclgl\Mesh.h>
//#include <ncltech\Scene.h>
//#include <ncltech\SimpleMeshObject.h>
//#include <nclgl/OBJMesh.h>
//#include <ncltech\PhysicsEngine.h>
//#include <ncltech\AssetsManager.h>
//#include <ncltech\NCLDebug.h>
//#include <ncltech\CollisionShape.h>
//#include <ncltech\Constraint.h>
//#include <ncltech\DistanceConstraint.h>
//#include <ncltech\SphereCollisionShape.h>
//#include <ncltech\CuboidCollisionShape.h>
//#include <ncltech\CollisionDetection.h>
#include <FMOD\inc\fmod.hpp>
#include "../../ncltech/GameObjectMag.h"
#include <ncltech\Audio.h>
#include <ncltech\PowerUps.h>

class GameObjectMag;

class MyScene : public Scene
{
	friend class GameObjectMag;
public:
	MyScene(Window& window, GameObjectMag* gom);
	~MyScene();

	bool InitialiseGL()	override;
	void RenderScene() override;
	void UpdateScene(float dt)  override;

	static bool AbilityUsed;
	static int counter;
	static int abilitycounter;

protected:	
	GameObjectMag*		GOM;
	Vector3 Proj_dir;

	int T_counter;
	int Str_c;
	int DebugMode;
	int diff;

	int score;
	int ballnum;
	float friction;
	float start_strong;
	float timer;
	
	bool ai_state;
	bool ai_toggle;
	bool travese_toggle;
	bool cooldown;
	bool gameover;
	bool Camerefix;

	string filename;
	GameTimer engine_timer;
	GameTimer Audio_Timer;

	FMOD_VECTOR CarPosition;
	FMOD_VECTOR CarVelocity;

	float damage = 0.0f;
	float time;
};