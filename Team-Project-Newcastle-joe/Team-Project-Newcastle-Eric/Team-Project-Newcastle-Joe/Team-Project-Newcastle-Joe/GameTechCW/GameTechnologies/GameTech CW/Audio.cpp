#include "Audio.h"

Audio::Audio(){
}

Audio::~Audio(){

	/*result = sound1->release();
	result = system2->close();
	result = system2->release();*/
}


void Audio::GetCameraInfo(Camera* camera, FMOD_RESULT result, FMOD::System* system){



	CameraPosition = { camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z };


	Projdir.x = -sin(camera->GetYaw() * PI / 180.0f);
	Projdir.z = -cos(camera->GetYaw() * PI / 180.0f);
	Projdir.y = sin(camera->GetPitch() * PI / 180.0f);
	Projdir.Normalise();


	CameraForward = { Projdir.x, Projdir.y, Projdir.z };


	Vector3 Right = Vector3::Cross(Projdir, Vector3(0.0f, 1.0f, 0.0f));
	Vector3 Up = Vector3::Cross(Right, Projdir);
	CameraUp = { Up.x, Up.y, Up.z };



	//CameraVelocity.x = (CameraPosition.x - LastPosition.x) * (1000 / INTERFACE_UPDATETIME);
	//CameraVelocity.y = (CameraPosition.y - LastPosition.y) * (1000 / INTERFACE_UPDATETIME);
	//CameraVelocity.z = (CameraPosition.z - LastPosition.z) * (1000 / INTERFACE_UPDATETIME);

	CameraVelocity = { 0.0f, 0.0f, 0.0f };

	LastPosition = CameraPosition;
	result = system->set3DListenerAttributes(0, &CameraPosition, &CameraVelocity, &CameraForward, &CameraUp);
	result = system->update();

}



void Audio::AddSound(const char* file, FMOD_VECTOR pos, FMOD_VECTOR vel, FMOD_RESULT result, FMOD::System* system, FMOD::Channel* channel, FMOD::Sound *sound, bool paused, float volume){

	result = system->createSound(file, FMOD_3D, 0, &sound);
	result = sound->set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 1000.0f * DISTANCEFACTOR);
	result = channel->set3DAttributes(&pos, &vel);
	
	result = channel->setVolume(volume);
	
	result = system->playSound(sound, 0, paused, &channel);

	result = system->update();

}
