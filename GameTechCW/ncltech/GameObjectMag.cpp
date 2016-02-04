#include "GameObjectMag.h"

void	GameObjectMag::GOMInit(Scene* m_scene) 
{
	Vector3 Proj_dir;
	Proj_dir.x = -sin(m_scene->m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.z = -cos(m_scene->m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.y = sin(m_scene->m_Camera->GetPitch() * PI / 180.0f);
	Proj_dir.Normalise();

	AssetsManager::GOIstance = new SimpleMeshObject("ground");

	AssetsManager::GOIstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOIstance->SetLocalTransform(Matrix4::Scale(Vector3(5.0f, 5.0f, 5.0f)));
	AssetsManager::GOIstance->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	AssetsManager::GOIstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOIstance->Physics()->name = "ground";
	AssetsManager::GOIstance->Physics()->SetInverseMass(0.5f);
	AssetsManager::GOIstance->Physics()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	AssetsManager::GOIstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(5.0f, 5.0f, 5.0f)));

	m_scene->AddGameObject(AssetsManager::GOIstance);


	AssetsManager::GOIstance = new SimpleMeshObject("car");

	AssetsManager::GOIstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOIstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	AssetsManager::GOIstance->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	AssetsManager::GOIstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOIstance->Physics()->name = "car";
	AssetsManager::GOIstance->Physics()->SetInverseMass(0.5f);
	AssetsManager::GOIstance->Physics()->SetPosition(m_scene->m_Camera->GetPosition()
		+ (Proj_dir * 1.5));
	AssetsManager::GOIstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));

	m_scene->AddGameObject(AssetsManager::GOIstance);
}

