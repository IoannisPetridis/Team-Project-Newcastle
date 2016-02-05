
#pragma once

#include <nclgl\Mesh.h>
#include <ncltech\Scene.h>
#include <ncltech\SimpleMeshObject.h>
#include <fmod.hpp>
#include <ncltech\Audio.h>

class MyScene : public Scene
{
public:
	MyScene(Window& window);
	~MyScene();

	bool InitialiseGL()	override;
	void RenderScene() override;
	void UpdateScene(float dt)  override;
	

	FMOD_RESULT result;
	FMOD::System *system2;

	FMOD::Sound *sound1, *sound2;

	FMOD::Channel   *channel1 = 0, *channel2 = 0;
	void            *extradriverdata = 0;
	bool             listenerflag = true;
	Audio audio;

	FMOD_VECTOR LastPosition;
	FMOD_VECTOR CameraPosition;
	FMOD_VECTOR CameraForward;
	FMOD_VECTOR CameraUp;
	FMOD_VECTOR CameraVelocity;
	



protected:
	GLuint				m_TargetTexture;
	GLuint				m_ThrowTex;

	SimpleMeshObject*	m_Sphere;
	SimpleMeshObject*	throw_S;
	SimpleMeshObject*	target;
	SimpleMeshObject*	goal;
	Plane*				plane;

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

	string filename;
	GameTimer engine_timer;
};