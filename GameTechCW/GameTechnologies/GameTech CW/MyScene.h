
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

	////////////
	GameObjectMag* GOM;
	////////////

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