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
	//PhysicsEngine::Instance()->SetGravity(Vector3(0.0f, -9.81f, 0.0f));

	PhysicsEngine::Instance()->SetGravity(Vector3(0.0f, 0.0f, 0.0f));
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
	{
		result = FMOD::System_Create(&system2);
		result = system2->init(100, FMOD_INIT_3D_RIGHTHANDED, extradriverdata);
		result = system2->createSound("drumloop.wav", FMOD_3D, 0, &sound1);
		result = sound1->set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 1000.0f * DISTANCEFACTOR);
		result = system2->set3DSettings(1.0, DISTANCEFACTOR, 1.0f);
		result = system2->playSound(sound1, 0, true, &channel1);


		result = system2->createSound("swish.wav", FMOD_DEFAULT, 0, &sound2);

		FMOD_VECTOR LastPosition = { 0.0f, 0.0f, 0.0f };
		FMOD_VECTOR pos = { 0.0f, 0.0f, 0.0f };
		FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };



		result = system2->playSound(sound2, 0, true, &channel2);
		result = channel1->set3DAttributes(&pos, &vel);

		result = channel1->setPaused(false);
	}
	return true;
}

void MyScene::UpdateScene(float msec)
{
	Scene::UpdateScene(msec);

	Proj_dir.x = -sin(m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.z = -cos(m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.y = sin(m_Camera->GetPitch() * PI / 180.0f);
	Proj_dir.Normalise();


	//audio update
	{
		//static float t = 0;
		static FMOD_VECTOR LastPosition = { 0.0f, 0.0f, 0.0f };

		FMOD_VECTOR CameraForward = { Proj_dir.x, Proj_dir.y, Proj_dir.z };

		Vector3 Right = Vector3::Cross(Proj_dir, Vector3(0.0f, 1.0f, 0.0f));
		Vector3 Up = Vector3::Cross(Right, Proj_dir);

		FMOD_VECTOR CameraUp = { Up.x, Up.y, Up.z };
		FMOD_VECTOR CameraVelocity = { 0.0f, 0.0f, 0.0f };
		FMOD_VECTOR CameraPosition = { m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z };

		CameraVelocity.x = (CameraPosition.x - LastPosition.x) * (1000 / INTERFACE_UPDATETIME);
		CameraVelocity.y = (CameraPosition.y - LastPosition.y) * (1000 / INTERFACE_UPDATETIME);
		CameraVelocity.z = (CameraPosition.z - LastPosition.z) * (1000 / INTERFACE_UPDATETIME);

		LastPosition = CameraPosition;

		result = system2->set3DListenerAttributes(0, &CameraPosition, &CameraVelocity, &CameraForward, &CameraUp);
		result = system2->update();
	}


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



