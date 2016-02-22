#include "MyScene.h"
#include "../../ncltech/ConfigFileLoader.h"
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "mainwindow.h"

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
	
	//{//Player_1
	//	AssetsManager::Player_1 = new Player("car");
	//	AssetsManager::Player_1->SetScene(this);
	//	AssetsManager::Player_1->SetMesh(AssetsManager::Cube(), false);
	//	//AssetsManager::Player_1->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));

	//	//3 choices of car texture
	//	//these textures are just placeholders from what we had
	//	if (MainWindow::playertexture == 1){
	//		AssetsManager::Player_1->SetTexture(AssetsManager::m_ThrowTex, false); //wall texture
	//		AssetsManager::Player_1->SetBumpMap(AssetsManager::m_ThrowTexBUMP, false);
	//	}

	//	if (MainWindow::playertexture == 2){
	//		AssetsManager::Player_1->SetTexture(AssetsManager::m_CheckerboardTex, false); //wood texture
	//	}

	//	if (MainWindow::playertexture == 3){
	//		AssetsManager::Player_1->SetTexture(AssetsManager::m_Field, false); //grass texture
	//	}

	//	//4 choices of car size, 1 2 3 4
	//	AssetsManager::Player_1->SetLocalTransform(Matrix4::Scale(Vector3(MainWindow::playersize, MainWindow::playersize, MainWindow::playersize)));
	//	AssetsManager::Player_1->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(MainWindow::playersize, MainWindow::playersize, MainWindow::playersize)));
	//	AssetsManager::Player_1->SetBoundingRadius(MainWindow::playersize * MainWindow::playersize);

	//	//rest of car
	//	AssetsManager::Player_1->Physics()->name = "car";
	//	AssetsManager::Player_1->Physics()->SetInverseMass(0.06f);
	//	AssetsManager::Player_1->Physics()->SetPosition(Vector3(10.0f, 5.0f, 10.0f));
	//	Matrix3 inertia(0.1f, 0.0f, 0.0f, 0.0f, 1.1f, 0.0f, 0.0f, 0.0f, 0.1f);
	//	AssetsManager::Player_1->Physics()->SetInverseInertia(inertia);

	//	this->AddGameObject(AssetsManager::Player_1);
	//}



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

	CarPosition = { AssetsManager::Player_1->Physics()->GetPosition().x, AssetsManager::Player_1->Physics()->GetPosition().y, AssetsManager::Player_1->Physics()->GetPosition().z };
	CarVelocity = { AssetsManager::Player_1->Physics()->GetLinearVelocity().x, AssetsManager::Player_1->Physics()->GetLinearVelocity().y, AssetsManager::Player_1->Physics()->GetLinearVelocity().z };
	float CarSpeed = AssetsManager::Player_1->Physics()->GetLinearVelocity().Length();

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



