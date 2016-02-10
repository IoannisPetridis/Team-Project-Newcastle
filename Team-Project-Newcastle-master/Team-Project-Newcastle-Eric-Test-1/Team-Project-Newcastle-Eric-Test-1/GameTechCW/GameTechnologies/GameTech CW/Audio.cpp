#include "Audio.h"

Audio::Audio(){
}

Audio::~Audio(){

	/*result = sound1->release();
	result = system2->close();
	result = system2->release();*/
}

void Audio::GetCameraPosition(Camera* camera, FMOD_VECTOR Position){

	Position = { camera->GetPosition().x , camera->GetPosition().y, camera->GetPosition().z };
	
}

void Audio::GetCameraForward(Camera* camera, FMOD_VECTOR CameraForward){
	Projdir.x = -sin(camera->GetYaw() * PI / 180.0f);
	Projdir.z = -cos(camera->GetYaw() * PI / 180.0f);
	Projdir.y = sin(camera->GetPitch() * PI / 180.0f);
	Projdir.Normalise();


	CameraForward = { Projdir.x, Projdir.y, Projdir.z };

}

void Audio::GetCameraUp(Camera* camera, FMOD_VECTOR CameraUp){

	Vector3 Right = Vector3::Cross(Projdir, Vector3(0.0f, 1.0f, 0.0f));
	Vector3 Up = Vector3::Cross(Right, Projdir);
	CameraUp = { Up.x, Up.y, Up.z };

}

void Audio::GetCameraVeloicity(Camera* camera, FMOD_VECTOR CameraVelocity, FMOD_VECTOR CameraPosition , FMOD_VECTOR LastPosition){

	CameraVelocity.x = (CameraPosition.x - LastPosition.x) * (1000 / INTERFACE_UPDATETIME);
	CameraVelocity.x = (CameraPosition.x - LastPosition.x) * (1000 / INTERFACE_UPDATETIME);
	CameraVelocity.x = (CameraPosition.x - LastPosition.x) * (1000 / INTERFACE_UPDATETIME);
	

	LastPosition = CameraPosition;
}


void Audio::GetCameraInfo(Camera* camera, FMOD_RESULT result, FMOD::System* system, FMOD_VECTOR CameraPosition, FMOD_VECTOR CameraForward, FMOD_VECTOR CameraUp, FMOD_VECTOR CameraVelocity, FMOD_VECTOR LastPosition){

	GetCameraPosition(camera, CameraPosition);
	GetCameraForward(camera, CameraForward);
	GetCameraUp(camera, CameraUp);
	GetCameraVeloicity(camera, CameraVelocity , CameraPosition , LastPosition);
	result = system->set3DListenerAttributes(0, &CameraPosition, &CameraVelocity, &CameraForward, &CameraUp);
	//result = system->update();

}

void Audio::LoadSound(const char* file, FMOD::Sound *sound, FMOD_RESULT result , FMOD::System* system){

	result = system->createSound(file, FMOD_3D, 0, &sound);
//	result = sound->set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 1000.0f * DISTANCEFACTOR);
	result = sound->set3DMinMaxDistance(0.5f * 1.0f, 1000.0f * 1.0f);
}

void Audio::AddSound(FMOD_VECTOR pos, FMOD_VECTOR vel, FMOD_RESULT result, FMOD::System* system, FMOD::Channel* channel1, FMOD::Sound *sound1){


	result = channel1->set3DAttributes(&pos, &vel);
	result = system->playSound(sound1, 0, false, &channel1);

}

void CreateSystem(FMOD_RESULT result, FMOD::System *system){

	result = FMOD::System_Create(&system);
	result = system->init(100, FMOD_INIT_3D_RIGHTHANDED, 0);
	result = system->set3DSettings(1.0, 1.0f, 1.0f);

}



//
//void Audio::GetCameraPosition(Camera* camera, FMOD_VECTOR Position){
//
//	Position = { camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z };
//
//}
//
//void Audio::GetCameraForward(Camera* camera, FMOD_VECTOR CameraForward){
//	Projdir.x = -sin(camera->GetYaw() * PI / 180.0f);
//	Projdir.z = -cos(camera->GetYaw() * PI / 180.0f);
//	Projdir.y = sin(camera->GetPitch() * PI / 180.0f);
//	Projdir.Normalise();
//
//
//	CameraForward = { Projdir.x, Projdir.y, Projdir.z };
//
//}
//
//void Audio::GetCameraUp(Camera* camera, FMOD_VECTOR CameraUp){
//
//	Vector3 Right = Vector3::Cross(Projdir, Vector3(0.0f, 1.0f, 0.0f));
//	Vector3 Up = Vector3::Cross(Right, Projdir);
//	CameraUp = { Up.x, Up.y, Up.z };
//
//}
//
//void Audio::GetCameraVeloicity(Camera* camera, FMOD_VECTOR CameraVelocity, FMOD_VECTOR CameraPosition, FMOD_VECTOR LastPosition){
//
//	CameraVelocity.x = (CameraPosition.x - LastPosition.x) * (1000 / INTERFACE_UPDATETIME);
//	CameraVelocity.x = (CameraPosition.x - LastPosition.x) * (1000 / INTERFACE_UPDATETIME);
//	CameraVelocity.x = (CameraPosition.x - LastPosition.x) * (1000 / INTERFACE_UPDATETIME);
//
//
//	LastPosition = CameraPosition;
//}
//
//
//void Audio::GetCameraInfo(Camera* camera, FMOD_RESULT result, FMOD::System* system, FMOD_VECTOR CameraPosition, FMOD_VECTOR CameraForward, FMOD_VECTOR CameraUp, FMOD_VECTOR CameraVelocity, FMOD_VECTOR LastPosition){
//
//	GetCameraPosition(camera, CameraPosition);
//	GetCameraForward(camera, CameraForward);
//	GetCameraUp(camera, CameraUp);
//	GetCameraVeloicity(camera, CameraVelocity, CameraPosition, LastPosition);
//	result = system->set3DListenerAttributes(0, &CameraPosition, &CameraVelocity, &CameraForward, &CameraUp);
//	//result = system->update();
//
//}