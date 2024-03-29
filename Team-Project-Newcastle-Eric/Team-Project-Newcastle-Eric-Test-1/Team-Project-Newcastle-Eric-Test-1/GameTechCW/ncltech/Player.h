#pragma once
#include "../nclgl/Camera.h"
#include "SimpleMeshObject.h"
#include "AssetsManager.h"
#include "Scene.h"

class Player : public SimpleMeshObject {
	friend class ActionHandler;
public:
	Player(const std::string& name);
	~Player();

	void CameraControl();
	void IDPlayerFaces();
	void RotateLock();

	void Replay();
	void TronEffect();
	void CollisionTrack();

	void NormalCal();

	Vector3 GetCameraDir() const { return Camera_Dir; }

//Initialization data
protected:
	Camera* P_camera;
	Vector3 Camera_Dir;

	Vector3 front_normal;
	Vector3 Rear_normal;
	Vector3 Left_normal;
	Vector3 Right_normal;
	Vector3 Top_normal;
	Vector3 Bottom_normal;

	void	OnUpdateObject(float dt) override {};

//utility
protected:
	float DisWalltoPlayer(GameObject* wall);

//Camera Control Toggle
protected:
	Vector3 Proj_dir;
	float FT_Pitch; //first touch pitch
	float FT_dis;	//first touch distance
	int FT_Timer;

	void CameraFollowPlayerFunc();
	bool CameraFollowPlayer = false;

	void CameraTrackObjFunc(GameObject* go);
	bool CameraTrackObj = false;

};