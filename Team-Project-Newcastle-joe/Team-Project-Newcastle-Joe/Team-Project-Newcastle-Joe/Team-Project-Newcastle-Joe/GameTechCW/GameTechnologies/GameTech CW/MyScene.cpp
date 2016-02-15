#include "MyScene.h"
#include "../../ncltech/ConfigFileLoader.h"
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

#define PI 3.14159265f

MyScene::MyScene(Window& window) : Scene(window)
{
	if (init == true)	{}
		init = InitialiseGL();

	UpdateWorldMatrices(m_RootGameObject, Matrix4());

	GOM = new GameObjectMag();	//initialize the GOM

	PhysicsEngine::Instance()->SetUpdateTimestep(1.0f / 60.0f);		//60 Updates per second
}

MyScene::~MyScene()
{
	//delete any texture used
	if (m_TargetTexture)
	{
		glDeleteTextures(1, &m_TargetTexture);
		m_TargetTexture = NULL;
	}
}

bool MyScene::InitialiseGL()
{
	PhysicsEngine::Instance()->SetGravity(Vector3(0.0f, -9.81f, 0.0f));
	//PhysicsEngine::Instance()->SetGravity(Vector3(0.0f, 0.0f, 0.0f));
	PhysicsEngine::Instance()->SetDampingFactor(0.988f);

	m_Camera->SetPosition(Vector3(24.f, 13.f, 9.f));
	m_Camera->SetYaw(90.0f);

	//Config file loader to load up the Fucntionality
	bool shadow = true;
	bool Motion_blur = true;
	bool replay = true;

	Camerefix = false;
	ai_toggle = true;
	travese_toggle = true;
	gameover = false;
	ai_state = true;
	cooldown = false;
	ballnum = 50;
	diff = 1;
	T_counter = 0;
	DebugMode = 2;
	Str_c = 0;
	score = 0;
	friction = 0.5f;
	start_strong = -1.0f;
	timer = 0.0f;
	//end
	
	//Initialize all game objects
	GOM->GOMInit(this);

	//audio
	result = FMOD::System_Create(&AudioSystem);
	result = AudioSystem->init(100, FMOD_INIT_3D_RIGHTHANDED, extradriverdata);

	result = AudioSystem->createSound(SOUNDSDIR"crash.wav", FMOD_3D, 0, &Crash);
	result = Crash->set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 1000.0f * DISTANCEFACTOR);

	result = AudioSystem->createSound(SOUNDSDIR"car.wav", FMOD_3D, 0, &Car);
	result = Car->setMode(FMOD_LOOP_NORMAL);
	result = Car->set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 1000.0f * DISTANCEFACTOR);

	result = AudioSystem->createSound(SOUNDSDIR"ball.wav", FMOD_3D, 0, &Ball);
	result = Ball->set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 1000.0f * DISTANCEFACTOR);

	result = AudioSystem->playSound(Car, 0, true, &channel3);

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

	//AUDIO

	Audio* audio = new Audio;
	std::vector<CollisionPair>* temp = PhysicsEngine::Instance()->GetCollisionPair();
	
	for (auto m = temp->begin(); m != temp->end(); ++m)
	{
		time = Audio_Timer.GetTimedMS();

		if (m->objectA->name == "car" &&  m->objectB->name == "cube"){
			if (time > 50){
				CarPosition = { m->objectA->GetPosition().x, m->objectA->GetPosition().y, m->objectA->GetPosition().z };
				CarVelocity = { m->objectA->GetLinearVelocity().x, m->objectA->GetLinearVelocity().y, m->objectA->GetLinearVelocity().z };
				float volume = m->objectA->GetLinearVelocity().Length()*0.1f;
				audio->AddSound(CarPosition, CarVelocity, result, AudioSystem, channel2, Crash, volume);
			}
		}

		if (m->objectA->name == "car" &&  m->objectB->name == "ball"){
			if (time > 50){
				SoundVelocity = { m->objectA->GetPosition().x, m->objectA->GetPosition().y, m->objectA->GetPosition().z };
				FMOD_VECTOR vel = { 0.f, 0.f, 0.f };
				float volume = m->objectA->GetLinearVelocity().Length()*10.f;
				audio->AddSound(SoundPosition, vel, result, AudioSystem, channel4, Ball, volume);
			}
		}
	}

	temp->clear();
	

	
	CarPosition = { this->FindGameObject("car")->Physics()->GetPosition().x, this->FindGameObject("car")->Physics()->GetPosition().y, this->FindGameObject("car")->Physics()->GetPosition().z };
	CarVelocity = { this->FindGameObject("car")->Physics()->GetLinearVelocity().x, this->FindGameObject("car")->Physics()->GetLinearVelocity().y, this->FindGameObject("car")->Physics()->GetLinearVelocity().z };
	result = channel3->set3DAttributes(&CarPosition, &CarVelocity);

	float carspeed = this->FindGameObject("car")->Physics()->GetLinearVelocity().Length();
	result = channel3->setFrequency(20000.f + carspeed * 200);
	result = channel3->setVolume(carspeed);
	result = AudioSystem->update();
	result = channel3->setPaused(false);

	audio->GetCameraInfo(m_Camera, result, AudioSystem);

	//END AUDIO

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