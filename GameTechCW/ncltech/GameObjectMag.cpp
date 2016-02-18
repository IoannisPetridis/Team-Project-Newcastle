#include "GameObjectMag.h"

void	GameObjectMag::GOMInit(Scene* m_scene) 
{
	Vector3 Proj_dir;
	Proj_dir.x = -sin(m_scene->m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.z = -cos(m_scene->m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.y = sin(m_scene->m_Camera->GetPitch() * PI / 180.0f);
	Proj_dir.Normalise();

	

	AssetsManager::GOInstance = new SimpleMeshObject("ground1");//Floor
	AssetsManager::GOInstance->SetMesh(AssetsManager::Ground(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 1.0f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.0f, 0.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol1";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 1.0f, 150.0f)));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground2");  //Right Bottom
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 1.0f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol2";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 35.5f, -184.f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 1.0f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(-135, 0, 0));

	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground3"); //Left Bottom
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 1.0f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, -0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
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
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol4";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 91.f, -219.f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 20.0f, 1.0f)));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground5"); //Left Middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 20.0f, 1.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 0));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol5";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 89.f, 219.f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 20.0f, 1.0f)));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground6"); //Left top
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 1.0f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol6";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 145.f, 185.f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 1.0f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(45, 0, 0));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground7"); //Right top
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 1.0f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol7";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 145.5f, -184.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 1.0f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(-45, 0, 0));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground8");// Roof
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(200.f, 1.0f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol8";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 180.f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(200.f, 1.0f, 150.0f)));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	//AssetsManager::GOInstance = new SimpleMeshObject("ground9"); //Back Bottom
	//AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	//AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 50.f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	//AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
	//AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	//AssetsManager::GOInstance->Physics()->name = "groundcol9";
	//AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-235.0f, 35.f, 0.0f));
	//AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 50.f, 150.0f)));
	//AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 45));
	//m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground9_left"); //Back Bottom Left goalside
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 50.f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol9_left";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-235.0f, 35.f, 100.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 50.f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 45));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground9_middle"); //Back Bottom middle goalside
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 20.f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol9_middle";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-256.2f, 56.f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 20.f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 45));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground9_goal_Bottom");// Back Goal Bottom
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.f, 1.0f, 50.f))*Matrix4::Translation(Vector3(0.0f, 0.0f, 0.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "ground9_goal_Bottom";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-214.0f, -14.0f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(20.f, 1.0f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 45));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground9_goal_middle"); //Back Goal middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 30.f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
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
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "ground9_goal_Top";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-257.0f, 27.50f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(20.f, 1.0f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 45));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground9_right"); //Back Bottom right goalside
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 50.f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol9_right";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-235.0f, 35.f, -100.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 50.f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 45));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground10"); //Back Middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 20.f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol10";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-270.0f, 90.f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 20.f, 150.0f)));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground11"); //Back top
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 50.f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol11";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-235.0f, 145.f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 50.f, 150.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 135));
	m_scene->AddGameObject(AssetsManager::GOInstance);



	//AssetsManager::GOInstance = new SimpleMeshObject("ground12"); //Front Bottom
	//AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	//AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 50.f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	//AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
	//AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	//AssetsManager::GOInstance->Physics()->name = "groundcol12";
	//AssetsManager::GOInstance->Physics()->SetPosition(Vector3(235.0F, 35.0F, 0.0f));
	//AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 50.f, 150.0f)));
	//AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, -45));
	//m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground12_left"); //Front Bottom Left goalside
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 50.f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol12_left";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(235.0f, 35.f, 100.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 50.f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, -45));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground12_middle"); //Front Bottom middle goalside
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 20.f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol12_middle";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(255.f, 56.f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 20.f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, -45));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground12_goal_Bottom");// Front Goal Bottom
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.f, 1.0f, 50.f))*Matrix4::Translation(Vector3(0.0f, 0.0f, 0.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "ground12_goal_Bottom";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(214.0f, -14.0f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(20.f, 1.0f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, -45));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground12_goal_middle"); //Front Goal middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 30.f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
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
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "ground12_goal_Top";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(257.0f, 27.0f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(20.f, 1.0f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, -45));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground12_right"); //Front Bottom right goalside
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 50.f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol12_right";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(235.0f, 35.f, -100.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 50.f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, -45));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground13"); //Front Middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 20.f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol13";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(270.0f, 90.f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 20.f, 150.0f)));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground14"); //Front top
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0, 50.f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol14";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(235.0f, 145.f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 50.f, 150.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, -135));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground15"); //Front Right Bottom
	AssetsManager::GOInstance->SetMesh(AssetsManager::Triangle(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.0, 40.f, 40.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f ));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol15";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-217.5f, 36.f, -167.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new PyramidCollisionShape(Vector3(1.0, 44.f, 49.5f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 135, -215));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground16");       //Front Right Middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 20.f, 49.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol16";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-235.0f, 90.5f, -185.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 20.f, 49.f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, -45, -0.f));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground17"); //Front Right Top
	AssetsManager::GOInstance->SetMesh(AssetsManager::Triangle(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.0, 40.f, 40.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol17";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-217.0f, 145.f, -167.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new PyramidCollisionShape(Vector3(1.0, 43.f, 49.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, -45, -35));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground118"); //Front Left Bottom
	AssetsManager::GOInstance->SetMesh(AssetsManager::Triangle(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.0, 40.f, 40.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol18";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-217.0f, 35.f, 167.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new PyramidCollisionShape(Vector3(1.0, 43.f, 49.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, -135, -215));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground19");       //Front Left Middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 20.f, 49.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol19";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-235.0f, 89.5f, 185.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 20.f, 49.f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 45, -0.f));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground20"); //Front Left Top
	AssetsManager::GOInstance->SetMesh(AssetsManager::Triangle(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.0, 40.f, 40.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol20";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(-217.0f, 145.f, 167.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new PyramidCollisionShape(Vector3(1.0, 43.2f, 49.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 45, -35));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground21"); //Back Right Bottom
	AssetsManager::GOInstance->SetMesh(AssetsManager::Triangle(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.0, 40.f, 40.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol21";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(217.0f, 35.f, -167.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new PyramidCollisionShape(Vector3(1.0, 44.f, 49.2f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 45, 145));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground22");       //Back Right Middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 20.f, 49.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol22";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(235.0f, 90.5f, -185.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 20.f, 49.f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, -135, -0.f));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground23"); //Back Right Top
	AssetsManager::GOInstance->SetMesh(AssetsManager::Triangle(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.0, 40.f, 40.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol23";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(217.0f, 145.f, -167.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new PyramidCollisionShape(Vector3(1.0, 43.f, 49.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 225, -35));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground24"); //Back Left Bottom
	AssetsManager::GOInstance->SetMesh(AssetsManager::Triangle(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.0, 40.f, 40.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol24";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(217.0f, 35.f, 167.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new PyramidCollisionShape(Vector3(1.0, 42.5f, 48.8f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, -45, 145));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground25");       //Back Left Middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 20.f, 49.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol25";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(235.0f, 89.5f, 185.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 20.f, 49.f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 135, -0.f));
	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground26"); //Back Left Top
	AssetsManager::GOInstance->SetMesh(AssetsManager::Triangle(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(20.0, 41.f, 40.f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol26";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(217.0f, 145.f, 167.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new PyramidCollisionShape(Vector3(1.0, 44.f, 49.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, -225, -35));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	
	AssetsManager::GOInstance = new SimpleMeshObject("car");  //main
	AssetsManager::GOInstance->SetMesh(AssetsManager::Car(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 0.5f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "car";
	AssetsManager::GOInstance->Physics()->SetInverseMass(0.2f);
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(10.0f, 10.0f, 10.0f));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, -90, 0));
	/*AssetsManager::GOInstance->Physics()->SetCollisionShape(new CylinderCollisionShape(10,10,Vector3(1.0f, 1.0f, 1.0f)));*/
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new SphereCollisionShape(1.0));

	/*AssetsManager::GOInstance->Physics()->name = "car_front_col";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(10.0f, 10.f, 10.f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0, 1.0, 1.0)));
	m_scene->AddGameObject(AssetsManager::GOInstance);*/

	//SimpleMeshObject* wheel1 = new SimpleMeshObject("wheel");
	//wheel1->Physics()->SetPosition(Vector3(10.f, 10.f, 10.f));
	//wheel1->Physics()->SetCollisionShape(new CylinderCollisionShape(10, 3.0, Vector3(10.f, 10.0f, 10.0f)));

	ParticleEmitter* rainbow = new ParticleEmitter();
	rainbow->SetParticleSize(1.0f);
	rainbow->SetParticleVariance(1.0f);
	rainbow->SetLaunchParticles(16.0f);
	rainbow->SetParticleLifetime(100.0f);
	rainbow->SetParticleSpeed(0.1f);

	rainbow->SetSourcePosition(Vector3(10, 10, 10));
	m_scene->AddParticleObject(rainbow);

	/*AssetsManager::GOInstance = new SimpleMeshObject("car");
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "car";
	AssetsManager::GOInstance->Physics()->SetInverseMass(0.2f);
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(10.0f, 10.0f, 10.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));*/

	m_scene->AddGameObject(AssetsManager::GOInstance);
}

