#pragma once


#include "../../FMOD/inc/fmod.hpp"
#include "../../FMOD/inc/fmod_errors.h"
#include "string.h"
#include "../nclgl/Camera.h"
#include "../../ncltech/PhysicsObject.h"


class Audio
{
	friend class Scene;
public:
	Audio();
	~Audio();

	void GetCameraInfo(Camera* camera, FMOD_RESULT result, FMOD::System* system);
	void AddSound(FMOD_VECTOR pos, FMOD_VECTOR vel, FMOD_RESULT result, FMOD::System* system, FMOD::Channel* channel1, FMOD::Sound *sound1, float volume);
	//void GetPosition(PhysicsObject* object,  FMOD_VECTOR position);
	void GetVelocity(PhysicsObject* object,  FMOD_VECTOR velocity);

	FMOD_VECTOR Getposition(PhysicsObject* object, FMOD_VECTOR velocity);

protected:

	Vector3 Projdir;
	FMOD_VECTOR CameraPosition;
	FMOD_VECTOR CameraForward;
	FMOD_VECTOR CameraUp;
	FMOD_VECTOR CameraVelocity;
	FMOD_VECTOR LastPosition;

private:

};