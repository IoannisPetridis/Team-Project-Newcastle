#include "GameObjectMag.h"

void	GameObjectMag::GOMInit(Scene* m_scene) 
{
	

	Vector3 Proj_dir;
	Proj_dir.x = -sin(m_scene->m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.z = -cos(m_scene->m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.y = sin(m_scene->m_Camera->GetPitch() * PI / 180.0f);
	Proj_dir.Normalise();

	ParticleEmitter* rainbow = new ParticleEmitter();

	rainbow->SetParticleSize(1.0f);
	rainbow->SetParticleVariance(1.0f);
	rainbow->SetLaunchParticles(16.0f);
	rainbow->SetParticleLifetime(100.0f);
	rainbow->SetParticleSpeed(0.1f);

	rainbow->SetSourcePosition(Vector3(10 , 10, 10));
	m_scene->AddParticleObject(rainbow);

	{
		AssetsManager::GOInstance = new SimpleMeshObject("ground");//Floor
		AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
		AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 1.0f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.0f, 0.0f)));
		AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
		AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

		AssetsManager::GOInstance->Physics()->name = "ground";
		AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 1.0f, 150.0f)));
		m_scene->AddGameObject(AssetsManager::GOInstance);

		AssetsManager::GOInstance = new SimpleMeshObject("ground_right_b");  //Right Bottom
		AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
		AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 1.0f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
		AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
		AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

		AssetsManager::GOInstance->Physics()->name = "ground_right_b";
		AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 35.5f, -184.f));
		AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 1.0f, 50.0f)));
		AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(-135, 0, 0));

		m_scene->AddGameObject(AssetsManager::GOInstance);

		AssetsManager::GOInstance = new SimpleMeshObject("ground_left_b"); //Left Bottom
		AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
		AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 1.0f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, -0.f)));
		AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
		AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

		AssetsManager::GOInstance->Physics()->name = "ground_left_b";
		AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 34.f, 184.5f));
		AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 1.0f, 50.0f)));
		AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(135, 0, 0));
		m_scene->AddGameObject(AssetsManager::GOInstance);

		AssetsManager::GOInstance = new SimpleMeshObject("ground_right_m");  //right Middle
		AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
		AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 20.0f, 1.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
		AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 0));
		AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
		AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

		AssetsManager::GOInstance->Physics()->name = "ground_right_m";
		AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 91.f, -219.f));
		AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 20.0f, 1.0f)));
		m_scene->AddGameObject(AssetsManager::GOInstance);


		AssetsManager::GOInstance = new SimpleMeshObject("ground_left_m"); //Left Middle
		AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
		AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 20.0f, 1.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
		AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 0));
		AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
		AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

		AssetsManager::GOInstance->Physics()->name = "groundcol_left_m";
		AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 89.f, 219.f));
		AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 20.0f, 1.0f)));
		m_scene->AddGameObject(AssetsManager::GOInstance);

		AssetsManager::GOInstance = new SimpleMeshObject("ground_left_t"); //Left top
		AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
		AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 1.0f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
		AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
		AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

		AssetsManager::GOInstance->Physics()->name = "ground_left_t";
		AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 145.f, 185.f));
		AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 1.0f, 50.0f)));
		AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(45, 0, 0));
		m_scene->AddGameObject(AssetsManager::GOInstance);


		AssetsManager::GOInstance = new SimpleMeshObject("ground_right_t"); //Right top
		AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
		AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 1.0f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
		AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
		AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

		AssetsManager::GOInstance->Physics()->name = "ground_right_t";
		AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 145.5f, -184.5f));
		AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 1.0f, 50.0f)));
		AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(-45, 0, 0));
		m_scene->AddGameObject(AssetsManager::GOInstance);


		AssetsManager::GOInstance = new SimpleMeshObject("ground_roof");// Roof
		AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
		AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 1.0f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
		AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
		AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

		AssetsManager::GOInstance->Physics()->name = "groundcol_roof";
		AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 180.f, 0.0f));
		AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 1.0f, 150.0f)));
		m_scene->AddGameObject(AssetsManager::GOInstance);

		AssetsManager::GOInstance = new SimpleMeshObject("ground_back_b"); //Back Bottom
		AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
		AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 50.f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
		AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
		AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

		AssetsManager::GOInstance->Physics()->name = "ground_back_b";
		AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-235.0f, 35.f, 0.0f));
		AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 50.f, 150.0f)));
		AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 45));
		m_scene->AddGameObject(AssetsManager::GOInstance);

		AssetsManager::GOInstance = new SimpleMeshObject("ground_back_m"); //Back Middle
		AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
		AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 20.f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
		AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
		AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

		AssetsManager::GOInstance->Physics()->name = "groundcol_back_m";
		AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-270.0f, 90.f, 0.0f));
		AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 20.f, 150.0f)));
		m_scene->AddGameObject(AssetsManager::GOInstance);

		AssetsManager::GOInstance = new SimpleMeshObject("ground_back_t"); //Back top
		AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
		AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 50.f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
		AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
		AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

		AssetsManager::GOInstance->Physics()->name = "groundcol_back_t";
		AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-235.0f, 145.f, 0.0f));
		AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 50.f, 150.0f)));
		AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 135));
		m_scene->AddGameObject(AssetsManager::GOInstance);

		AssetsManager::GOInstance = new SimpleMeshObject("ground_front_b"); //Front bottom
		AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
		AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 50.f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
		AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
		AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

		AssetsManager::GOInstance->Physics()->name = "groundcol_front_b";
		AssetsManager::GOInstance->Physics()->SetPosition(Vector3(235.0F, 35.0F, 0.0f));
		AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 50.f, 150.0f)));
		AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, -45));
		m_scene->AddGameObject(AssetsManager::GOInstance);

		AssetsManager::GOInstance = new SimpleMeshObject("ground_front_m"); //Front Middle
		AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
		AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 20.f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
		AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
		AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

		AssetsManager::GOInstance->Physics()->name = "ground_front_m";
		AssetsManager::GOInstance->Physics()->SetPosition(Vector3(270.0f, 90.f, 0.0f));
		AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 20.f, 150.0f)));
		m_scene->AddGameObject(AssetsManager::GOInstance);


		AssetsManager::GOInstance = new SimpleMeshObject("ground_front_t"); //Front top
		AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
		AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 50.f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
		AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
		AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

		AssetsManager::GOInstance->Physics()->name = "ground_front_t";
		AssetsManager::GOInstance->Physics()->SetPosition(Vector3(235.0f, 145.f, 0.0f));
		AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 50.f, 150.0f)));
		AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, -135));
		m_scene->AddGameObject(AssetsManager::GOInstance);
	}

	AssetsManager::GOInstance = new SimpleMeshObject("car");

	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "car";
	AssetsManager::GOInstance->Physics()->SetInverseMass(0.2f);
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(10.0f, 90.0f, 10.0f));
	//AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(2.0f, 2.0f, 2.0f)));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("box");

	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(5.0f, 5.0f, 5.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "box";
	AssetsManager::GOInstance->Physics()->SetInverseMass(0.2f);
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(10.0f, 170.0f, 10.0f));
	//AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(2.0f, 2.0f, 2.0f)));
	m_scene->AddGameObject(AssetsManager::GOInstance);
	AssetsManager::GOInstance = new SimpleMeshObject("box");

	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(5.0f, 5.0f, 5.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "box";
	AssetsManager::GOInstance->Physics()->SetInverseMass(0.2f);
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(10.0f, 170.0f, 10.0f));
	//AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(2.0f, 2.0f, 2.0f)));
	m_scene->AddGameObject(AssetsManager::GOInstance);
	AssetsManager::GOInstance = new SimpleMeshObject("box");

	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(5.0f, 5.0f, 5.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "box";
	AssetsManager::GOInstance->Physics()->SetInverseMass(0.2f);
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(10.0f, 170.0f, 10.0f));
	//AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(2.0f, 2.0f, 2.0f)));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("box");

	AssetsManager::GOInstance->SetMesh(AssetsManager::Sphere(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(5.0f, 5.0f, 5.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "box";
	AssetsManager::GOInstance->Physics()->SetInverseMass(0.2f);
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(10.0f, 10.0f, 10.0f));
	//AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(2.0f, 2.0f, 2.0f)));
	
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("box");

	AssetsManager::GOInstance->SetMesh(AssetsManager::Sphere(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(5.0f, 5.0f, 5.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "box";
	AssetsManager::GOInstance->Physics()->SetInverseMass(0.2f);
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(20.0f, 10.0f, 10.0f));
	//AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(2.0f, 2.0f, 2.0f)));

	m_scene->AddGameObject(AssetsManager::GOInstance);
	

	//AssetsManager::GOInstance = new SimpleMeshObject("light");

	//AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	//AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	//AssetsManager::GOInstance->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	//AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	//AssetsManager::GOInstance->Physics()->name = "light";
	////AssetsManager::GOInstance->Physics()->SetInverseMass(0.2f);
	////AssetsManager::GOInstance->Physics()->SetPosition(Vector3(10.0f, 10.0f, 10.0f));
	////AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));
	////AssetsManager::GOInstance->Physics()->SetCollisionShape(new SphereCollisionShape(1.0f));
	//m_scene->AddGameObject(AssetsManager::GOInstance);
}

