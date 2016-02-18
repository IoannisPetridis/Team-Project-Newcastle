#pragma once
//#include "GameObject.h"
#include "AssetsManager.h"
//#include "SimpleMeshObject.h"
#include "../nclgl/OBJMesh.h"
#include "../nclgl/Mesh.h"
#include "../ncltech/CollisionShape.h"
#include "../ncltech/CuboidCollisionShape.h"
#include "../ncltech/SphereCollisionShape.h"
#include "../ncltech//PyramidCOllisionShape.h"
#include "../ncltech/CylinderCollisionShape.h"
//#include "Scene.h"
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
	
	void	BuildNodeLists(GameObject* node, Scene* m_scene);
	void	SortNodeLists(Scene* m_scene);
	void	ClearNodeLists(Scene* m_scene);

	void		AddGameObject(GameObject* game_object);
	void		RemoveGameObject(GameObject* game_object);

	GameObject* FindGameObject(const std::string& name);

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

	GameObject*	 m_RootGameObject;
};
