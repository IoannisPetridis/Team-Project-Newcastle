#pragma once

#include "AssetsManager.h"
#include "../nclgl/OBJMesh.h"
#include "../nclgl/Mesh.h"
#include "../ncltech/CollisionShape.h"
#include "../ncltech/CuboidCollisionShape.h"
#include "../ncltech/SphereCollisionShape.h"
#include "ActionHandler.h"
#include <ncltech\PhysicsEngine.h>
#include <ncltech\NCLDebug.h>
#include <ncltech\Constraint.h>
#include <ncltech\DistanceConstraint.h>
#include <ncltech\CollisionDetection.h>


class MyScene;

class GameObjectMag {
public:
	void	GOMInit(Scene* m_scene);

protected:
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
