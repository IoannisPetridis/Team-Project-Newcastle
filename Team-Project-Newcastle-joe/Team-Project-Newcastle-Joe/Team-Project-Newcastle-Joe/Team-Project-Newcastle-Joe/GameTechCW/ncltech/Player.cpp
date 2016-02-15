#pragma once
#include "Player.h"
#include "NCLDebug.h"
#include "CollisionDetection.h"
#include "Hull.h"
#include "PhysicsEngine.h"

#define PI 3.1415926535897932f

Player::Player(const std::string& name) : 
SimpleMeshObject(name), FT_Timer(0)
{
	front_normal = this->Physics()->GetWorldSpaceTransform() * Vector3(0.0f, 0.0f, -1.0f);
	front_normal.Normalise();
	Rear_normal = this->Physics()->GetWorldSpaceTransform() * Vector3(0.0f, 0.0f, 1.0f);
	Rear_normal.Normalise();
	Left_normal = this->Physics()->GetWorldSpaceTransform() * Vector3(-1.0f, 0.0f, 0.0f);
	Left_normal.Normalise();
	Right_normal = this->Physics()->GetWorldSpaceTransform() * Vector3(1.0f, 0.0f, 0.0f);
	Right_normal.Normalise();
	Top_normal = this->Physics()->GetWorldSpaceTransform() * Vector3(0.0f, 1.0f, 0.0f);
	Top_normal.Normalise();
	Bottom_normal = this->Physics()->GetWorldSpaceTransform() * Vector3(0.0f, -1.0f, 0.0f);
	Bottom_normal.Normalise();
}

void Player::NormalCal() {
	front_normal = this->Physics()->GetOrientation().ToMatrix3() * Vector3(0.0f, 0.0f, -1.0f);
	front_normal.Normalise();
	Rear_normal = this->Physics()->GetOrientation().ToMatrix3() * Vector3(0.0f, 0.0f, 1.0f);
	Rear_normal.Normalise();
	Left_normal = this->Physics()->GetOrientation().ToMatrix3() * Vector3(-1.0f, 0.0f, 0.0f);
	Left_normal.Normalise();
	Right_normal = this->Physics()->GetOrientation().ToMatrix3() * Vector3(1.0f, 0.0f, 0.0f);
	Right_normal.Normalise();
	Top_normal = this->Physics()->GetOrientation().ToMatrix3() * Vector3(0.0f, 1.0f, 0.0f);
	Top_normal.Normalise();
	Bottom_normal = this->Physics()->GetOrientation().ToMatrix3() * Vector3(0.0f, -1.0f, 0.0f);
	Bottom_normal.Normalise();
}

void Player::CameraControl() {
	P_camera = m_Scene->m_Camera;

	Proj_dir.x = -sin(P_camera->GetYaw() * PI / 180.0f);
	Proj_dir.z = -cos(P_camera->GetYaw() * PI / 180.0f);
	Proj_dir.y = sin(P_camera->GetPitch() * PI / 180.0f);
	Proj_dir.Normalise();

	Camera_Dir = Proj_dir;

	//Toggles
	{
		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_1)) {
			CameraFollowPlayer = !CameraFollowPlayer;
		}
		if (CameraFollowPlayer) CameraFollowPlayerFunc();

		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_2)) {
			CameraTrackObj = !CameraTrackObj;
		}
		if (CameraTrackObj) CameraTrackObjFunc(m_Scene->m_RootGameObject->FindGameObject("ball"));
	}

	//Camera Penetration Control
	{
		Vector3 Camera_Pos = P_camera->GetPosition();

		float dis_1 = DisWalltoPlayer(m_Scene->m_RootGameObject->FindGameObject("ground"));
		if (dis_1 < 0.4f) {
			if (P_camera->GetPitch() > 2.0f) P_camera->SetPitch(2.0f);
		}

		//along the -Z axis
		float dis_2 = DisWalltoPlayer(m_Scene->m_RootGameObject->FindGameObject("ground_right_b"));
		if (dis_2 < 5.0f) {
			float dir_z = Vector3::Dot(Proj_dir, Vector3(0.0f, 0.0f, -1.0f));
			float dir_x = Vector3::Dot(Proj_dir, Vector3(1.0f, 0.0f, 0.0f));
			if (dir_z >= -0.25) {
				if (P_camera->GetPitch() > 30.0f) P_camera->SetPitch(30.0f);
					P_camera->SetPosition(this->Physics()->GetPosition()
					- (Proj_dir * 10.0f));
			}
			else {
				if (dir_x >= 0) 
				P_camera->SetPosition(this->Physics()->GetPosition() 
				- (Proj_dir * dis_2) + Vector3(0.0f, 2.0f, -3.0f));
				else
				P_camera->SetPosition(this->Physics()->GetPosition()
				- (Proj_dir * dis_2) + Vector3(0.0f, 2.0f, -3.0f));
			}
		}	
		
		//along the Z axis
		float dis_3 = DisWalltoPlayer(m_Scene->m_RootGameObject->FindGameObject("ground_left_b"));
		if (dis_3 < 4.0f) { 
			float dir_z = Vector3::Dot(Proj_dir, Vector3(0.0f, 0.0f, 1.0f));
			float dir_x = Vector3::Dot(Proj_dir, Vector3(1.0f, 0.0f, 0.0f));
			if (dir_z >= 0)
			{
				if (dir_x >= 0) 
				P_camera->SetPosition(this->Physics()->GetPosition()
				- (Proj_dir * dis_3) + Vector3(-4.0f, 2.0f, -3.0f));
				else 
				P_camera->SetPosition(this->Physics()->GetPosition()
				- (Proj_dir * dis_3) + Vector3(4.0f, 2.0f, -3.0f));
			}
			else {
				if (dir_x >= 0)
				P_camera->SetPosition(this->Physics()->GetPosition()
				- (Proj_dir * dis_3) + Vector3(-4.0f, 2.0f, 3.0f));
				else
				P_camera->SetPosition(this->Physics()->GetPosition()
				- (Proj_dir * dis_3) + Vector3(4.0f, 2.0f, 3.0f));
			}
		}
		
		//along the X axis
		float dis_4 = DisWalltoPlayer(m_Scene->m_RootGameObject->FindGameObject("ground_front_b"));
		if (dis_4 < 4.0f) {
			float dir_4 = Vector3::Dot(Proj_dir, Vector3(1.0f, 0.0f, 0.0f));
			if (dir_4 >= 0) P_camera->SetPosition(this->Physics()->GetPosition()
				- (Proj_dir * 5.0f) + Vector3(-3.0f, 2.0f, 0.0f));
			else {
				P_camera->SetPosition(this->Physics()->GetPosition()
					- (Proj_dir * dis_4) + Vector3(3.0f, 2.0f, 1.0f));
			}
		}

		//along the -X axis
		float dis_5 = DisWalltoPlayer(m_Scene->m_RootGameObject->FindGameObject("ground_back_b"));
		float lenght_5 = (P_camera->GetPosition() - this->Physics()->GetPosition()).Length() - 1.0f;
		if (dis_5 < 4.0f) {
			float dir_5 = Vector3::Dot(Proj_dir, Vector3(-1.0f, 0.0f, 0.0f));
			if (dir_5 >= 0) P_camera->SetPosition(this->Physics()->GetPosition()
				- (Proj_dir * 5.0f) + Vector3(3.0f, 2.0f, 0.0f));
			else {
				P_camera->SetPosition(this->Physics()->GetPosition()
					- (Proj_dir * dis_5) + Vector3(-3.0f, 2.0f, 1.0f));
			}
		}
	}
}

void Player::CameraTrackObjFunc(GameObject* go) {
	float yaw;
	float Xaxis;
	float Zaxis;

	//GOTemp only used in certain scope 
	AssetsManager::GOTemp = go;
	Vector3 ball_pos = AssetsManager::GOTemp->Physics()->GetPosition();
	Vector3 Cam_pos = P_camera->GetPosition();

	Vector3 dir = (ball_pos - Cam_pos);
	dir.Normalise();

	{//Ball tracking
		float offset = 0.0f;
		float pitch = asin(dir.y) * 180.0f / PI;

		Xaxis = Vector3::Dot(dir, Vector3(0.0f, 0.0f, -1.0f));
		Zaxis = Vector3::Dot(dir, Vector3(1.0f, 0.0f, 0.0f));

		if (dir.y > 1.0f) offset = 0.7f;
		else offset = 0.3f;
		
		if (dir.x < offset && dir.x > -offset) {
			yaw = acos(Zaxis) * 180.0f / PI;
			if (dir.z <= 0.0f) {
				if (yaw >= 90.0f) yaw = yaw - 90.0f;
				else yaw = 270.0f + yaw;
			}
			else {
				if (yaw >= 90) yaw = 270.0f - yaw;
				else yaw = 270.0f - yaw;
			}
		}
		else {
			yaw = acos(Xaxis) * 180.0f / PI;
			if (dir.x <= 0.0f) yaw = yaw;
			else yaw = 360.0f - yaw;
		}
		
		//reason to calculate second axis is to cancel the value deviation when dir.x is 
		//extremly small so that there is no enough presicion to accurately accommodate
		//the area between -0.001 < dir.x < 0.001

		P_camera->SetYaw(yaw);
		P_camera->SetPitch(pitch);
	}
}

void Player::CameraFollowPlayerFunc() {
	float speed = this->Physics()->GetLinearVelocity().Length();
	float disfromballtoPlayer;

	AssetsManager::GOTemp = m_Scene->m_RootGameObject->FindGameObject("ball");
	Vector3 ball_pos = AssetsManager::GOTemp->Physics()->GetPosition();
	Vector3 Player_pos = this->Physics()->GetPosition();

	Vector3 dir = (ball_pos - Player_pos);

	disfromballtoPlayer = dir.Length();

	P_camera->SetPosition(this->Physics()->GetPosition() -
		Proj_dir * max(speed * 0.3f, 7.0f) + Vector3(0.0f, 
		max(disfromballtoPlayer / 100.0f, 2.0f), 0.0f) - (Proj_dir * 3.0f));

	//for (auto& m : PhysicsEngine::Instance()->GetCollisionPair_Ground()) {
	//	if (m.objectA == AssetsManager::Camera_Entity->Physics() ||
	//		m.objectB == AssetsManager::Camera_Entity->Physics()) {
	//		FT_Pitch = P_camera->GetPitch();
	//		FT_dis = (Player_pos - AssetsManager::Camera_Entity->Physics()->GetPosition()).Length();
	//	}
	//}
	//if (P_camera->GetPitch() < FT_Pitch) {
	//	AssetsManager::Tweat = 1;
	//}
	//if (P_camera->GetPitch() > FT_Pitch) {
	//	AssetsManager::Tweat = 3;

	//	float cur_pitch = P_camera->GetPitch();
	//	float cur_dis = ((FT_dis - 2.0f) * cur_pitch) / (45.0f - FT_Pitch);

	//	cout << FT_dis << endl;

	//	P_camera->SetPosition(this->Physics()->GetPosition() - (Proj_dir * cur_dis));
	//}
	PhysicsEngine::Instance()->GetCollisionPair_Ground().clear();
}

//calculate the distance between wall and player
float Player::DisWalltoPlayer(GameObject* wall) {
	float penetration = 0;

	CollisionDetection::Instance()->CheckDistance(this->Physics(), wall->Physics(),
		this->Physics()->GetCollisionShape(), wall->Physics()->GetCollisionShape(), penetration);

	return penetration;
}

void Player::IDPlayerFaces() {
	this->Physics()->GetCollisionShape()->DebugDraw(this->Physics());
}

void Player::RotateLock() {
	if (P_camera->GetPitch() > 2.0f) P_camera->SetPitch(2.0f);
}