#include "AssetsManager.h"


//Mesh Assets
Mesh* AssetsManager::m_pPlane	= NULL;
Mesh* AssetsManager::m_pCube	= NULL;
Mesh* AssetsManager::m_pSphere	= NULL;
Mesh* AssetsManager::m_Tardis	= NULL;

//Texture Assets
GLuint AssetsManager::m_CheckerboardTex = 0;
GLuint AssetsManager::m_TargetTexture = 0;
GLuint AssetsManager::m_ThrowTex = 0;
GLuint AssetsManager::m_ThrowTexBUMP = 0;
GLuint AssetsManager::m_Glass = 0;
GLuint AssetsManager::m_GlassBUMP = 0;

//GameObject Assets
SimpleMeshObject* AssetsManager::GOInstance;
SimpleMeshObject* AssetsManager::Camera_Entity;
GameObject* AssetsManager::GOTemp;
Player*	AssetsManager::Player_1;

//Player* Assetsmanager::PlayerInstance;
//AI*	Assetsmanager::AIInstance;
//StaticObject* Assetsmanager::StaticObject;
//DynamicObject* Assetsmanager::DynamicObject;

//Constant
int AssetsManager::Tweat = 1;

void AssetsManager::InitializeMeshes()
{
	m_CheckerboardTex = LoadTexture("checkerboard.tga");
	m_TargetTexture = LoadTexture("target.tga");
	m_ThrowTex = LoadTexture("brick.tga");
	m_Glass = LoadTexture("grass.jpg");
	m_GlassBUMP = LoadTexture("grassDOT.png");
	m_ThrowTexBUMP = LoadTexture("brickDOT.jpg");
	
	
	m_pPlane = Mesh::GenerateQuadTexCoordCol(Vector2(1.f, 1.f), Vector2(0.0f, 1.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_pCube = new OBJMesh(MESHDIR"cube.obj");
	m_pSphere = new OBJMesh(MESHDIR"sphere.obj");
	m_Tardis = new OBJMesh(MESHDIR"tardis.obj");

	m_pPlane->SetTexture(m_CheckerboardTex);
	m_pCube->SetTexture(m_CheckerboardTex);
	m_pSphere->SetTexture(m_CheckerboardTex);
	
}

void AssetsManager::ReleaseMeshes()
{
	if (m_pPlane != NULL)
	{
		glDeleteTextures(1, &m_CheckerboardTex);
		glDeleteTextures(1, &m_TargetTexture);
		glDeleteTextures(1, &m_ThrowTex);
		glDeleteTextures(1, &m_ThrowTexBUMP);
		glDeleteTextures(1, &m_Glass);
		glDeleteTextures(1, &m_GlassBUMP);
		
		delete m_pPlane;
		delete m_pCube;
		delete m_pSphere;
		delete m_Tardis;
	}

	m_pPlane = NULL;
	m_pPlane = NULL;
	m_pCube  = NULL;
	m_pSphere= NULL;
	m_Tardis = NULL;
}

//should be able to modify glTexParameteri 
GLuint AssetsManager::LoadTexture(string Tex_name) {
	GLuint temp = SOIL_load_OGL_texture((TEXTUREDIR + Tex_name).c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, temp);
	glBindTexture(GL_TEXTURE_2D, temp);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); //No linear interpolation to get crisp checkerboard no matter the scalling
	glBindTexture(GL_TEXTURE_2D, 0);
	
	return temp;
}


