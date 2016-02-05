#include "GameObjectMag.h"

void	GameObjectMag::GOMInit(Scene* m_scene) 
{
	Vector3 Proj_dir;
	Proj_dir.x = -sin(m_scene->m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.z = -cos(m_scene->m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.y = sin(m_scene->m_Camera->GetPitch() * PI / 180.0f);
	Proj_dir.Normalise();

	AssetsManager::GOInstance = new SimpleMeshObject("ground");

	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(100.0f, 1.0f, 100.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "ground";
	//AssetsManager::GOInstance->Physics()->SetInverseMass(1.0f);
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, -5.0f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(100.0f, 1.0f, 100.0f)));

	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("car");

	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "car";
	AssetsManager::GOInstance->Physics()->SetInverseMass(0.2f);
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(10.0f, 10.0f, 10.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));

	m_scene->AddGameObject(AssetsManager::GOInstance);
}

