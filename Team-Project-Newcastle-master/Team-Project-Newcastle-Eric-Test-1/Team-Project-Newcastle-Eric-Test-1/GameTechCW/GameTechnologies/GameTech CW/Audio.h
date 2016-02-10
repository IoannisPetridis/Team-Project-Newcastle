#pragma once


#include "../../FMOD/inc/fmod.hpp"
#include "string.h"
#include "../nclgl/Camera.h"


class Audio 
{

public:
	Audio();
	~Audio();

	void GetCameraPosition(Camera* camera, FMOD_VECTOR Position);
	void GetCameraForward(Camera* camera, FMOD_VECTOR CameraForward);
	void GetCameraUp(Camera* camera, FMOD_VECTOR CameraUp);
	void GetCameraVeloicity(Camera* camera, FMOD_VECTOR CameraVelocity, FMOD_VECTOR CameraPosition, FMOD_VECTOR LastPosition);

	void GetCameraInfo(Camera* camera, FMOD_RESULT result, FMOD::System* system, FMOD_VECTOR CameraPosition, FMOD_VECTOR CameraForward, FMOD_VECTOR CameraUp, FMOD_VECTOR CameraVelocity, FMOD_VECTOR LastPosition);
	void CreateSystem(FMOD_RESULT result, FMOD::System *system);
	void LoadSound(const char* file, FMOD::Sound *sound, FMOD_RESULT result ,FMOD::System* system);
	void AddSound(FMOD_VECTOR pos, FMOD_VECTOR vel, FMOD_RESULT result, FMOD::System* system, FMOD::Channel* channel1, FMOD::Sound *sound1);


	/*FMOD_VECTOR CameraPosition;
	FMOD_VECTOR CameraForward;
	FMOD_VECTOR CameraUp;
	FMOD_VECTOR CameraVelocity;
	FMOD_VECTOR LastPosition;*/
	/*FMOD::Sound *sound1, *sound2;
	
	FMOD::Channel   *channel1 = 0, *channel2 = 0;
	void            *extradriverdata = 0;
	bool             listenerflag = true;
*/
	const int   INTERFACE_UPDATETIME = 50;      // 50ms update for interface
	const float DISTANCEFACTOR = 1.0f;          // Units per meter.  I.e feet would = 3.28.  centimeters would = 100.


protected:
	
	Vector3 Projdir;
	
private:
	
};