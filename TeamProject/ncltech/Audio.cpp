#include "Audio.h"

//Audio System
FMOD_RESULT Audio::Result;
FMOD::System *Audio::AudioSystem;

//Sounds
FMOD::Sound* Audio::Car   = 0;
FMOD::Sound* Audio::Crash = 0;
FMOD::Sound* Audio::Ball  = 0;
FMOD::Sound* Audio::Wall  = 0;
FMOD::Sound* Audio::Goal = 0;

//Channels
FMOD::Channel *Audio::channel1 = 0;
FMOD::Channel *Audio::channel2 = 0;
FMOD::Channel *Audio::channel3 = 0;
FMOD::Channel *Audio::channel4 = 0;

//Extra Info
const int   Audio::INTERFACE_UPDATETIME = 50;      // 50ms update for interface
const float Audio::DISTANCEFACTOR = 1.0f;
void	   *Audio::extradriverdata = 0;

//CameraInfo
Vector3		Audio::Projdir;
FMOD_VECTOR Audio::CameraPosition;
FMOD_VECTOR Audio::CameraForward;
FMOD_VECTOR Audio::CameraUp;
FMOD_VECTOR Audio::CameraVelocity;
FMOD_VECTOR Audio::LastPosition;


void Audio::GetCameraInfo(Camera* camera){

	CameraPosition = { camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z };
	Projdir.x = -sin(camera->GetYaw() * PI / 180.0f);
	Projdir.z = -cos(camera->GetYaw() * PI / 180.0f);
	Projdir.y =  sin(camera->GetPitch() * PI / 180.0f);
	Projdir.Normalise();
	CameraForward = { Projdir.x, Projdir.y, Projdir.z };
	Vector3 Right = Vector3::Cross(Projdir, Vector3(0.0f, 1.0f, 0.0f));
	Vector3 Up = Vector3::Cross(Right, Projdir);
	CameraUp = { Up.x, Up.y, Up.z };

	CameraVelocity = { 0.0f, 0.0f, 0.0f };

	LastPosition = CameraPosition;
	Result = AudioSystem->set3DListenerAttributes(0, &CameraPosition,0, &CameraForward, &CameraUp);
	Result = AudioSystem->update();
}

void Audio::AddSound(FMOD_VECTOR pos, FMOD_VECTOR vel, FMOD::Channel* channel, FMOD::Sound *sound, float volume){

	Result = AudioSystem->playSound(sound, 0, true, &channel);
	Result = channel->set3DAttributes(&pos, &vel);
	Result = channel->setVolume(volume);
	Result = channel->setPaused(false);
}


FMOD_VECTOR GetPosition(PhysicsObject object){
	FMOD_VECTOR position = { object.GetPosition().x, object.GetPosition().y, object.GetPosition().z };
	return position;
}

void GetVelocity(PhysicsObject* object, FMOD_VECTOR velocity){
	velocity = { object->GetLinearVelocity().x, object->GetLinearVelocity().y, object->GetLinearVelocity().z };
	
}

void Audio::InitialiseAudio(){

	Result = FMOD::System_Create(&AudioSystem);
	Result = Audio::AudioSystem->init(100, FMOD_INIT_3D_RIGHTHANDED, extradriverdata);

}

void Audio::ReleaseAudio(){

	Result = Car->release();
	Result = Crash->release();
	Result = Ball->release();
	Result = Wall->release();
	
	Result = AudioSystem->close();
	Result = AudioSystem->release();

}

void Audio::LoadSounds(){

	Result = AudioSystem->createSound(SOUNDSDIR"crash.wav", FMOD_3D, 0, &Crash);
	Result = Crash->set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 1000.0f * DISTANCEFACTOR);

	Result = AudioSystem->createSound(SOUNDSDIR"ball.wav", FMOD_3D, 0, &Ball);
	Result = Ball->set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 1000.0f * DISTANCEFACTOR);

	Result = AudioSystem->createSound(SOUNDSDIR"car.wav", FMOD_3D, 0, &Car);
	Result = AudioSystem->createSound(SOUNDSDIR"goal.wav", FMOD_DEFAULT, 0, &Goal);

	Result = Car->setMode(FMOD_LOOP_NORMAL);
	Result = Car->set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 1000.0f * DISTANCEFACTOR);
	Result = AudioSystem->playSound(Car, 0, true, &channel3);
	
}

void Audio::UpdateSound(FMOD_VECTOR position ,FMOD_VECTOR velocity, float frequency, float volume,FMOD::Channel* channel){

	Result = channel3->set3DAttributes(&position, &velocity);
	Result = channel3->setFrequency(frequency);
	Result = channel3->setVolume(volume);
	Result = channel3->setPaused(false);
	Result = AudioSystem->update();
}

void Audio::CollisionSound(PhysicsObject* objectA, PhysicsObject* objectB,  float time){


		if ((objectA->name == "car" &&  objectB->name == "cube") || 
			(objectB->name == "car" &&  objectA->name == "cube") ){
			if (time > 50){
			FMOD_VECTOR	Position = { objectA->GetPosition().x, objectA->GetPosition().y, objectA->GetPosition().z };
			FMOD_VECTOR	Velocity = { objectA->GetLinearVelocity().x, objectA->GetLinearVelocity().y, objectA->GetLinearVelocity().z };
			float volume = objectA->GetLinearVelocity().Length()*0.6f;
			AddSound(Position, Velocity, channel2, Crash, volume);
			}
		}

		if ((objectA->name == "car" &&  objectB->name == "ball") ||
			(objectB->name == "car" &&  objectA->name == "ball")){
			if (time > 50){
				FMOD_VECTOR Position = { objectA->GetPosition().x, objectA->GetPosition().y, objectA->GetPosition().z };
				FMOD_VECTOR vel = { 0.f, 0.f, 0.f };
				float volume = objectA->GetLinearVelocity().Length()*10.f;
				AddSound(Position, vel, Audio::channel4, Audio::Ball, volume);
			}
		}
	}






//	if (m->objectA->name == "car" &&  m->objectB->name == "cube"){
//		if (time > 50){
//			CarPosition = { m->objectA->GetPosition().x, m->objectA->GetPosition().y, m->objectA->GetPosition().z };
//			CarVelocity = { m->objectA->GetLinearVelocity().x, m->objectA->GetLinearVelocity().y, m->objectA->GetLinearVelocity().z };
//			float volume = m->objectA->GetLinearVelocity().Length()*0.1f;
//			Audio::AddSound(CarPosition, CarVelocity,  Audio::channel2, Audio::Crash, volume);
//		}
//	}

//	if (m->objectA->name == "car" &&  m->objectB->name == "ball"){
//		if (time > 50){
//			SoundVelocity = { m->objectA->GetPosition().x, m->objectA->GetPosition().y, m->objectA->GetPosition().z };
//			FMOD_VECTOR vel = { 0.f, 0.f, 0.f };
//			float volume = m->objectA->GetLinearVelocity().Length()*10.f;
//			Audio::AddSound(SoundPosition, vel, Audio::channel4, Audio::Ball, volume);
//		}
//	}
//}
	

