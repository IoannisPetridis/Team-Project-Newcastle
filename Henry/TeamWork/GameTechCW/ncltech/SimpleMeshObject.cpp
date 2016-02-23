#include "SimpleMeshObject.h"

SimpleMeshObject::SimpleMeshObject(const std::string& name) :
GameObject(name),
m_DeleteMeshOnCleanup(false),
m_DeleteTexOnCleanup(false),
m_pMesh(NULL),
m_Texture(0)
{
}

SimpleMeshObject::~SimpleMeshObject()
{
	if (m_DeleteMeshOnCleanup && m_pMesh)
	{
		delete m_pMesh;
		m_pMesh = NULL;
	}

	if (m_DeleteTexOnCleanup && m_Texture)
	{
		glDeleteTextures(1, &m_Texture);
		m_Texture = 0;
	}
}

void	SimpleMeshObject::OnUpdateObject(float dt) {

}


void SimpleMeshObject::SetMesh(Mesh* mesh, bool deleteOnCleanup)
{
	m_pMesh = mesh;
	m_DeleteMeshOnCleanup = deleteOnCleanup;

	if (!m_Texture)
	{
		m_Texture = m_pMesh->GetTexture();
	}
}

void SimpleMeshObject::SetTexture(GLuint tex, bool deleteOnCleanup)
{
	m_Texture = tex;
	m_DeleteTexOnCleanup = deleteOnCleanup;
}

void	SimpleMeshObject::OnRenderObject()
{
	if (m_Texture)
	{
		m_pMesh->SetTexture(m_Texture);
		m_pMesh->SetBumpMap(m_Bumpmap);
	}

	m_pMesh->Draw();
}

void SimpleMeshObject::SetBumpMap(GLuint tex, bool deleteOnCleanup)
{
	m_Bumpmap = tex;
	m_DeleteTexOnCleanup = deleteOnCleanup;
}

void SimpleMeshObject::NormalCal() {
	front_normal = this->Physics()->GetOrientation().ToMatrix3() * Vector3(0.0f, 0.0f, -1.0f);
	front_normal.Normalise();
	Rear_normal = this->Physics()->GetOrientation().ToMatrix3() * Vector3(0.0f, 0.0f, 1.0f);
	Rear_normal.Normalise();
	Left_normal = this->Physics()->GetOrientation().ToMatrix3() * Vector3(-1.0f, 0.0f, 0.0f);
	Left_normal.Normalise();
	Right_normal = this->Physics()->GetOrientation().ToMatrix3() * Vector3(1.0f, 0.0f, 0.0f);
	Right_normal.Normalise();
	Top_normal = this->Physics()->GetOrientation().ToMatrix3() * Vector3(0.0f, 1.0f, 0.0f);
	Top_normal.Normalise();
	Bottom_normal = this->Physics()->GetOrientation().ToMatrix3() * Vector3(0.0f, -1.0f, 0.0f);
	Bottom_normal.Normalise();
}