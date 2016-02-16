#pragma once


#include "../../FMOD/inc/fmod.hpp"
#include "../../FMOD/inc/fmod_errors.h"
#include "string.h"
#include "../nclgl/Camera.h"
#include "../../ncltech/PhysicsObject.h"
#include "../../ncltech/PhysicsEngine.h"


class Audio
{
	friend class Scene;
	friend class MyScene;
public:
	
	static void GetCameraInfo(Camera* camera);
	static void AddSound(FMOD_VECTOR pos, FMOD_VECTOR vel, FMOD::Channel* channel1, FMOD::Sound *sound1, float volume);
	static void GetVelocity(PhysicsObject* object, FMOD_VECTOR velocity);
	static  FMOD_VECTOR GetPosition(PhysicsObject object);

	static void InitialiseAudio();
	static void ReleaseAudio();
	static void LoadSounds();
	static void UpdateSound(FMOD_VECTOR position, FMOD_VECTOR velocity, float frequency, float volume, FMOD::Channel* channel);
	static void CollisionSound(PhysicsObject* objectA, PhysicsObject* objectB, float time);

	static FMOD_RESULT Result;
	static FMOD::System *AudioSystem;
	static FMOD::Channel   *channel1, *channel2, *channel3, *channel4;

protected:

	static Vector3 Projdir;
	static FMOD_VECTOR CameraPosition;
	static FMOD_VECTOR CameraForward;
	static FMOD_VECTOR CameraUp;
	static FMOD_VECTOR CameraVelocity;
	static FMOD_VECTOR LastPosition;

	static FMOD::Sound *Car, *Crash, *Ball, *Wall;
	

	static const int   INTERFACE_UPDATETIME;      // 50ms update for interface
	static const float DISTANCEFACTOR;
	static void   *extradriverdata;

private:

};