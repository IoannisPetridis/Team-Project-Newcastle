
#include "MyScene.h"


#include <nclgl/OBJMesh.h>
#include <ncltech\Constraint.h>
#include <ncltech\DistanceConstraint.h>
#include <ncltech\SimpleMeshObject.h>
#include <ncltech\PhysicsEngine.h>
#include <ncltech\CommonMeshes.h>
#include <ncltech\NCLDebug.h>
#include <ncltech\CollisionDetection.h>
#include <ncltech\SphereCollisionShape.h>
#include <ncltech\CuboidCollisionShape.h>
#include <ncltech\PiramidCollisionShape.h>
#include <iostream>
#include <mmsystem.h>
#include <windows.h>
#include <../Game Technologies/Tutorial3 - Solver/Player.h>
MyScene::MyScene(Window& window) : Scene(window)
{
	//lock the mouse into the screen
	window.LockMouseToWindow(true);
	if (init == true)
		init = InitialiseGL();

	UpdateWorldMatrices(m_RootGameObject, Matrix4());

	

	//PhysicsEngine::Instance()->SetUpdateTimestep(1.0f / 1.0f);	//1 Update per second

	//PhysicsEngine::Instance()->SetUpdateTimestep(1.0f / 5.0f);	//5 Updates per second

	PhysicsEngine::Instance()->SetUpdateTimestep(1.0f / 60.0f);		//60 Updates per second

	//PhysicsEngine::Instance()->SetUpdateTimestep(1.0f / 100.0f);		//100 Updates per second

}

MyScene::~MyScene()
{
	if (m_TargetTexture)
	{
		glDeleteTextures(1, &m_TargetTexture);
		m_TargetTexture = NULL;
	}
}

bool MyScene::InitialiseGL()
{
	m_Camera->SetPosition(Vector3(-6.25f, 2.0f, 10.0f));
	//PhysicsEngine::Instance()->SetGravity(Vector3(0.0f, 0.0f, 0.0f));
	//set Gravity
	PhysicsEngine::Instance()->SetGravity(Vector3(0.0f, -9.81f, 0.0f));		//No Gravity
	PhysicsEngine::Instance()->SetDampingFactor(0.99f);						//No Damping
	

	m_TargetTexture = SOIL_load_OGL_texture(TEXTUREDIR"target.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, m_TargetTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); //No linear interpolation to get crisp checkerboard no matter the scalling
	glBindTexture(GL_TEXTURE_2D, 0);


	////TORUS
	////Create Ground
	//SimpleMeshObject* Torus = new SimpleMeshObject("Torus");
	//Torus->SetMesh(CommonMeshes::Torus(), false);
	//Torus->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	//Torus->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	//Torus->SetBoundingRadius(80.0f * 80.f);

	//Torus->Physics()->SetPosition(Vector3(0.0f, 20.0f, 0.0f));
	////Torus->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(100.0f, 1.0f, 100.f)));
	////Torus->Physics()->SetIsGlobal(true);
	//this->AddGameObject(Torus);

	
	//////Create Ground
	//SimpleMeshObject* batman = new SimpleMeshObject("batman");
	//batman->SetMesh(CommonMeshes::Batman(), false);
	//batman->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	//batman->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	//batman->SetOldColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	//batman->SetBoundingRadius(2.0f);

	//batman->Physics()->SetPosition(Vector3(0.0f, -99.0f, 0.0f));
	//batman->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 5.0f, 1.0f)));
	//this->AddGameObject(batman);

	//Create a 'Player' (batmobile)
	Player* batmobile = new Player("batmobile");
	batmobile->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	batmobile->SetBoundingRadius(2.0f);
	batmobile->Physics()->SetPosition(Vector3(53.0f, -99.0f, 0.0f));
	batmobile->Physics()->SetElasticity(1.0f);
	this->AddGameObject(batmobile);

	//create AI Object
	SimpleMeshObject* AI = new SimpleMeshObject("AI");
	AI->SetMesh(CommonMeshes::Batman(), false);
	AI->SetLocalTransform(Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));
	AI->SetColour(Vector4(1.0f, 1.f, 1.f, 1.0f));
	AI->SetOldColour(Vector4(1.0f, 1.f, 1.f, 1.0f));
	AI->SetBoundingRadius(1.0f);
	AI->Physics()->SetPosition(Vector3(17.0f, 30.0f, 10.0f));
	AI->Physics()->SetIsAI(true);
	AI->Physics()->SetCollisionShape(new SphereCollisionShape(1.f));
	this->AddGameObject(AI);

		
	////Create Ground
	SimpleMeshObject* floor  = new SimpleMeshObject("floor");
	floor->SetMesh(CommonMeshes::Cube(), false);
	floor->SetLocalTransform(Matrix4::Scale(Vector3(100.0f, 1.0f, 100.f)));
	floor->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	floor->SetOldColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	floor->SetBoundingRadius(80.0f * 80.f);

	floor->Physics()->SetPosition(Vector3(0.0f, -100.0f, 0.0f));
	floor->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(100.0f, 1.0f, 100.f)));
	floor->Physics()->SetIsGlobal(true);
	this->AddGameObject(floor);
	
	////Create Ground
	SimpleMeshObject* skybox = new SimpleMeshObject("sky");
	skybox->SetMesh(CommonMeshes::Cube(), false);
	this->AddGameObject(skybox);

	//////Create Ground
	///*SimpleMeshObject* top = new SimpleMeshObject("top");
	//top->SetMesh(CommonMeshes::Cube(), false);
	//top->SetLocalTransform(Matrix4::Scale(Vector3(100.0f, 1.0f, 100.f)));
	//top->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	//top->SetBoundingRadius(80.0f * 80.f);

	//top->Physics()->SetPosition(Vector3(0.0f, 100.0f, 0.0f));
	//top->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(100.0f, 1.0f, 100.f)));
	//top->Physics()->SetIsGlobal(true);
	//this->AddGameObject(top);*/
	//
	//////Create Ground
	//SimpleMeshObject* rightWall = new SimpleMeshObject("rightWall");
	//rightWall->SetMesh(CommonMeshes::Cube(), false);
	//rightWall->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 100.0f, 100.f)));
	//rightWall->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	//rightWall->SetBoundingRadius(80.0f * 80.f);
	//rightWall->Physics()->SetIsWake(false);

	//rightWall->Physics()->SetPosition(Vector3(100.0f, 0.0f, 0.0f));
	//rightWall->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 100.0f, 100.f)));
	//rightWall->Physics()->SetIsGlobal(true);
	//this->AddGameObject(rightWall);

	//////Create Ground
	//SimpleMeshObject* leftWall = new SimpleMeshObject("leftWall");
	//leftWall->SetMesh(CommonMeshes::Cube(), false);
	//leftWall->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 100.0f, 100.f)));
	//leftWall->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	//leftWall->SetBoundingRadius(80.0f * 80.f);
	//leftWall->Physics()->SetIsWake(false);

	//leftWall->Physics()->SetPosition(Vector3(-100.0f, 0.0f, 0.0f));
	//leftWall->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 100.0f, 100.f)));
	//leftWall->Physics()->SetIsGlobal(true);
	//this->AddGameObject(leftWall);

	//////Create Ground
	//SimpleMeshObject* frontWall = new SimpleMeshObject("frontWall");
	//frontWall->SetMesh(CommonMeshes::Cube(), false);
	//frontWall->SetLocalTransform(Matrix4::Scale(Vector3(100.0f, 100.0f, 1.f)));
	//frontWall->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	//frontWall->SetBoundingRadius(80.0f * 80.f);
	//frontWall->Physics()->SetIsWake(false);

	//frontWall->Physics()->SetPosition(Vector3(0.0f, 0.0f, 100.0f));
	//frontWall->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(100.0f, 100.0f, 1.f)));
	//frontWall->Physics()->SetIsGlobal(true);
	//this->AddGameObject(frontWall);

	//////Create Ground
	//SimpleMeshObject* backWall = new SimpleMeshObject("backWall");
	//backWall->SetMesh(CommonMeshes::Cube(), false);
	//backWall->SetLocalTransform(Matrix4::Scale(Vector3(100.0f, 100.0f, 1.f)));
	//backWall->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	//backWall->SetBoundingRadius(80.0f * 80.f);
	//backWall->Physics()->SetIsWake(false);

	//backWall->Physics()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
	//backWall->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(100.0f, 100.0f, 1.f)));
	//backWall->Physics()->SetIsGlobal(true);
	//this->AddGameObject(backWall);

	////Create Target
	//SimpleMeshObject* target = new SimpleMeshObject("Target");
	//target->SetMesh(CommonMeshes::Cube(), false);
	//target->SetTexture(m_TargetTexture, false);
	//target->SetLocalTransform(Matrix4::Scale(Vector3(0.1f, 2.0f, 2.f)));
	//target->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	//target->SetBoundingRadius(4.0f);

	//target->Physics()->SetPosition(Vector3(0.1f, 2.0f, 0.0f));

	//this->AddGameObject(target);
	//Create Target
	
	
	//------------------------------------------------------------------------------------------------

	
	SimpleMeshObject* tardis = new SimpleMeshObject("Tardis");
	tardis->SetMesh(CommonMeshes::Tardis(), false);
	tardis->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	tardis->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	tardis->SetBoundingRadius(4.0f);
	tardis->Physics()->SetPosition(Vector3(10.0f, -50.0f, 10.0f));
	tardis->Physics()->SetAngularVelocity(Vector3(0,1,0));
	//tardis->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.6f, 5.0f, 1.6f)));
	this->AddGameObject(tardis);

	SimpleMeshObject* tardisLight = new SimpleMeshObject("tardisLight");
	tardisLight->SetMesh(CommonMeshes::EmptyBox(), false);
	tardisLight->SetLocalTransform(Matrix4::Scale(Vector3(0.0f, 0.0f, 0.0f)));
	tardisLight->SetBoundingRadius(1.0f);
	tardisLight->Physics()->SetPosition(tardis->Physics()->GetPosition() + Vector3(0, 5.8, 0));
	tardisLight->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(0.2f, 0.3f, 0.2f)));
	tardisLight->Physics()->SetAngularVelocity(tardis->Physics()->GetAngularVelocity());
	tardisLight->Physics()->SetIsTardis(true);
	tardisLight->Physics()->SetElasticity(0.8f);
	this->AddGameObject(tardisLight);

	SimpleMeshObject* tardisTop = new SimpleMeshObject("tardisTop");
	tardisTop->SetMesh(CommonMeshes::EmptyBox(), false);
	tardisTop->SetLocalTransform(Matrix4::Scale(Vector3(0.0f, 0.0f, 0.0f)));
	tardisTop->SetBoundingRadius(1.0f);
	tardisTop->Physics()->SetPosition(tardis->Physics()->GetPosition() + Vector3(0, 4.0, 0));
	//tardisTop->Physics()->SetPosition(tardis->Physics()->GetPosition() + Vector3(0, 5.25, 0));
	//tardisTop->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.3f, 0.15f, 1.3f)));
	tardisTop->Physics()->SetCollisionShape(new SphereCollisionShape(1.55f));

	//tardisTop->Physics()->SetOrientation(Quaternion::);

	tardisTop->Physics()->SetAngularVelocity(tardis->Physics()->GetAngularVelocity());
	tardisTop->Physics()->SetIsTardis(true);
	tardisTop->Physics()->SetElasticity(0.8f);
	this->AddGameObject(tardisTop);

	SimpleMeshObject* tardisBody = new SimpleMeshObject("tardisBody");
	tardisBody->SetMesh(CommonMeshes::EmptyBox(), false);
	tardisBody->SetLocalTransform(Matrix4::Scale(Vector3(0.0f, 0.0f, 0.0f)));
	tardisBody->SetBoundingRadius(1.0f);
	tardisBody->Physics()->SetPosition(tardis->Physics()->GetPosition() + Vector3(0, 2.5, 0));
	tardisBody->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.55f, 2.5f, 1.55f)));
	tardisBody->Physics()->SetAngularVelocity(tardis->Physics()->GetAngularVelocity());
	tardisBody->Physics()->SetIsTardis(true);
	tardisBody->Physics()->SetElasticity(0.8f);
	this->AddGameObject(tardisBody);

	SimpleMeshObject* protectedBall = new SimpleMeshObject("protectedBall");
	protectedBall->SetMesh(CommonMeshes::EmptyBox(), false);
	protectedBall->SetLocalTransform(Matrix4::Scale(Vector3(0.0f, 0.0f, 0.0f)));
	protectedBall->SetBoundingRadius(1.0f);
	protectedBall->Physics()->SetPosition(tardis->Physics()->GetPosition() + Vector3(0, 2.5, 0));
	protectedBall->Physics()->SetCollisionShape(new SphereCollisionShape(8.f));
	protectedBall->Physics()->SetAngularVelocity(tardis->Physics()->GetAngularVelocity());
	protectedBall->Physics()->SetIsTardis(true);
	protectedBall->Physics()->SetIsProtectedBall(true);
	protectedBall->Physics()->SetElasticity(0.8f);
	this->AddGameObject(protectedBall);
	//------------------------------------------------------------------------------------------------
	
	
	////Create a projectile
	//SimpleMeshObject* m_Sphere = new SimpleMeshObject("Sphere");
	//m_Sphere->SetMesh(CommonMeshes::Sphere(), false);
	//m_Sphere->SetLocalTransform(Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));
	//m_Sphere->SetColour(Vector4(1.0f, 0.2f, 0.5f, 1.0f));
	//m_Sphere->SetBoundingRadius(1.0f);

	//m_Sphere->Physics()->SetPosition(Vector3(-12.5f, 2.0f, 0.f));

	//m_Sphere->Physics()->SetInverseMass(1.f);

	//m_Sphere->Physics()->SetLinearVelocity(Vector3(0.f, 2.5f, 0.0f));
	//m_Sphere->Physics()->SetForce(Vector3(1.f, -1.f, 0.0f));

	//this->AddGameObject(m_Sphere);

	


	//Create the holder
	
	SimpleMeshObject* holder2 = new SimpleMeshObject("holder2");
	holder2->SetMesh(CommonMeshes::Cube(), false);
	holder2->SetLocalTransform(Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));
	holder2->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	holder2->SetBoundingRadius(4.0f);

	//holder2->Physics()->SetAngularVelocity(Vector3(0.0f,1.0f,0.0f));

	holder2->Physics()->SetPosition(Vector3(20.0f, 5.0f, 0.0f));

	this->AddGameObject(holder2);

	//Create a ball for pendulum
	SimpleMeshObject* pendulumBall2 = new SimpleMeshObject("pendulumBall2");
	pendulumBall2->SetMesh(CommonMeshes::Sphere(), false);
	pendulumBall2->SetLocalTransform(Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));
	pendulumBall2->SetColour(Vector4(1.0f, 0.2f, 0.5f, 1.0f));
	pendulumBall2->SetOldColour(Vector4(1.0f, 0.2f, 0.5f, 1.0f));
	pendulumBall2->SetBoundingRadius(0.5f);

	pendulumBall2->Physics()->SetPosition(Vector3(23.0f, 5.0f, 0.f));
	float mass = 1.f;
	pendulumBall2->Physics()->SetInverseMass(1.0f / mass);

	//pendulumBall2->Physics()->SetLinearVelocity(Vector3(0.f, 10.0f, 0.0f));
	//pendulumBall2->Physics()->SetForce(Vector3(0.0f, -100.0f, 0.0f));

	pendulumBall2->Physics()->SetCollisionShape(new SphereCollisionShape(0.5f));
	//pendulumBall2->Physics()->SetInverseInertia(pendulumBall2->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f / mass));


	this->AddGameObject(pendulumBall2);

	DistanceConstraint* pendulum2 = new DistanceConstraint(holder2->Physics(), pendulumBall2->Physics(), holder2->Physics()->GetPosition() , pendulumBall2->Physics()->GetPosition() );
	PhysicsEngine::Instance()->AddConstraint(pendulum2);
	
	
	//-------------------------------------------------------------------------
	//pendulum list
	SimpleMeshObject* topBox = new SimpleMeshObject("topBox");
	topBox->SetMesh(CommonMeshes::Cube(), false);
	topBox->SetLocalTransform(Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));
	topBox->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	topBox->SetBoundingRadius(1.0f);
	topBox->Physics()->SetPosition(Vector3(-15.f, 10.0f, 0.0f));
	this->AddGameObject(topBox);


	SimpleMeshObject* lastObject = topBox;
	for (int i = 1; i <= 10; ++i)
	{
	SimpleMeshObject* pendulumBall2 = new SimpleMeshObject("swing"+to_string(i));
	pendulumBall2->SetMesh(CommonMeshes::Sphere(), false);
	//pendulumBall2->SetMesh(CommonMeshes::Cube(), false);
	pendulumBall2->SetLocalTransform(Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));
	pendulumBall2->SetColour(Vector4(1.0f, 0.2f, 0.5f, 1.0f));
	pendulumBall2->SetBoundingRadius(0.5f);

	pendulumBall2->Physics()->SetPosition(Vector3(-15.f + i * 1.5f, 10.0f, 0.0f));
	//pendulumBall2->Physics()->SetPosition(Vector3(-15.f, 10.0f - i * 1.5f, 0.0f));
	float mass = 1.f;
	pendulumBall2->Physics()->SetInverseMass(1.0f / mass);

	pendulumBall2->Physics()->SetCollisionShape(new SphereCollisionShape(0.5f));
	pendulumBall2->Physics()->SetInverseInertia(pendulumBall2->Physics()->GetCollisionShape()->BuildInverseInertia(1.f));
	//pendulumBall2->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(0.5f, 0.5f, 0.5f)));

	this->AddGameObject(pendulumBall2);


	DistanceConstraint* pendulum2 = new DistanceConstraint(pendulumBall2->Physics(), lastObject->Physics(), pendulumBall2->Physics()->GetPosition(), lastObject->Physics()->GetPosition());
	PhysicsEngine::Instance()->AddConstraint(pendulum2);

	lastObject = pendulumBall2;
	}
	//-------------------------------------------------------------------------

	

	//SimpleMeshObject* plane = new SimpleMeshObject("plane");
	//plane->SetMesh(CommonMeshes::Plane(), false);
	//plane->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	//plane->SetColour(Vector4(1.0f, 0.2f, 0.5f, 1.0f));
	//plane->SetBoundingRadius(4.0f);

	//plane->Physics()->SetPosition(Vector3(-8.0f, 7.0f, 0.f));
	////float mass = 10.f;
	////plane->Physics()->SetInverseMass(1.0f / mass);

	////pendulumBall2->Physics()->SetLinearVelocity(Vector3(0.f, 10.0f, 0.0f));
	////pendulumBall2->Physics()->SetForce(Vector3(0.0f, -100.0f, 0.0f));
	//plane->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.f, 0.2f)));
	////plane->Physics()->SetCollisionShape(new SphereCollisionShape(0.5f));
	////plane->Physics()->SetInverseInertia(pendulumBall2->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f / mass));
	//this->AddGameObject(plane);

	/*SimpleMeshObject* box = new SimpleMeshObject("box");
	box->SetMesh(CommonMeshes::Cube(), false);
	box->SetLocalTransform(Matrix4::Scale(Vector3(5.0f, 1.0f, 5.0f)));
	box->SetColour(Vector4(1.0f, 1.0f, 0.0f, 1.0f));
	box->SetBoundingRadius(4.0f);
	box->Physics()->SetPosition(Vector3(-10.0f, -10.0f, -10.0f));
	box->Physics()->SetAngularVelocity(Vector3(0, 1, 0));
	box->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(5.0f, 1.0f, 5.0f)));
	box->Physics()->SetFriction(2.0f);
	this->AddGameObject(box);*/
	
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				SimpleMeshObject* wallOfBox = new SimpleMeshObject("wallOfBox");
				wallOfBox->SetMesh(CommonMeshes::Cube(), false);
				wallOfBox->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
				wallOfBox->SetColour(Vector4(1.0f, 0.647f, 0.0f, 1.0f));
				wallOfBox->SetOldColour(Vector4(1.0f, 0.647f, 0.0f, 1.0f));
				wallOfBox->SetBoundingRadius(4.0f);
				wallOfBox->Physics()->SetPosition(Vector3(50.0f + (i*2.f), -98.0f + (j*2.f), 10.0f+(k*30.0f)));
				wallOfBox->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));
				wallOfBox->Physics()->SetInverseMass(3.f);
				wallOfBox->Physics()->SetInverseInertia(wallOfBox->Physics()->GetCollisionShape()->BuildInverseInertia(wallOfBox->Physics()->GetInverseMass()));
				wallOfBox->Physics()->SetIsWake(false);
				this->AddGameObject(wallOfBox);
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
			SimpleMeshObject* floatingBall = new SimpleMeshObject("floatingBall");
			floatingBall->SetMesh(CommonMeshes::Sphere(), false);
			floatingBall->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
			floatingBall->SetColour(Vector4(1.0f, 1.0f, 0.0f, 1.0f));
			floatingBall->SetOldColour(Vector4(1.0f, 1.0f, 0.0f, 1.0f));
			floatingBall->SetBoundingRadius(4.0f);
			floatingBall->Physics()->SetPosition(Vector3(-30.0f + (i*-2.5f), 10.0f + (j*2.5f), -10.0f + (k*-2.5f)));
			floatingBall->Physics()->SetCollisionShape(new SphereCollisionShape(1.0f));
			floatingBall->Physics()->SetInverseMass(3.f);
			floatingBall->Physics()->SetInverseInertia(floatingBall->Physics()->GetCollisionShape()->BuildInverseInertia(floatingBall->Physics()->GetInverseMass()));
			floatingBall->Physics()->SetIsWake(false);
			this->AddGameObject(floatingBall);
				//if (i==2&&j==2&&k==2)
				//{
				//	SimpleMeshObject* m_Sphere2 = new SimpleMeshObject("shootBox");
				//	m_Sphere2->SetMesh(CommonMeshes::Sphere(), false);
				//	m_Sphere2->SetLocalTransform(Matrix4::Scale(Vector3(5.f, 5.f, 5.f)));
				//	m_Sphere2->SetColour(Vector4(1.0f, 0.2f, 0.5f, 0.0f));
				//	m_Sphere2->SetBoundingRadius(5.0f);
				//	m_Sphere2->Physics()->SetInverseMass(1.f);
				//	//stack1->Physics()->SetLinearVelocity(Vector3(0.0f, -5.51f, 0.0f));
				//	m_Sphere2->Physics()->SetPosition(Vector3(10.0f + (i*2.5f), 10.0f + (j*2.5f), 10.0f + (k*2.5f)));
				//	m_Sphere2->Physics()->SetCollisionShape(new SphereCollisionShape(8.0f));
				//	m_Sphere2->Physics()->SetInverseInertia(m_Sphere2->Physics()->GetCollisionShape()->BuildInverseInertia(m_Sphere2->Physics()->GetInverseMass()));
				//	m_Sphere2->Physics()->SetIsWake(true);
				//	m_Sphere2->Physics()->SetFriction(2.0f);
				//	m_Sphere2->Physics()->SetElasticity(0.2f);
				//
				//	this->AddGameObject(m_Sphere2);
				//}
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				SimpleMeshObject* floatingBox = new SimpleMeshObject("floatingBox");
				floatingBox->SetMesh(CommonMeshes::Cube(), false);
				floatingBox->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
				floatingBox->SetColour(Vector4(1.0f, 1.0f, 0.0f, 1.0f));
				floatingBox->SetOldColour(Vector4(1.0f, 1.0f, 0.0f, 1.0f));
				floatingBox->SetBoundingRadius(4.0f);
				floatingBox->Physics()->SetPosition(Vector3(-40.0f + (i*-2.5f), 10.0f + (j*2.5f), -10.0f + (k*-2.5f)));
				floatingBox->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));
				floatingBox->Physics()->SetInverseMass(3.f);
				floatingBox->Physics()->SetInverseInertia(floatingBox->Physics()->GetCollisionShape()->BuildInverseInertia(floatingBox->Physics()->GetInverseMass()));
				floatingBox->Physics()->SetIsWake(false);
				this->AddGameObject(floatingBox);
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				SimpleMeshObject* floatingPiramid = new SimpleMeshObject("floatingPiramid");
				floatingPiramid->SetMesh(CommonMeshes::Piramid(), false);
				floatingPiramid->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
				floatingPiramid->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
				floatingPiramid->SetOldColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
				floatingPiramid->SetBoundingRadius(4.0f);
				floatingPiramid->Physics()->SetPosition(Vector3(-50.0f + (i*-2.5f), 10.0f + (j*2.5f), -10.0f + (k*-2.5f)));
				floatingPiramid->Physics()->SetCollisionShape(new PiramidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));
				floatingPiramid->Physics()->SetInverseMass(3.f);
				floatingPiramid->Physics()->SetInverseInertia(floatingPiramid->Physics()->GetCollisionShape()->BuildInverseInertia(floatingPiramid->Physics()->GetInverseMass()));
				floatingPiramid->Physics()->SetIsWake(false);
				this->AddGameObject(floatingPiramid);
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		SimpleMeshObject* stack1 = new SimpleMeshObject("stack1");
		stack1->SetMesh(CommonMeshes::Cube(), false);
		stack1->SetLocalTransform(Matrix4::Scale(Vector3(5.0f, 5.0f, 5.0f)));
		stack1->SetColour(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		stack1->SetOldColour(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		stack1->SetBoundingRadius(4.0f);
		stack1->Physics()->SetPosition(Vector3(10.0f, -95.0f + (i*15.0f), 10.0f));
		stack1->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(5.0f, 5.0f, 5.0f)));
		stack1->Physics()->SetLinearVelocity(Vector3(0.0f, -5.51f, 0.0f));
		stack1->Physics()->SetIsWake(true);
		stack1->Physics()->SetInverseMass(1.f);
		stack1->Physics()->SetInverseInertia(stack1->Physics()->GetCollisionShape()->BuildInverseInertia(stack1->Physics()->GetInverseMass()));
		stack1->Physics()->SetFriction(2.0f);
		stack1->Physics()->SetElasticity(0.05);
		this->AddGameObject(stack1);
	}

	for (int i = 0; i < 4; i++)
	{
		SimpleMeshObject* box1 = new SimpleMeshObject("box1");
		box1->SetMesh(CommonMeshes::Cube(), false);
		box1->SetLocalTransform(Matrix4::Scale(Vector3(5.0f, 5.0f, 5.0f)));
		box1->SetColour(Vector4(0.0f, 1.0f, 0.0f, 1.0f));
		box1->SetOldColour(Vector4(0.0f, 1.0f, 0.0f, 1.0f));
		box1->SetBoundingRadius(4.0f);
		box1->Physics()->SetPosition(Vector3(-20.0f, -90.0f + (i*15.0f), 60.0f));

		if (i == 1)
		{
			box1->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(45, 45, 45));
		}
		if (i == 3)
		{
			box1->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(45, 45, 0));
		}

		box1->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(5.0f, 5.0f, 5.0f)));
		box1->Physics()->SetLinearVelocity(Vector3(0.0f, -5.51f, 0.0f));
		box1->Physics()->SetInverseMass(1.f);
		box1->Physics()->SetIsWake(true);
		box1->Physics()->SetFriction(2.0f);
		box1->Physics()->SetElasticity(0.05);
		box1->Physics()->SetInverseInertia(box1->Physics()->GetCollisionShape()->BuildInverseInertia(box1->Physics()->GetInverseMass()));
		this->AddGameObject(box1);
	}


	return true;
	
}

void MyScene::UpdateScene(float msec)
{
	
	
	Scene::UpdateScene(msec);
	//Draw Score
	NCLDebug::AddStatusEntry(Vector4(1, 0, 0, 1), "Score: %d", PhysicsEngine::Instance()->GetScore());
	//Draw axis X Y Z
	NCLDebug::DrawHairLine(Vector3(0, 0, 0), Vector3(2, 0, 0), Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	NCLDebug::DrawHairLine(Vector3(0, 0, 0), Vector3(0, 2, 0), Vector4(0.0f, 1.0f, 0.0f, 1.0f));
	NCLDebug::DrawHairLine(Vector3(0, 0, 0), Vector3(0, 0, 2), Vector4(0.0f, 0.0f, 1.0f, 1.0f));
	
	GameObject* obj = Scene::FindGameObject("Player1");
	if (obj != NULL)
	{
		Vector3 player_pos = obj->Physics()->GetPosition();
		NCLDebug::Log(Vector3(1.0f, 0.0f, 0.0f), "Player Position - %5.2fm, %5.2fm, %5.2fm\n", player_pos.x, player_pos.y, player_pos.z);
	}

	//Fading
	//change value from 0.0 to 1.0 back and for
	const float animFadeTime = 3; //2.5 Seconds to fade
	float stayTime = 3;
	//if (isDrawFade)
	totalFadeTime += msec;

	//forward way
	if (isFadeIn) //fading back
	{
		stayTime = 2;
		fade = totalFadeTime / animFadeTime;

	}
	else //fading away
	{
		stayTime = 1;
		fade = (animFadeTime - totalFadeTime) / animFadeTime;
	}
	if (totalFadeTime >= animFadeTime)
	{
		if (totalFadeTime >= stayTime + animFadeTime)
		{
			totalFadeTime = 0.0f;
			isFadeIn = !isFadeIn;
		}
	}
	//cout << fade << endl;
	GameObject* tardis = Scene::FindGameObject("Tardis");
	tardis->SetColour(Vector4(1, 1, 1, fade));
	//tardis->SetOldColour(Vector4(1, 1, 1, fade));
	tardis->Physics()->SetAngularVelocity(Vector3(0, 1, 0));
	tardis->Physics()->SetFade(fade);

	GameObject* tardisLight = Scene::FindGameObject("tardisLight");
	tardisLight->Physics()->SetAngularVelocity(tardis->Physics()->GetAngularVelocity());
	tardisLight->Physics()->SetFade(fade);

	GameObject* tardisTop = Scene::FindGameObject("tardisTop");
	tardisTop->Physics()->SetAngularVelocity(tardis->Physics()->GetAngularVelocity());
	tardisTop->Physics()->SetFade(fade);

	GameObject* tardisBody = Scene::FindGameObject("tardisBody");
	tardisBody->Physics()->SetAngularVelocity(tardis->Physics()->GetAngularVelocity());
	tardisBody->Physics()->SetFade(fade);


	GameObject* AI = Scene::FindGameObject("AI");
	
	if (AI->isMove == true)
	{
		AI->Physics()->SetPosition(AI->Physics()->GetPosition() + (AI->direction * speed * elapsed));
		
		if ((AI->Physics()->GetPosition() - AI->start).Length() >= AI->distance)
		{
			AI->Physics()->SetPosition(AI->end);
			AI->isMove = false;
		}
	}


	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_F))
	{
		shootBall();
	}
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_V))
	{
		shootBox();
	}
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_E))
	{
		shootPiramid();
	}
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_J))
	{
		shootBall();
	}
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_K))
	{
		//move the obj from point a to b
		if (speed == 50)
			speed = 0;
		else
			speed = 50;
	}
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_M))
	{
		//loop between 0 1 2 3 4
		if (MyScene::getViewMode() == 4)
			MyScene::setViewMode(0);
		else
			MyScene::setViewMode(MyScene::getViewMode() + 1);

		cout << MyScene::getViewMode();

		if (MyScene::getViewMode() == 0)
		{
			GameObject::isShow = true;
			PhysicsEngine::showOctree = false;
			PhysicsEngine::showManifolds = false;
			PhysicsEngine::showOctree = false;
			PhysicsEngine::showCollision = false;
			PhysicsEngine::showWake = false;
		}
		else if (MyScene::getViewMode() == 1)
		{
			PhysicsEngine::showConstraints = true;
			PhysicsEngine::showCollision = true;
			GameObject::isShow = false;

			PhysicsEngine::showOctree = false;
			PhysicsEngine::showManifolds = false;
			PhysicsEngine::showWake = false;
		}
		else if (MyScene::getViewMode() == 2)
		{
			PhysicsEngine::showManifolds = true;

			PhysicsEngine::showOctree = false;
			PhysicsEngine::showCollision = false;
			GameObject::isShow = true;
			PhysicsEngine::showWake = false;
		}
		else if(MyScene::getViewMode() == 3)
		{
			PhysicsEngine::showOctree = true;

			PhysicsEngine::showManifolds = false;
			GameObject::isShow = true;
			PhysicsEngine::showWake = false;
		}
		else if (MyScene::getViewMode() == 4)
		{
			PhysicsEngine::showWake = true;
			GameObject::isShow = true;
			PhysicsEngine::showOctree = false;
			PhysicsEngine::showManifolds = false;
			PhysicsEngine::showOctree = false;
			PhysicsEngine::showCollision = false;
		}
		

		//NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Scene Update  : %5.2fms", update_ms);
	}	
}

void MyScene::RenderScene()
{
	for (size_t i = 1; i < m_TrajectoryPoints.size(); i++)
	{
		NCLDebug::DrawHairLine(m_TrajectoryPoints[i - 1], m_TrajectoryPoints[i], Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	}

	Scene::RenderScene();
}

void MyScene::shootPiramid()
{
	//Piramid
	SimpleMeshObject* Piramid = new SimpleMeshObject("Piramid");
	Piramid->SetMesh(CommonMeshes::Piramid(), false);
	Piramid->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	Piramid->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	Piramid->SetOldColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	Piramid->SetBoundingRadius(1.5f);

	Piramid->Physics()->SetPosition(m_Camera->GetPosition());
	Piramid->Physics()->SetInverseMass(1.f);
	Piramid->Physics()->SetLinearVelocity(-Vector3(viewMatrix.values[2], viewMatrix.values[6], viewMatrix.values[10]) * 20);

	Piramid->Physics()->SetCollisionShape(new PiramidCollisionShape(Vector3(1.0f, 1.0f, 1.f)));
	Piramid->Physics()->SetInverseInertia(Piramid->Physics()->GetCollisionShape()->BuildInverseInertia(Piramid->Physics()->GetInverseMass()));
	Piramid->Physics()->SetFriction(2.0f);
	Piramid->Physics()->SetElasticity(0.05f);
	
	this->AddGameObject(Piramid);
}


void MyScene::shootBox()
{
	//Create a projectile
	SimpleMeshObject* shootBox = new SimpleMeshObject("shootBox");
	shootBox->SetMesh(CommonMeshes::Cube(), false);
	shootBox->SetLocalTransform(Matrix4::Scale(Vector3(1.f, 1.f, 1.f)));
	shootBox->SetColour(Vector4(1.0f, 0.2f, 0.5f, 1.0f));
	shootBox->SetOldColour(Vector4(1.0f, 0.2f, 0.5f, 1.0f));
	shootBox->SetBoundingRadius(1.5f);

	shootBox->Physics()->SetPosition(m_Camera->GetPosition());

	shootBox->Physics()->SetInverseMass(1.f);
	
	shootBox->Physics()->SetLinearVelocity(-Vector3(viewMatrix.values[2], viewMatrix.values[6], viewMatrix.values[10]) * 20);

	//m_Sphere2->Physics()->SetForce(Vector3(1.f, 0.f, 0.0f));
	//m_Sphere2->Physics()->SetCollisionShape(new SphereCollisionShape(0.5f));
	//m_Sphere2->Physics()->SetInverseInertia(m_Sphere2->Physics()->GetCollisionShape()->BuildInverseInertia(1.f));
	shootBox->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.f, 1.f, 1.f)));
	shootBox->Physics()->SetInverseInertia(shootBox->Physics()->GetCollisionShape()->BuildInverseInertia(shootBox->Physics()->GetInverseMass()));
	shootBox->Physics()->SetFriction(2.0f);
	shootBox->Physics()->SetElasticity(0.05f);
	this->AddGameObject(shootBox);
}

void MyScene::shootBall()
{
	//Create a projectile
	SimpleMeshObject* m_Sphere2 = new SimpleMeshObject("shootSphere");
	m_Sphere2->SetMesh(CommonMeshes::Sphere(), false);
	m_Sphere2->SetLocalTransform(Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));
	m_Sphere2->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_Sphere2->SetOldColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_Sphere2->SetBoundingRadius(0.5f);

	m_Sphere2->Physics()->SetPosition(m_Camera->GetPosition());

	m_Sphere2->Physics()->SetInverseMass(1.f);
	
	m_Sphere2->Physics()->SetLinearVelocity(-Vector3(viewMatrix.values[2], viewMatrix.values[6], viewMatrix.values[10]) * 20);

	//m_Sphere2->Physics()->SetForce(Vector3(1.f, 0.f, 0.0f));
	m_Sphere2->Physics()->SetCollisionShape(new SphereCollisionShape(0.5f));
	//m_Sphere2->Physics()->SetInverseInertia(m_Sphere2->Physics()->GetCollisionShape()->BuildInverseInertia(1.f));
	m_Sphere2->Physics()->SetInverseInertia(m_Sphere2->Physics()->GetCollisionShape()->BuildInverseInertia(m_Sphere2->Physics()->GetInverseMass()));
	this->AddGameObject(m_Sphere2);
	PlaySound(TEXT("sound/shoot.wav"), NULL, SND_ASYNC);
}

void MyScene::shootHook()
{
	//Create a projectile
	SimpleMeshObject* firstBall = new SimpleMeshObject("firstBall");
	firstBall->SetMesh(CommonMeshes::Sphere(), false);
	firstBall->SetLocalTransform(Matrix4::Scale(Vector3(0.2f, 0.2f, 0.2f)));
	firstBall->SetColour(Vector4(1.0f, 0.2f, 0.5f, 1.0f));
	firstBall->SetOldColour(Vector4(1.0f, 0.2f, 0.5f, 1.0f));
	firstBall->SetBoundingRadius(1.0f);

	firstBall->Physics()->SetPosition(m_Camera->GetPosition() - Vector3(0.5f, 0, 0));

	firstBall->Physics()->SetInverseMass(1.f);
	
	//m_Sphere2->Physics()->SetLinearVelocity(Vector3(0.0f, 0.0f, 0.0f));
	firstBall->Physics()->SetLinearVelocity(-Vector3(viewMatrix.values[2], viewMatrix.values[6], viewMatrix.values[10]) * 10);

	//m_Sphere2->Physics()->SetForce(Vector3(1.f, 0.f, 0.0f));

	this->AddGameObject(firstBall);

	//Create a ball for pendulum
	SimpleMeshObject* secondBall = new SimpleMeshObject("secondBall");
	secondBall->SetMesh(CommonMeshes::Sphere(), false);
	secondBall->SetLocalTransform(Matrix4::Scale(Vector3(0.2f, 0.2f, 0.2f)));
	secondBall->SetColour(Vector4(1.0f, 0.2f, 0.5f, 1.0f));
	secondBall->SetOldColour(Vector4(1.0f, 0.2f, 0.5f, 1.0f));
	secondBall->SetBoundingRadius(1.0f);

	secondBall->Physics()->SetPosition(m_Camera->GetPosition() + Vector3(0.5f, 0, 0));
	secondBall->Physics()->SetInverseMass(1.f);

	secondBall->Physics()->SetLinearVelocity(Vector3(0.0f, 0.0f, 0.0f));
	secondBall->Physics()->SetForce(Vector3(0.0f, 0.0f, 0.0f));



	this->AddGameObject(secondBall);

	DistanceConstraint* pendulum4 = new DistanceConstraint(firstBall->Physics(), secondBall->Physics(), firstBall->Physics()->GetPosition(), secondBall->Physics()->GetPosition());
	PhysicsEngine::Instance()->AddConstraint(pendulum4);
}