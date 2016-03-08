#pragma once

#include "AssetsManager.h"
#include "../nclgl/OBJMesh.h"
#include "../nclgl/Mesh.h"
#include "../ncltech/CollisionShape.h"
#include "../ncltech/CuboidCollisionShape.h"
#include "../ncltech/SphereCollisionShape.h"
#include <ncltech\PiramidCollisionShape.h>
#include "ActionHandler.h"
#include <ncltech\PhysicsEngine.h>
#include <ncltech\NCLDebug.h>
#include <ncltech\Constraint.h>
#include <ncltech\DistanceConstraint.h>
#include <ncltech\CollisionDetection.h>


class MyScene;

class GameObjectMag {
public:
	void	GOM_Loading(Scene* m_scene);
	void	GOM_GamePlay(Scene* m_scene);

	void AIStuff(Scene* m_scene);
	void SoloAIStuff(Scene* m_scene);

	void SetID(int i) { id = i; }
	int GetID() const {
		return id;
	}

	bool AIChoice;

protected:
	int id;

	void	GOphysicsSetting(
		bool Gravity,
		bool CollisionCheck
		);

	void	GOGraphicSetting(
		bool Effect1,
		bool Effect2,
		bool Effect3
		);
};
