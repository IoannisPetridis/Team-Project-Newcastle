#include "CommonMeshes.h"
#include <nclgl\OBJMesh.h>

Mesh* CommonMeshes::m_pPlane	= NULL;
Mesh* CommonMeshes::m_pCube		= NULL;
Mesh* CommonMeshes::m_pSphere	= NULL;
Mesh* CommonMeshes::m_pTardis = NULL;
Mesh* CommonMeshes::m_EmptyBox = NULL;
Mesh* CommonMeshes::m_pTorus = NULL;
Mesh* CommonMeshes::m_pPiramid = NULL;
Mesh* CommonMeshes::m_pAI = NULL;
Mesh* CommonMeshes::m_pBatman= NULL;

GLuint CommonMeshes::m_CheckerboardTex = 0;
GLuint CommonMeshes::m_textureForSphere = 0;
GLuint CommonMeshes::m_textureForAI =0;
GLuint CommonMeshes::m_textureBrick = 0;

void CommonMeshes::InitializeMeshes()
{
	if (m_pPlane == NULL)
	{
		m_CheckerboardTex = SOIL_load_OGL_texture(TEXTUREDIR"checkerboard.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		glBindTexture(GL_TEXTURE_2D, m_CheckerboardTex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); //No linear interpolation to get crisp checkerboard no matter the scalling
		glBindTexture(GL_TEXTURE_2D, 0);

		m_textureForSphere = SOIL_load_OGL_texture(TEXTUREDIR"rainbow.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		glBindTexture(GL_TEXTURE_2D, m_textureForSphere);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); //No linear interpolation to get crisp checkerboard no matter the scalling
		glBindTexture(GL_TEXTURE_2D, 0);

		m_textureForAI = SOIL_load_OGL_texture(TEXTUREDIR"nope2.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		glBindTexture(GL_TEXTURE_2D, m_textureForAI);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); //No linear interpolation to get crisp checkerboard no matter the scalling
		glBindTexture(GL_TEXTURE_2D, 0);

		m_textureBrick = SOIL_load_OGL_texture(TEXTUREDIR"brick.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		glBindTexture(GL_TEXTURE_2D, m_textureBrick);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); //No linear interpolation to get crisp checkerboard no matter the scalling
		glBindTexture(GL_TEXTURE_2D, 0);


		m_pPlane = Mesh::GenerateQuadTexCoordCol(Vector2(1.f, 1.f), Vector2(0.0f, 1.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		m_pCube = new OBJMesh(MESHDIR"cube.obj");
		m_pSphere = new OBJMesh(MESHDIR"sphere.obj");
		m_pPiramid = new OBJMesh(MESHDIR"Piramid3.obj");
		//m_pTorus = new OBJMesh(MESHDIR"Torus.obj");
		m_pTardis = new OBJMesh(MESHDIR"TARDIS.obj");
		m_pAI = new OBJMesh(MESHDIR"sphere.obj");
		m_pBatman = new OBJMesh(MESHDIR"batmanCenter.obj");
		m_EmptyBox = m_pCube;

		m_pPlane->SetTexture(m_CheckerboardTex);
		m_pCube->SetTexture(m_CheckerboardTex);
		m_pSphere->SetTexture(m_textureForSphere);
		m_pPiramid->SetTexture(m_textureBrick);
		m_pAI->SetTexture(m_textureForAI);
		//m_pTorus->SetTexture(m_CheckerboardTex);
	}
}

void CommonMeshes::ReleaseMeshes()
{
	if (m_pPlane != NULL)
	{
		glDeleteTextures(1, &m_CheckerboardTex);
		delete m_pPlane;
		delete m_pCube;
		delete m_pSphere;
		delete m_pTardis;
		delete m_pBatman;
	}

	m_pPlane = NULL;
}