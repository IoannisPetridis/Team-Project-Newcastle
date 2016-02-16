#include "GameObjectMag.h"

void	GameObjectMag::GOMInit(Scene* m_scene)
{
	Vector3 Proj_dir;
	Proj_dir.x = -sin(m_scene->m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.z = -cos(m_scene->m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.y = sin(m_scene->m_Camera->GetPitch() * PI / 180.0f);
	Proj_dir.Normalise();

	Quaternion rot;

	//Partical
	ParticleEmitter* rainbow = new ParticleEmitter();
	rainbow->BallHighlightLine();
	rainbow->SetSourcePosition(Vector3(10, 10, 10));
	m_scene->AddParticleObject(rainbow);
	//End

	ParticleEmitter* crash = new ParticleEmitter();
	crash->CrashSpark();
	crash->TrigleOnOff();
	crash->SetSourcePosition(Vector3(10, 20, 10));
	m_scene->AddParticleObject(crash);

{
		
	AssetsManager::GOInstance = new SimpleMeshObject("ground");//Floor
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Glass, false);
	AssetsManager::GOInstance->SetBumpMap(AssetsManager::m_GlassBUMP, false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 1.0f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.0f, 0.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
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


	{//Player_1
		AssetsManager::Player_1 = new Player("car");
		//set scene
		AssetsManager::Player_1->SetScene(m_scene);

		AssetsManager::Player_1->SetMesh(AssetsManager::Cube(), false);
		//settexture&bumpMap
		AssetsManager::Player_1->SetTexture(AssetsManager::m_ThrowTex, false);
		AssetsManager::Player_1->SetBumpMap(AssetsManager::m_ThrowTexBUMP, false);
		//
		AssetsManager::Player_1->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
		AssetsManager::Player_1->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
		AssetsManager::Player_1->SetBoundingRadius(1.0f * 1.0f);

		AssetsManager::Player_1->Physics()->name = "car";
		AssetsManager::Player_1->Physics()->SetInverseMass(0.06f);
		AssetsManager::Player_1->Physics()->SetPosition(Vector3(10.0f, 10.0f, 10.0f));
		AssetsManager::Player_1->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));
		
		Matrix3 inertia(1.0f, 0.0f, 0.0f, 0.0f, 1.1f, 0.0f, 0.0f, 0.0f, 1.1f);
		
		AssetsManager::Player_1->Physics()->SetInverseInertia(inertia);
		//AssetsManager::Player_1->Physics()->SetInverseInertia(
		//	AssetsManager::Player_1->Physics()->GetCollisionShape()->BuildInverseInertia(1.f));

		m_scene->AddGameObject(AssetsManager::Player_1);
	}

	AssetsManager::GOInstance = new SimpleMeshObject("cube");

	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(1.0f * 1.f);

	AssetsManager::GOInstance->Physics()->name = "cube";
	AssetsManager::GOInstance->Physics()->SetInverseMass(0.06f);
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(10.0f, 10.0f, 10.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(2.0f, 2.0f, 2.0f)));
	AssetsManager::GOInstance->Physics()->SetInverseInertia(
		AssetsManager::GOInstance->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f));

	m_scene->AddGameObject(AssetsManager::GOInstance);

	{//ball
		AssetsManager::GOInstance = new SimpleMeshObject("ball");

		AssetsManager::GOInstance->SetMesh(AssetsManager::Sphere(), false);
		AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(4.0f, 4.0f, 4.0f)));
		AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 0.5f, 1.0f));
		AssetsManager::GOInstance->SetBoundingRadius(1.0f * 1.f);

		AssetsManager::GOInstance->SetTexture(AssetsManager::m_ThrowTex, false);

		AssetsManager::GOInstance->Physics()->name = "ball";
		AssetsManager::GOInstance->Physics()->SetInverseMass(0.06f);
		AssetsManager::GOInstance->Physics()->SetPosition(Vector3(10.0f, 5.0f, 10.0f));
		AssetsManager::GOInstance->Physics()->SetCollisionShape(new SphereCollisionShape(4.0f));
		AssetsManager::GOInstance->Physics()->SetInverseInertia(
			AssetsManager::GOInstance->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f));

		m_scene->AddGameObject(AssetsManager::GOInstance);
	}

	{//Camera
		AssetsManager::Camera_Entity = new SimpleMeshObject("Camera_Entity");
		AssetsManager::Camera_Entity->Physics()->name = "Camera_Entity";
		AssetsManager::Camera_Entity->Physics()->SetInverseMass(1.0f);
		AssetsManager::Camera_Entity->Physics()->SetPosition(m_scene->m_Camera->GetPosition());
		AssetsManager::Camera_Entity->Physics()->SetCollisionShape(new SphereCollisionShape(0.7f));
	}
}

