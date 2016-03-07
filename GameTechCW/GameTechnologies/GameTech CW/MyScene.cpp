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

		Vector3* vlist = new Vector3[3];
		vlist[0] = Vector3(0.0f, 0.5f, 0.0f) * 10.0f;
		vlist[1] = Vector3(0.5f, -0.5f, 0.0f) * 10.0f;
		vlist[2] = Vector3(-0.5f, -0.5f, 0.0f) * 10.0f;

		NCLDebug::DrawPolygon(3, vlist);

		delete[] vlist;
	}

	else if (GOM->GetID() == 1) {
		AssetsManager::InitializeMeshes();
		GOM->GOM_GamePlay(this);
	
		AssetsManager::Player_1 = new Player("car");
		AssetsManager::Player_1->SetScene(this);
		AssetsManager::Player_1->SetMesh(AssetsManager::Cube(), false);

		//3 choices of car texture
		//these textures are just placeholders from what we had
		if (MainWindow::playertexture == 1){
			
			AssetsManager::Player_1->SetTexture(AssetsManager::m_Glass, false);
		}

		if (MainWindow::playertexture == 2){
			AssetsManager::Player_1->SetTexture(AssetsManager::m_CheckerboardTex, false); //wood texture
		}

		if (MainWindow::playertexture == 3){
			AssetsManager::Player_1->SetTexture(AssetsManager::m_Field, false); //grass texture
		}

		//4 choices of car size, 1 2 3 4
		int size= MainWindow::playersize * 0.5;
		AssetsManager::Player_1->SetLocalTransform(Matrix4::Scale(Vector3((MainWindow::playersize), (MainWindow::playersize), (MainWindow::playersize))));
		AssetsManager::Player_1->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3((MainWindow::playersize), (MainWindow::playersize), (MainWindow::playersize))));
		AssetsManager::Player_1->SetBoundingRadius((MainWindow::playersize) * (MainWindow::playersize));

		AssetsManager::Player_1->Physics()->name = "car";
		AssetsManager::Player_1->Physics()->SetInverseMass(0.06f);
		AssetsManager::Player_1->Physics()->SetPosition(Vector3(10.0f, 5.0f, 10.0f));
		Matrix3 inertia(0.1f, 0.0f, 0.0f, 0.0f, 1.1f, 0.0f, 0.0f, 0.0f, 0.1f);
		AssetsManager::Player_1->Physics()->SetInverseInertia(inertia);
		AssetsManager::Player_1->Physics()->SetCar(true);
		this->AddGameObject(AssetsManager::Player_1);
	}

	{//Player_1
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
			Audio::CollisionSound(m->objectA, m->objectB, time);
		}
	}
	temp->clear();

	CarPosition = { AssetsManager::Player_1->Physics()->GetPosition().x, AssetsManager::Player_1->Physics()->GetPosition().y, AssetsManager::Player_1->Physics()->GetPosition().z };
	CarVelocity = { AssetsManager::Player_1->Physics()->GetLinearVelocity().x, AssetsManager::Player_1->Physics()->GetLinearVelocity().y, AssetsManager::Player_1->Physics()->GetLinearVelocity().z };
	float CarSpeed = AssetsManager::Player_1->Physics()->GetLinearVelocity().Length();
	FMOD_VECTOR AIPosition = { AssetsManager::NeutralAI->Physics()->GetPosition().x, AssetsManager::NeutralAI->Physics()->GetPosition().y, AssetsManager::NeutralAI->Physics()->GetPosition().z };
	FMOD_VECTOR AIVelocity = { AssetsManager::NeutralAI->Physics()->GetLinearVelocity().x, AssetsManager::NeutralAI->Physics()->GetLinearVelocity().y, AssetsManager::NeutralAI->Physics()->GetLinearVelocity().z };
	
	float AIForce = AssetsManager::NeutralAI->Physics()->GetForce().Length();
	Audio::UpdateSound(AIPosition, AIVelocity, 20000.f + AIForce * 200, 10.f + AIForce, Audio::channel9);
	Audio::UpdateSound(CarPosition, CarVelocity, 20000.f + CarSpeed * 200, 10.f + CarSpeed, Audio::channel3);	
	Audio::Result = Audio::AudioSystem->update();

	Audio::GetCameraInfo(m_Camera);
	
	////END AUDIO


	//PowerUps
	if (AssetsManager::Player_1->invisible){
		if (PowerUps::InvisTimer.GetLastTime() > 20000){
			AssetsManager::Player_1->SetColour(Vector4(AssetsManager::Player_1->GetColour().x, AssetsManager::Player_1->GetColour().y, AssetsManager::Player_1->GetColour().z, 1.f));
			AssetsManager::Player_1->invisible = false;
		}
	}

	if (PowerUps::GetPlayerPickup()){
		ParticleEmitter* powerupspark = new ParticleEmitter();

		powerupspark->SetParticleSize(0.8f);
		powerupspark->SetParticleVariance(1.0f);
		powerupspark->SetLaunchParticles(5.0f);
		powerupspark->SetParticleLifetime(20.0f);
		powerupspark->SetParticleSpeed(0.3f);
		powerupspark->SetParticleRate(5.f);
		powerupspark->SetDirection(Vector3(0.f, 4.f, 0.f));
		powerupspark->SetSourcePosition(AssetsManager::Player_1->Physics()->GetPosition());
		this->AddParticleObject(powerupspark);
		PowerUps::SetPlayerPickup(false);
		}

	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_B)){
		PowerUps::AddRandomPowerUp(this);
	}

	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_N)){
		PowerUps::UsePowerUp(AssetsManager::Player_1, this);
	}


	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_I)){
		AssetsManager::Player_1->SetPowerUpState("banana");
	}

	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_Z)){
		PowerUps::AddAndroidPowerUp(100, 100, this, "banana");
	}

	if (PhysicsEngine::Instance()->IsPaused()){
		Audio::channel2->setPaused(true);
		Audio::channel3->setPaused(true);
		Audio::channel4->setPaused(true);
	}
	else{
		Audio::channel2->setPaused(false);
		Audio::channel3->setPaused(false);
		Audio::channel4->setPaused(false);
	}

	if (AssetsManager::Player_1->Physics()->GetHP() <= 0){
		AssetsManager::Player_1->Physics()->SetPosition(Vector3(10.0f, 10.0f, 10.0f));
		AssetsManager::Player_1->Physics()->SetHP(100.f);
	}

}

void MyScene::RenderScene()
{
	Scene::RenderScene();
}



