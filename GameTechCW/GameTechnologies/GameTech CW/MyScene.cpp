#include "MyScene.h"
#include "../../ncltech/ConfigFileLoader.h"
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "mainwindow.h"

bool MyScene::AbilityUsed = false;
int MyScene::counter = 0;
int MyScene::abilitycounter = 200;

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
	ActionHandler::Instance()->AIChoice = MainWindow::AIchoice;
	GOM->AIChoice = MainWindow::AIchoice;

	PhysicsEngine::Instance()->SetGravity(Vector3(0.0f, -14.81f, 0.0f));
	PhysicsEngine::Instance()->SetDampingFactor(0.990f);

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
	
		AssetsManager::Player_1->SetScene(this);
		AssetsManager::Player_1->SetMesh(AssetsManager::Cube(), false);

		//3 choices of car texture
		if (MainWindow::playertexture == 1){
			
			AssetsManager::Player_1->SetTexture(AssetsManager::m_Blue, false);
		}

		if (MainWindow::playertexture == 2){
			AssetsManager::Player_1->SetTexture(AssetsManager::m_Lightning, false);
		}

		if (MainWindow::playertexture == 3){
			AssetsManager::Player_1->SetTexture(AssetsManager::m_BlueCat, false);
		}

		//4 choices of car size, 1 2 3 4
		float size = (MainWindow::playersize * 0.5);
		AssetsManager::Player_1->SetLocalTransform(Matrix4::Scale(Vector3(size, size, size)));
		AssetsManager::Player_1->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(size, size, size)));
		AssetsManager::Player_1->SetBoundingRadius(size * size);
		AssetsManager::Player_1->Physics()->SetCar(true);
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
	/*FMOD_VECTOR AIPosition = { AssetsManager::NeutralAI->Physics()->GetPosition().x, AssetsManager::NeutralAI->Physics()->GetPosition().y, AssetsManager::NeutralAI->Physics()->GetPosition().z };
	FMOD_VECTOR AIVelocity = { AssetsManager::NeutralAI->Physics()->GetLinearVelocity().x, AssetsManager::NeutralAI->Physics()->GetLinearVelocity().y, AssetsManager::NeutralAI->Physics()->GetLinearVelocity().z };
	float AIForce = AssetsManager::NeutralAI->Physics()->GetForce().Length();
	Audio::UpdateSound(AIPosition, AIVelocity, 20000.f + AIForce * 200, 10.f + AIForce, Audio::channel9);
	Audio::Result = Audio::AudioSystem->update();*/
	Audio::UpdateSound(CarPosition, CarVelocity, 20000.f + CarSpeed * 200, 10.f + CarSpeed, Audio::channel3);
	Audio::GetCameraInfo(m_Camera);
	////END AUDIO


	//player special ability
	int skillchoice = MainWindow::playerskill;

	if (!MyScene::AbilityUsed && Window::GetKeyboard()->KeyHeld(KEYBOARD_Q)) {
		MyScene::AbilityUsed = true;
		if (skillchoice == 1){ //ball pull
			ActionHandler::Instance()->GravityGun();
		}

		if (skillchoice == 2){ //midpoint teleport
			AssetsManager::Player_1->Physics()->SetPosition(Vector3(0, 10, 0));
			MyScene::AbilityUsed = true;
		}

		if (skillchoice == 3){
			ActionHandler::Instance()->AIOffAbility = true;
		}
	}

	if (AbilityUsed == true) {
		abilitycounter--;
		if (abilitycounter == 0) {
			ActionHandler::Instance()->AIOffAbility = false;
			ActionHandler::Instance()->RemoveForce();
		}
	}

	//PowerUps
	if (AssetsManager::Player_1->invisible){
		if (PowerUps::InvisTimer.GetLastTime() > 17500){
			AssetsManager::Player_1->SetColour(Vector4(AssetsManager::Player_1->GetColour().x, AssetsManager::Player_1->GetColour().y, AssetsManager::Player_1->GetColour().z, 1.f));
			AssetsManager::Player_1->invisible = false;
		}
	}

	if (PowerUps::GetPlayerPickup()){
		ParticleEmitter* powerupspark = new ParticleEmitter();

		powerupspark->SetParticleSize(0.6f);
		powerupspark->SetParticleVariance(2.0f);
		powerupspark->SetLaunchParticles(20.0f);
		powerupspark->SetParticleLifetime(20.0f);
		powerupspark->SetParticleSpeed(0.3f);
		powerupspark->SetParticleRate(10.f);
		powerupspark->SetDirection(Vector3(0.f, 4.f, 0.f));
		powerupspark->SetSourcePosition(AssetsManager::Player_1->Physics()->GetPosition());
		powerupspark->SetParticleColour(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		powerupspark->SetIsTimer(true);
		powerupspark->SetEmitterLifetime(150.0f);
		this->AddParticleObject(powerupspark);

		PowerUps::SetPlayerPickup(false);
	}
	
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_B)){
		PowerUps::AddRandomPowerUp(this,AssetsManager::PowerUpBox2);
	}

	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_N)){
		PowerUps::UsePowerUp(AssetsManager::Player_1, this);
	}


	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_I)){
		AssetsManager::Player_1->SetPowerUpState("invisibility");
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

	/*NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Camera X:" + std::to_string((int)m_Camera->GetPosition().x)
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
		);*/

	NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "HP : " + std::to_string(AssetsManager::Player_1->Physics()->GetHP()));
	
	if (AssetsManager::Player_1->Physics()->GetHP() <= 0){
		AssetsManager::Player_1->Physics()->SetPosition(Vector3(10.0f, 10.0f, 10.0f));
		AssetsManager::Player_1->Physics()->SetHP(100.f);
	}

	
}

void MyScene::RenderScene()
{
	Scene::RenderScene();
}



