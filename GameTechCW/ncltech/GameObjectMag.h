//#define Launch

#ifdef Launch

#pragma once
#include "GameObject.h"
#include "SimpleMeshObject.h"
#include "../nclgl/OBJMesh.h"
#include "../nclgl/Mesh.h"

class GameObjectMag {
public:
	void	GOSetting(SimpleMeshObject*& go, Mesh* m, Matrix4& LocalTrans, Vector4& colour,
		float BoundingR);
	void	GOGraphicSetting(bool Effect1, bool Effect2, bool Effect3);
	void	GOphysicsSetting(bool Gravity, bool Collision);
	
	void	BuildNodeLists(GameObject* node, Scene* m_scene);
	void	SortNodeLists();
	void	ClearNodeLists();

	GameObject* FindGameObject(const std::string& name);
protected:

	void		AddGameObject(GameObject* game_object);
	void		RemoveGameObject(GameObject* game_object);

private:
	GameObject*			m_RootGameObject;
};

#endif