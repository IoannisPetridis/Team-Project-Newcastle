/******************************************************************************
Class: SimpleMeshObject
Implements: GameObject
Author:Pieran Marris <p.marris@newcastle.ac.uk>
Description: A simple game object implementation that has a mesh and an optional texture component
that are rendered to the scene.


(\_/)
( '_')
/""""""""""""\=========     -----D
/"""""""""""""""""""""""\
....\_@____@____@____@____@_/

*//////////////////////////////////////////////////////////////////////////////
#pragma once
#include "GameObject.h"
#include "../Mesh.h"

class SimpleMeshObject : public GameObject
{
public:
	SimpleMeshObject(const std::string& name);
	~SimpleMeshObject();

	void	SetMesh(Mesh* mesh, bool deleteMeshOnCleanup);
	Mesh*	GetMesh()		{ return m_pMesh; }

	void	SetTexture(GLuint tex, bool deleteTexOnCleanup);
	GLuint  GetTexture()	{ return m_Texture; }

	void	SetBumpMap(GLuint tex, bool deleteTexOnCleanup);
	GLuint  GetBumpMap()	{ return m_Texture; }

public:
	virtual void NormalCal();

	void	SetFrontNormal(Vector3 normal) { front_normal = normal; }
	Vector3 GetFrontNormal() { return front_normal; }

	void	SetRearNormal(Vector3 normal) { Rear_normal = normal; }
	Vector3 GetRearNormal() { return Rear_normal; }

	void	SetLeftNormal(Vector3 normal) { Left_normal = normal; }
	Vector3 GetLeftNormal() { return Left_normal; }

	void	SetRightNormal(Vector3 normal) { Right_normal = normal; }
	Vector3 GetRightNormal() { return Right_normal; }

	void	SetTopNormal(Vector3 normal) { Top_normal = normal; }
	Vector3 GetTopNormal() { return Top_normal; }

	void	SetBottomNormal(Vector3 normal) { Bottom_normal = normal; }
	Vector3 GetBottomNormal() { return Bottom_normal; }

protected:
	void	OnRenderObject() override;				//Handles OpenGL calls to Render the object
	void	OnUpdateObject(float dt) override;

protected:
	bool	m_DeleteMeshOnCleanup, m_DeleteTexOnCleanup;

	GLuint  m_Texture;
	GLuint	m_Bumpmap;
	Mesh*	m_pMesh;

protected:

	Vector3 front_normal;
	Vector3 Rear_normal;
	Vector3 Left_normal;
	Vector3 Right_normal;
	Vector3 Top_normal;
	Vector3 Bottom_normal;
};