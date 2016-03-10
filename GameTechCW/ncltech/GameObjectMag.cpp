#include "GameObjectMag.h"
#include "PowerUps.h"

void	GameObjectMag::GOM_GamePlay(Scene* m_scene)
{
	Vector3 Proj_dir;
	Proj_dir.x = -sin(m_scene->m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.z = -cos(m_scene->m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.y = sin(m_scene->m_Camera->GetPitch() * PI / 180.0f);
	Proj_dir.Normalise();

	Quaternion rot;

	//Partical
	ParticleEmitter* rainbow = new ParticleEmitter();

	rainbow->SetParticleSize(0.8f);
	rainbow->SetParticleVariance(1.0f);
	rainbow->SetLaunchParticles(5.0f);
	rainbow->SetParticleLifetime(100.0f);
	rainbow->SetParticleSpeed(0.1f);
	rainbow->SetParticleRate(5.f);
	
	rainbow->SetSourcePosition(Vector3(10, 10, 10));
	m_scene->AddParticleObject(rainbow);
	//End


	//SHELF
	AssetsManager::GOInstance = new SimpleMeshObject("ground_shelf");//Floor
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 1.0f, 150.0f)));
	AssetsManager::GOInstance->Physics()->name = "ground_shelf";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, -12.0f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 1.0f, 150.0f)));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	//STADIUM

	AssetsManager::GOInstance = new SimpleMeshObject("ground");//Floor
	AssetsManager::GOInstance->SetMesh(AssetsManager::Ground(), false);
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Field, false);
	//AssetsManager::GOInstance->SetBumpMap(AssetsManager::m_FieldBUMP, false);

	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 2.0f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.0f, 0.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol1";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, -1.0f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 2.0f, 150.0f)));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground2");  //Right Bottom
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	//AssetsManager::GOInstance->SetTexture(AssetsManager::m_Field, false);
	//AssetsManager::GOInstance->SetBumpMap(AssetsManager::m_FieldBUMP, false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 1.0f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.1f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol2";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 35.5f, -184.f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 1.0f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(-135, 0, 0));

	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground3"); //Left Bottom
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 1.0f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, -0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.1f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol3";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 34.f, 184.5f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 1.0f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(135, 0, 0));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground4");  //right Middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 20.0f, 1.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 0));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.1f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol4";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 91.f, -219.f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 20.0f, 1.0f)));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground5"); //Left Middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 20.0f, 1.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 0));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.1f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol5";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 89.f, 219.f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 20.0f, 1.0f)));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground6"); //Left top
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 1.0f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.1f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol6";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 145.f, 185.f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 1.0f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(45, 0, 0));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground7"); //Right top
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 1.0f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.1f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol7";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 145.5f, -184.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 1.0f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(-45, 0, 0));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground8");// Roof
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 1.0f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.1f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol8";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 180.f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 1.0f, 150.0f)));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground9_left"); //Back Bottom Left goalside
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 50.f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.1f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol9_left";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-235.0f, 35.f, 100.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 50.f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 45));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground9_middle"); //Back Bottom middle goalside
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 20.f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.1f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol9_middle";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-256.2f, 56.f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 20.f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 45));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground9_goal_Bottom");// Back Goal Bottom
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(29.f, 1.0f, 50.f))*Matrix4::Translation(Vector3(0.0f, 0.0f, 0.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Blue, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "ground9_goal_Bottom";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-228.0f, 0.0f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(29.f, 1.0f, 50.f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 0));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground9_goal_middle"); //Back Goal middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 30.f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Blue, false); //test
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol9_goal_middle";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-249.f, -08.0f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 30.f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 45));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground9_goal_Right"); //Back Goal Right
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.0, 30.0f, 1.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Blue, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "ground9_goal_Right";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-235.0f, 7.5f, -49.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(20.0, 30.0f, 1.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 45));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground9_goal_Left"); //Back Goal Left
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.0, 30.0f, 1.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Blue, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "ground9_goal_Left";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-234.70f, 7.5f, 49.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(20.0, 30.0f, 1.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 45));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground9_goal_Top");//Back Goal Top
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.f, 1.0f, 50.f))*Matrix4::Translation(Vector3(0.0f, 0.0f, 0.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Blue, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "ground9_goal_Top";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-257.0f, 27.50f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(20.f, 1.0f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 45));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground9_right"); //Back Bottom right goalside
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 50.f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.1f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol9_right";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-235.0f, 35.f, -100.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 50.f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 45));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground10"); //Back Middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 20.f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Blue, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol10";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-270.0f, 90.f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 20.f, 150.0f)));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground11"); //Back top
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 50.f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.1f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol11";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-235.0f, 145.f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 50.f, 150.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 135));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground12_left"); //Front Bottom Left goalside
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 50.f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.1f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol12_left";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(235.0f, 35.f, 100.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 50.f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, -45));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground12_middle"); //Front Bottom middle goalside
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 20.f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.1f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol12_middle";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(255.f, 56.f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 20.f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, -45));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground12_goal_Bottom");// Front Goal Bottom
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(29.f, 1.0f, 50.f))*Matrix4::Translation(Vector3(0.0f, 0.0f, 0.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Red, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "ground12_goal_Bottom";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(228.0f, 0.0f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(29.f, 1.0f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 0));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground12_goal_middle"); //Front Goal middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 30.f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Red, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol12_goal_middle";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(249.f, -08.0f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 30.f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, -45));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground12_goal_Right"); //Front Goal Left
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.0, 30.0f, 1.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Red, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "ground12_goal_Right";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(235.0f, 7.5f, -49.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(20.0, 30.0f, 1.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, -45));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground12_goal_Left"); //Front Goal Right
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.0, 30.0f, 1.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Red, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "ground12_goal_Left";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(235.0f, 7.5f, 50.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(20.0, 30.0f, 1.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, -45));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground12_goal_Top");//Front Goal Top
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.f, 1.0f, 50.f))*Matrix4::Translation(Vector3(0.0f, 0.0f, 0.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Red, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "ground12_goal_Top";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(255.0f, 28.0f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(20.f, 1.0f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, -45));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground12_right"); //Front Bottom right goalside
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 50.f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.1f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol12_right";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(235.0f, 35.f, -100.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 50.f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, -45));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground13"); //Front Middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 20.f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Red, false); //red band between goals
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol13";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(270.0f, 90.f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 20.f, 150.0f)));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground14"); //Front top
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 50.f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.1f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol14";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(235.0f, 145.f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 50.f, 150.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, -135));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground15"); //Front Right Bottom
	AssetsManager::GOInstance->SetMesh(AssetsManager::Triangle(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.0, 40.f, 40.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Blue, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);
	

	AssetsManager::GOInstance->Physics()->name = "groundcol15";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-217.5f, 36.5f, -167.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new PiramidCollisionShape(Vector3(1.0, 44.f, 49.5f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 135, -215));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground16");       //Front Right Middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 20.f, 49.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Blue, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol16";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-235.0f, 90.5f, -185.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 20.f, 49.f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, -45, -0.f));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground17"); //Front Right Top
	AssetsManager::GOInstance->SetMesh(AssetsManager::Triangle(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.0, 40.f, 40.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Blue, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol17";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-217.0f, 145.f, -167.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new PiramidCollisionShape(Vector3(1.0, 43.f, 49.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, -45, -35));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground118"); //Front Left Bottom
	AssetsManager::GOInstance->SetMesh(AssetsManager::Triangle(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.0, 40.f, 40.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Blue, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol18";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-217.0f, 36.f, 167.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new PiramidCollisionShape(Vector3(1.0, 43.f, 49.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, -135, -215));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground19");       //Front Left Middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 20.f, 49.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Blue, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol19";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-235.0f, 89.5f, 185.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 20.f, 49.f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 45, -0.f));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground20"); //Front Left Top
	AssetsManager::GOInstance->SetMesh(AssetsManager::Triangle(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.0, 40.f, 40.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Blue, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol20";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-217.0f, 144.5f, 167.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new PiramidCollisionShape(Vector3(1.0, 43.2f, 49.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 45, -35));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground21"); //Back Right Bottom
	AssetsManager::GOInstance->SetMesh(AssetsManager::Triangle(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.0, 40.f, 40.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Red, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol21";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(217.0f, 36.f, -167.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new PiramidCollisionShape(Vector3(1.0, 44.f, 49.2f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 45, 145));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground22");       //Back Right Middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 20.f, 49.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Red, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol22";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(235.0f, 90.5f, -185.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 20.f, 49.f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, -135, -0.f));
	
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground23"); //Back Right Top
	AssetsManager::GOInstance->SetMesh(AssetsManager::Triangle(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.0, 40.f, 40.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Red, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol23";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(217.0f, 145.f, -167.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new PiramidCollisionShape(Vector3(1.0, 43.f, 49.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 225, -35));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground24"); //Back Left Bottom
	AssetsManager::GOInstance->SetMesh(AssetsManager::Triangle(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.0, 40.f, 40.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Red, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol24";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(217.0f, 35.5f, 167.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new PiramidCollisionShape(Vector3(1.0, 42.5f, 48.8f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, -45, 145));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground25");       //Back Left Middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 20.f, 49.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Red, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol25";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(235.0f, 89.5f, 185.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 20.f, 49.f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 135, -0.f));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground26"); //Back Left Top
	AssetsManager::GOInstance->SetMesh(AssetsManager::Triangle(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.0, 41.f, 40.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetTexture(AssetsManager::m_Red, false);
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol26";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(217.0f, 145.f, 167.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new PiramidCollisionShape(Vector3(1.0, 44.f, 49.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, -225, -35));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	{//Player_1
		AssetsManager::Player_1 = new Player("car");
		//set scene
		AssetsManager::Player_1->SetScene(m_scene);

		//AssetsManager::Player_1->SetMesh(AssetsManager::Car(), false);
		AssetsManager::Player_1->SetMesh(AssetsManager::Cube(), false);
		//settexture&bumpMap
		//AssetsManager::Player_1->SetTexture(AssetsManager::m_BlueCat, false);

		AssetsManager::Player_1->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
		//AssetsManager::Player_1->SetColour(Vector4(0.2f, 10.0f, 0.5f, 1.0f));
		AssetsManager::Player_1->SetBoundingRadius(1.0f * 1.0f);

		AssetsManager::Player_1->Physics()->name = "car";
		AssetsManager::Player_1->Physics()->SetInverseMass(0.1f);
		AssetsManager::Player_1->Physics()->SetPosition(Vector3(-40.0f, 2.0f, 0.0f));
		AssetsManager::Player_1->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));

		Matrix3 inertia(1.0f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 1.0f);

		AssetsManager::Player_1->Physics()->SetInverseInertia(inertia);

		m_scene->AddGameObject(AssetsManager::Player_1);

		//AssetsManager::Wheel = new SimpleMeshObject("wheel");
		//Matrix3 inertia_2(0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.1f);

		//AssetsManager::Wheel->SetMesh(AssetsManager::Sphere(), false);
		//AssetsManager::Wheel->SetLocalTransform(Matrix4::Scale(Vector3(4.0f, 4.0f, 4.0f)));
		//AssetsManager::Wheel->SetColour(Vector4(1.0f, 1.0f, 0.5f, 1.0f));
		//AssetsManager::Wheel->SetBoundingRadius(4.0f * 4.f);

		//AssetsManager::Wheel->Physics()->name = "Wheel";
		//AssetsManager::Wheel->Physics()->SetInverseMass(15.0f);
		//AssetsManager::Wheel->Physics()->SetPosition(Vector3(10.0f, 4.5f, 0.0f));
		//AssetsManager::Wheel->Physics()->SetCollisionShape(
		//	new CylinderCollisionShape(1.0f, 1.0f, Vector3(1.0f, 1.0f, 1.0f)));
		//AssetsManager::Wheel->Physics()->SetInverseInertia(inertia);

		//m_scene->AddGameObject(AssetsManager::Wheel);
	}

	{//ball
		AssetsManager::GOInstance = new SimpleMeshObject("ball");

		AssetsManager::GOInstance->SetMesh(AssetsManager::Sphere(), false);
		AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(4.0f, 4.0f, 4.0f)));
		AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 0.5f, 1.0f));
		AssetsManager::GOInstance->SetBoundingRadius(4.0f * 4.f);

		AssetsManager::GOInstance->Physics()->name = "ball";
		AssetsManager::GOInstance->Physics()->SetInverseMass(10.0f);
		AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 4.5f, 0.0f));
		AssetsManager::GOInstance->Physics()->SetCollisionShape(new SphereCollisionShape(4.0f));
		AssetsManager::GOInstance->Physics()->SetInverseInertia(
		AssetsManager::GOInstance->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f));

		m_scene->AddGameObject(AssetsManager::GOInstance);

		//std::function<bool(PhysicsObject*)> ballHit = [&](PhysicsObject* otherObject){
		//	Vector3 temp;
		//	temp = m_scene->m_RootGameObject->FindGameObject("ball")->Physics()->GetForce();
		//	m_scene->m_RootGameObject->FindGameObject("ball")->Physics()->SetForce(temp - Vector3(0.f, 2.f, 0.f));
		//	return true;
		//};

		//AssetsManager::GOInstance->Physics()->SetOnCollisionCallback(ballHit);
	}

	{//goals for ai
		AssetsManager::GOInstance = new SimpleMeshObject("FriendlyGoal");

		AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
		AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(.01f, .01f, .01f)));
		AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
		AssetsManager::GOInstance->SetBoundingRadius(1.0f * 1.f);

		AssetsManager::GOInstance->Physics()->name = "FriendlyGoal";
		AssetsManager::GOInstance->Physics()->SetInverseMass(0.0f);
		AssetsManager::GOInstance->Physics()->SetPosition(Vector3(200.0f, 2.0f, 0.0f));
		//AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));
		//AssetsManager::GOInstance->Physics()->SetInverseInertia(
		//AssetsManager::GOInstance->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f));

		//AssetsManager::GOInstance->SetTexture(AssetsManager::m_Red, false);
		m_scene->AddGameObject(AssetsManager::GOInstance);

		AssetsManager::GOInstance = new SimpleMeshObject("EnemyGoal");

		AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
		AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(.01f, .01f, .01f)));
		AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
		AssetsManager::GOInstance->SetBoundingRadius(1.0f * 1.f);

		AssetsManager::GOInstance->Physics()->name = "EnemyGoal";
		AssetsManager::GOInstance->Physics()->SetInverseMass(0.0f);
		AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-200.0f, 2.0f, 0.0f));
		//AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));
		//AssetsManager::GOInstance->Physics()->SetInverseInertia(
		//AssetsManager::GOInstance->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f));

		//AssetsManager::GOInstance->SetTexture(AssetsManager::m_Glass, false);
		m_scene->AddGameObject(AssetsManager::GOInstance);
	}

	if (AIChoice) {
		AIStuff(m_scene);
	}
	
	else {
		SoloAIStuff(m_scene);
	}

	PowerUpsLoader();
	PowerUps::AddRandomPowerUp(m_scene, AssetsManager::PowerUpBox1);
	PowerUps::AddRandomPowerUp(m_scene, AssetsManager::PowerUpBox2);
	PowerUps::AddRandomPowerUp(m_scene, AssetsManager::PowerUpBox3);
	PowerUps::AddRandomPowerUp(m_scene, AssetsManager::PowerUpBox4);
	PowerUps::AddRandomPowerUp(m_scene, AssetsManager::PowerUpBox5);
}

void	 GameObjectMag::GOM_Loading(Scene* m_scene) {
	m_scene->m_Camera->SetPosition(Vector3(0.0f, 0.0f, 6.0f));
	m_scene->m_Camera->SetYaw(-180.0f);

	std::string filename = "loading.tga";
	GLuint temp = SOIL_load_OGL_texture((TEXTUREDIR + filename).c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, temp);
	glBindTexture(GL_TEXTURE_2D, temp);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	SimpleMeshObject* ground = new SimpleMeshObject("load");
	ground->SetMesh(Mesh::GenerateQuad(), false);
	ground->SetTexture(temp, false);

	ground->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 200.0f, 0.0f)));
	ground->Physics()->SetPosition(Vector3(0.0f, 0.0f, 5.0f));
	ground->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	ground->SetBoundingRadius(80.0f * 80.f);

	m_scene->AddGameObject(ground);
}

//adds single ai
void GameObjectMag::SoloAIStuff(Scene* m_scene) {
	AssetsManager::SoloAI = new SoloAI("SoloAI", m_scene);
	AssetsManager::SoloAI->SetTexture(AssetsManager::m_Red, false);
	AssetsManager::SoloAI->Physics()->SetCar(true);
	m_scene->AddGameObject(AssetsManager::SoloAI);
}

//adds 3 ai's
void GameObjectMag::AIStuff(Scene* m_scene) {
	{
		AssetsManager::NeutralAI = new NeutralAI("NeutralAI", m_scene);
		AssetsManager::NeutralAI->SetTexture(AssetsManager::m_Red, false);
		AssetsManager::NeutralAI->Physics()->SetCar(true);
		m_scene->AddGameObject(AssetsManager::NeutralAI);

		AssetsManager::DefensiveAI = new DefensiveAI("DefensiveAI", m_scene);
		AssetsManager::DefensiveAI->SetTexture(AssetsManager::m_Red, false);
		AssetsManager::DefensiveAI->Physics()->SetCar(true);
		m_scene->AddGameObject(AssetsManager::DefensiveAI);

		AssetsManager::AggressiveAI = new AggressiveAI("AggressiveAI", m_scene);
		AssetsManager::AggressiveAI->SetTexture(AssetsManager::m_Red, false);
		AssetsManager::AggressiveAI->Physics()->SetCar(true);
		m_scene->AddGameObject(AssetsManager::AggressiveAI);
	}
}

void GameObjectMag::PowerUpsLoader(){

	AssetsManager::PowerUpBox1 = new SimpleMeshObject("powerup");
	AssetsManager::PowerUpBox1->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::PowerUpBox1->SetBoundingRadius(1.0f);
	AssetsManager::PowerUpBox1->SetLocalTransform(Matrix4::Scale(Vector3(1.f, 1.f, 1.f)));
	AssetsManager::PowerUpBox1->SetTexture(AssetsManager::m_CubeTex, false);
	AssetsManager::PowerUpBox1->Physics()->name = "powerup";
	AssetsManager::PowerUpBox1->Physics()->SetInverseMass(0.06f);
	AssetsManager::PowerUpBox1->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.f, 1.f, 1.f)));
	AssetsManager::PowerUpBox1->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f);

	AssetsManager::PowerUpBox2 = new SimpleMeshObject("powerup");
	AssetsManager::PowerUpBox2->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::PowerUpBox2->SetBoundingRadius(1.0f);
	AssetsManager::PowerUpBox2->SetLocalTransform(Matrix4::Scale(Vector3(1.f, 1.f, 1.f)));
	AssetsManager::PowerUpBox2->SetTexture(AssetsManager::m_CubeTex, false);
	AssetsManager::PowerUpBox2->Physics()->name = "powerup";
	AssetsManager::PowerUpBox2->Physics()->SetInverseMass(0.06f);
	AssetsManager::PowerUpBox2->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.f, 1.f, 1.f)));
	AssetsManager::PowerUpBox2->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f);

	AssetsManager::PowerUpBox3 = new SimpleMeshObject("powerup");
	AssetsManager::PowerUpBox3->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::PowerUpBox3->SetBoundingRadius(1.0f);
	AssetsManager::PowerUpBox3->SetLocalTransform(Matrix4::Scale(Vector3(1.f, 1.f, 1.f)));
	AssetsManager::PowerUpBox3->SetTexture(AssetsManager::m_CubeTex, false);
	AssetsManager::PowerUpBox3->Physics()->name = "powerup";
	AssetsManager::PowerUpBox3->Physics()->SetInverseMass(0.06f);
	AssetsManager::PowerUpBox3->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.f, 1.f, 1.f)));
	AssetsManager::PowerUpBox3->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f);

	AssetsManager::PowerUpBox4 = new SimpleMeshObject("powerup");
	AssetsManager::PowerUpBox4->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::PowerUpBox4->SetBoundingRadius(1.0f);
	AssetsManager::PowerUpBox4->SetLocalTransform(Matrix4::Scale(Vector3(1.f, 1.f, 1.f)));
	AssetsManager::PowerUpBox4->SetTexture(AssetsManager::m_CubeTex, false);
	AssetsManager::PowerUpBox4->Physics()->name = "powerup";
	AssetsManager::PowerUpBox4->Physics()->SetInverseMass(0.06f);
	AssetsManager::PowerUpBox4->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.f, 1.f, 1.f)));
	AssetsManager::PowerUpBox4->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f);

	AssetsManager::PowerUpBox5 = new SimpleMeshObject("powerup");
	AssetsManager::PowerUpBox5->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::PowerUpBox5->SetBoundingRadius(1.0f);
	AssetsManager::PowerUpBox5->SetLocalTransform(Matrix4::Scale(Vector3(1.f, 1.f, 1.f)));
	AssetsManager::PowerUpBox5->SetTexture(AssetsManager::m_CubeTex, false);
	AssetsManager::PowerUpBox5->Physics()->name = "powerup";
	AssetsManager::PowerUpBox5->Physics()->SetInverseMass(0.06f);
	AssetsManager::PowerUpBox5->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.f, 1.f, 1.f)));
	AssetsManager::PowerUpBox5->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f);

	AssetsManager::BananaPU = new SimpleMeshObject("powerup_banana");
	AssetsManager::BananaPU->SetMesh(AssetsManager::Banana(), false);
	AssetsManager::BananaPU->SetBoundingRadius(1.0f * 1.f);
	AssetsManager::BananaPU->SetLocalTransform(Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));
	AssetsManager::BananaPU->Physics()->name = "powerup_banana";
	AssetsManager::BananaPU->Physics()->SetInverseMass(0.06f);
	AssetsManager::BananaPU->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(0.5f, 0.5f, 0.5f)));
	AssetsManager::BananaPU->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f);
	AssetsManager::BananaPU->Physics()->SetPosition(Vector3(0.0f, -10.f, 0.f));

	AssetsManager::BananaPU2 = new SimpleMeshObject("powerup_banana1");
	AssetsManager::BananaPU2->SetMesh(AssetsManager::Banana(), false);
	AssetsManager::BananaPU2->SetBoundingRadius(1.0f * 1.f);
	AssetsManager::BananaPU2->SetLocalTransform(Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));
	AssetsManager::BananaPU2->Physics()->name = "powerup_banana1";
	AssetsManager::BananaPU2->Physics()->SetInverseMass(0.06f);
	AssetsManager::BananaPU2->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(0.5f, 0.5f, 0.5f)));
	AssetsManager::BananaPU2->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f);
	AssetsManager::BananaPU2->Physics()->SetPosition(Vector3(20.0f, -10.f, 0.f));

	AssetsManager::BananaPU3 = new SimpleMeshObject("powerup_banana2");
	AssetsManager::BananaPU3->SetMesh(AssetsManager::Banana(), false);
	AssetsManager::BananaPU3->SetBoundingRadius(1.0f * 1.f);
	AssetsManager::BananaPU3->SetLocalTransform(Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));
	AssetsManager::BananaPU3->Physics()->name = "powerup_banana2";
	AssetsManager::BananaPU3->Physics()->SetInverseMass(0.06f);
	AssetsManager::BananaPU3->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(0.5f, 0.5f, 0.5f)));
	AssetsManager::BananaPU3->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f);
	AssetsManager::BananaPU3->Physics()->SetPosition(Vector3(15.0f, -10.f, 0.f));

	AssetsManager::BananaPU4 = new SimpleMeshObject("powerup_banana3");
	AssetsManager::BananaPU4->SetMesh(AssetsManager::Banana(), false);
	AssetsManager::BananaPU4->SetBoundingRadius(1.0f * 1.f);
	AssetsManager::BananaPU4->SetLocalTransform(Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));
	AssetsManager::BananaPU4->Physics()->name = "powerup_banana3";
	AssetsManager::BananaPU4->Physics()->SetInverseMass(0.06f);
	AssetsManager::BananaPU4->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(0.5f, 0.5f, 0.5f)));
	AssetsManager::BananaPU4->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f);
	AssetsManager::BananaPU4->Physics()->SetPosition(Vector3(10.0f, -10.f, 0.f));

	AssetsManager::BananaPU5 = new SimpleMeshObject("powerup_banana4");
	AssetsManager::BananaPU5->SetMesh(AssetsManager::Banana(), false);
	AssetsManager::BananaPU5->SetBoundingRadius(1.0f * 1.f);
	AssetsManager::BananaPU5->SetLocalTransform(Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));
	AssetsManager::BananaPU5->Physics()->name = "powerup_banana4";
	AssetsManager::BananaPU5->Physics()->SetInverseMass(0.06f);
	AssetsManager::BananaPU5->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(0.5f, 0.5f, 0.5f)));
	AssetsManager::BananaPU5->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f);
	AssetsManager::BananaPU5->Physics()->SetPosition(Vector3(5.0f, -10.f, 0.f));

}