#pragma once
#include <nclgl\Mesh.h>

class Scene;

//can be used as assets manager

class CommonMeshes
{
	friend class Scene; //Initializes/Destroys the given meshes with it's own lifecycle
public:

	static Mesh* Plane()		{ return m_pPlane; }
	static Mesh* Cube()			{ return m_pCube; }
	static Mesh* Sphere()		{ return m_pSphere; }

protected:
	static void InitializeMeshes();
	static void ReleaseMeshes();

protected:
	static Mesh* m_pCube;
	static Mesh* m_pSphere;
	static Mesh* m_pPlane;

	static GLuint m_CheckerboardTex;
};