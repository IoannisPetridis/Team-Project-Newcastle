#pragma once
#include "../nclgl/Mesh.h"
#include "../nclgl/OBJMesh.h"
#include "SimpleMeshObject.h"


class Scene;

//can be used as assets manager
//pre-load all the assets as Mesh*

class AssetsManager
{
	friend class Scene; //Initializes/Destroys the given meshes with it's own lifecycle
public:

	static Mesh* Plane()		{ return m_pPlane; }
	static Mesh* Cube()			{ return m_pCube; }
	static Mesh* Sphere()		{ return m_pSphere; }
	static Mesh* Tardis()		{ return m_Tardis; }

	static GLuint m_CheckerboardTex;
	static GLuint m_TargetTexture;
	static GLuint m_ThrowTex;

	static SimpleMeshObject* GOInstance;

	//AssetsLoader:
	static GLuint LoadTexture(string Tex_name);
	static Mesh* LoadMesh(string Mesh_name, string type);
	static OBJMesh* LoadOBJMesh(string Mesh_name);

protected:
	static void InitializeMeshes();
	static void ReleaseMeshes();

protected:
	static Mesh* m_pCube;
	static Mesh* m_pSphere;
	static Mesh* m_pPlane;
	static Mesh* m_Tardis;


};