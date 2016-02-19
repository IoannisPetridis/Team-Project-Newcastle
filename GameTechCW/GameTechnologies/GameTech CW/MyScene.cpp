#include "MyScene.h"
#include "../../ncltech/ConfigFileLoader.h"
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

#define PI 3.14159265f

MyScene::MyScene(Window& window, GameObjectMag* gom) : Scene(window), GOM(gom)
{
	if (init == true)	{}
		init = InitialiseGL();

	UpdateWorldMatrices(m_RootGameObject, Matrix4());
	
	PhysicsEngine::Instance()->SetUpdateTimestep(1.0f / 60.0f);		//60 Updates per second
}

MyScene::~MyScene()
{
}

bool MyScene::InitialiseGL()
{
	PhysicsEngine::Instance()->SetGravity(Vector3(0.0f, -14.81f, 0.0f));
	PhysicsEngine::Instance()->SetDampingFactor(0.988f);

	m_Camera->SetPosition(Vector3(24.f, 13.f, 9.f));
	m_Camera->SetYaw(90.0f);
	
	if (GOM->GetID() == 0) {
		GOM->GOM_Loading(this);
	}
	else if (GOM->GetID() == 1) {
		AssetsManager::InitializeMeshes();
		GOM->GOM_GamePlay(this);
	}

	//Initialize all game objects
	Audio_Timer.GetTimedMS();
	return true;
}

void MyScene::UpdateScene(float msec)
{
	Scene::UpdateScene(msec);

	Proj_dir.x = -sin(m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.z = -cos(m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.y = sin(m_Camera->GetPitch() * PI / 180.0f);
	Proj_dir.Normalise();

	//Camera Control
	AssetsManager::Player_1->CameraControl();

	std::vector<CollisionPair>* temp = PhysicsEngine::Instance()->GetVPair();

	for (auto m = temp->begin(); m != temp->end(); ++m)
	{
		if (m->objectA->name.find("ground") != string::npos || m->objectB->name.find("ground") != string::npos) {}
		else{
			time = Audio_Timer.GetTimedMS();
			//cout << time << " " << m->objectA->name << " colliding with :  " << m->objectB->name << endl;
			Audio::CollisionSound(m->objectA, m->objectB, time);
		}
	}
	temp->clear();

	CarPosition = { this->FindGameObject("car")->Physics()->GetPosition().x, this->FindGameObject("car")->Physics()->GetPosition().y, this->FindGameObject("car")->Physics()->GetPosition().z };
	CarVelocity = { this->FindGameObject("car")->Physics()->GetLinearVelocity().x, this->FindGameObject("car")->Physics()->GetLinearVelocity().y, this->FindGameObject("car")->Physics()->GetLinearVelocity().z };
	float CarSpeed = this->FindGameObject("car")->Physics()->GetLinearVelocity().Length();

	Audio::UpdateSound(CarPosition, CarVelocity, 20000.f + CarSpeed * 200, 10.f + CarSpeed, Audio::channel3);
	Audio::GetCameraInfo(m_Camera);
	////END AUDIO

	NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Camera X:" + std::to_string((int)m_Camera->GetPosition().x)
		+ " Y:"
		+ std::to_string((int)m_Camera->GetPosition().y)
		+ " Z:"
		+ std::to_string((int)m_Camera->GetPosition().z)
		+ " Pitch:"
		+ std::to_string((float)m_Camera->GetPitch())
		+ " Yaw:"
		+ std::to_string((float)m_Camera->GetYaw())
		+ " cord:" 
		+ std::to_string((float)Proj_dir.x) + " "
		+ std::to_string((float)Proj_dir.y) + " "
		+ std::to_string((float)Proj_dir.z) + " "
		);
}

void MyScene::RenderScene()
{
	Scene::RenderScene();
}



