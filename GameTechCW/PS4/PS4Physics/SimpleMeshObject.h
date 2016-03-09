#ifdef _WIN32

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
#include "Vector3.h"

class SimpleMeshObject : public GameObject
{
public:
	SimpleMeshObject(const std::string& name);
	~SimpleMeshObject();

	void	SetMesh(Mesh* mesh, bool deleteMeshOnCleanup);
	Mesh*	GetMesh()		{ return m_pMesh; }

	void	SetTexture(unsigned int tex, bool deleteTexOnCleanup);
	unsigned int  GetTexture()	{ return m_Texture; }

	void	SetBumpMap(unsigned int tex, bool deleteTexOnCleanup);
	unsigned int  GetBumpMap()	{ return m_Texture; }

public:
	virtual void NormalCal();

	void	SetFrontNormal(glm::Vector3 normal) { front_normal = normal; }
	glm::Vector3 GetFrontNormal() { return front_normal; }

	void	SetRearNormal(glm::Vector3 normal) { Rear_normal = normal; }
	glm::Vector3 GetRearNormal() { return Rear_normal; }

	void	SetLeftNormal(glm::Vector3 normal) { Left_normal = normal; }
	glm::Vector3 GetLeftNormal() { return Left_normal; }

	void	SetRightNormal(glm::Vector3 normal) { Right_normal = normal; }
	glm::Vector3 GetRightNormal() { return Right_normal; }

	void	SetTopNormal(glm::Vector3 normal) { Top_normal = normal; }
	glm::Vector3 GetTopNormal() { return Top_normal; }

	void	SetBottomNormal(glm::Vector3 normal) { Bottom_normal = normal; }
	glm::Vector3 GetBottomNormal() { return Bottom_normal; }

protected:
	void	OnRenderObject() override;				//Handles OpenGL calls to Render the object
	void	OnUpdateObject(float dt) override;

protected:
	bool	m_DeleteMeshOnCleanup, m_DeleteTexOnCleanup;

	unsigned int  m_Texture;
	unsigned int  m_Bumpmap;
	Mesh*	m_pMesh;

protected:

	glm::Vector3 front_normal;
	glm::Vector3 Rear_normal;
	glm::Vector3 Left_normal;
	glm::Vector3 Right_normal;
	glm::Vector3 Top_normal;
	glm::Vector3 Bottom_normal;
};

#endif