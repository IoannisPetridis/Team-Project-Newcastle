
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
#include "Audio.h"
#include "../../ncltech/GameObjectMag.h"

class GameObjectMag;

class MyScene : public Scene
{
	friend class GameObjectMag;
public:
	MyScene(Window& window);
	~MyScene();

	bool InitialiseGL()	override;
	void RenderScene() override;
	void UpdateScene(float dt)  override;

protected:
	GLuint				m_TargetTexture;
	GLuint				m_ThrowTex;

	SimpleMeshObject*	m_Sphere;
	SimpleMeshObject*	throw_S;
	SimpleMeshObject*	target;
	SimpleMeshObject*	goal;
	Plane*				plane;

	GameObjectMag* GOM;
	
	std::vector<Vector3> m_TrajectoryPoints;
	std::vector<string> LB_name;
	std::vector<string> LB_score;
	std::vector<GameObject*> subshapes;

	Vector3 Proj_dir;
	Vector3	Target_Pos;
	Vector3 GK_Pos;
	
	Vector3 planenormal;
	Vector3 GK_Init_Pos;

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



	FMOD_RESULT result;
	FMOD::System *system2;

	FMOD::Sound *sound1, *sound2 , *sound3;

	FMOD::Channel   *channel1 = 0, *channel2 = 0 , *channel3 = 0;
	void            *extradriverdata = 0;
	bool             listenerflag = true;
	

	FMOD_VECTOR LastPosition;
	FMOD_VECTOR CameraPosition;
	FMOD_VECTOR CameraForward;
	FMOD_VECTOR CameraUp;
	FMOD_VECTOR CameraVelocity;

	const int   INTERFACE_UPDATETIME = 50;      // 50ms update for interface
	const float DISTANCEFACTOR = 1.0f;

};