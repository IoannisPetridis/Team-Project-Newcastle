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

	Camerefix = true;
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
	result = FMOD::System_Create(&system2);   
	result = system2->init(100, FMOD_INIT_3D_RIGHTHANDED, extradriverdata);  

	result = system2->createSound(SOUNDSDIR"crash.wav", FMOD_3D, 0, &sound2);
	result = sound2->set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 1000.0f * DISTANCEFACTOR);

	result = system2->createSound(SOUNDSDIR"car.wav", FMOD_3D, 0, &sound3);
	result = sound3->setMode(FMOD_LOOP_NORMAL);
	result = sound3->set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 1000.0f * DISTANCEFACTOR);
	result = channel3->setVolume(5.5f);

	result = system2->playSound(sound3, 0, true, &channel3);



	engine_timer.GetTimedMS();



	return true;
}

void MyScene::UpdateScene(float msec)
{
	Scene::UpdateScene(msec);

	Proj_dir.x = -sin(m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.z = -cos(m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.y = sin(m_Camera->GetPitch() * PI / 180.0f);
	Proj_dir.Normalise();



	//AUDIO

	std::vector<CollisionPair>* temp = PhysicsEngine::Instance()->GetCollisionPair();

		
	for (int i = 0; i < temp->size(); i++)
	{
		FMOD_VECTOR pos = { temp->begin()->objectA->GetPosition().x, temp->begin()->objectA->GetPosition().y, temp->begin()->objectA->GetPosition().z };
		FMOD_VECTOR vel = { 0.f, 0.f, 0.f };
		float volume = temp->begin()->objectA->GetLinearVelocity().Length()*0.1f;
		
		
		float time = engine_timer.GetTimedMS();

		if (time > 50){

			if (temp->begin()->objectA->name == "car" || temp->begin()->objectB->name == "car"){
				result = system2->playSound(sound2, 0, true, &channel2);
				result = channel2->set3DAttributes(&pos, &vel);
				result = channel2->setVolume(volume);
				result = channel2->setPaused(false);
				damage++;
				this->FindGameObject("car")->SetColour(Vector4(0.2f + damage, 1.0f, 0.5f, 1.0f));
			}
		}
	}

	
	temp->clear();


	FMOD_VECTOR Carpos = { this->FindGameObject("car")->Physics()->GetPosition().x, this->FindGameObject("car")->Physics()->GetPosition().y, this->FindGameObject("car")->Physics()->GetPosition().z };
	FMOD_VECTOR Carvel = { this->FindGameObject("car")->Physics()->GetLinearVelocity().x, this->FindGameObject("car")->Physics()->GetLinearVelocity().y, this->FindGameObject("car")->Physics()->GetLinearVelocity().z };
	//FMOD_VECTOR Carvel = { 0.0f, 0.0f, 0.0f };
	result = channel3->set3DAttributes(&Carpos, &Carvel);

	float carspeed = this->FindGameObject("car")->Physics()->GetLinearVelocity().Length();
	result = channel3->setFrequency(20000.f + carspeed * 200);
	result = channel3->setVolume(carspeed);
	result = system2->update();
	result = channel3->setPaused(false);


	Audio* audio = new Audio;
	audio->GetCameraInfo(m_Camera, result, system2);

	//END AUDIO

	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_1)) {
		Camerefix = !Camerefix;
		
	}
	if (Camerefix) {
		m_Camera->SetPosition(this->FindGameObject("car")->Physics()->GetPosition() -
			Proj_dir * 15.0f);
	}

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



