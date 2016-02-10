#include "GameObjectMag.h"

void	GameObjectMag::GOMInit(Scene* m_scene,
	SimpleMeshObject*&	m_Sphere,
	SimpleMeshObject*&	throw_S,
	SimpleMeshObject*&	target,
	SimpleMeshObject*&	goal,
	Plane*&				plane) {

for (int i = 0; i < 10; i++)
	{
	ParticleEmitter* rainbow = new ParticleEmitter();
	rainbow->setTextureToBall();
	rainbow->SetParticleSize(1.0f);
	rainbow->SetParticleVariance(1.0f);
	rainbow->SetLaunchParticles(16.0f);
	rainbow->SetParticleLifetime(100.0f);
	rainbow->SetParticleSpeed(0.1f);
	
	rainbow->SetSourcePosition(Vector3(10+(i*10), 10, 10));
	m_scene->AddParticleObject(rainbow);
	}

	SimpleMeshObject* ground = new SimpleMeshObject("Ground");

	ground->SetMesh(AssetsManager::Cube(), false);
	ground->SetLocalTransform(Matrix4::Scale(Vector3(34.0f, 2.0f, 34.0f)));
	ground->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	ground->SetBoundingRadius(80.0f * 80.f);

	ground->Physics()->name = "ground";
	ground->Physics()->SetPosition(Vector3(-6.25f, -2.0f, 0.0f));
	ground->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(34.0f, 2.0f, 34.0f)));

	m_scene->AddGameObject(ground);

	//Plane in Rest State
	target = new SimpleMeshObject("mPlane");
	target->SetMesh(AssetsManager::Cube(), false);
	target->SetTexture(AssetsManager::m_TargetTexture, false);
	target->SetLocalTransform(Matrix4::Scale(Vector3(0.1f, 2.0f, 2.f)));
	target->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	target->SetBoundingRadius(4.0f);

	target->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(0.1f, 2.0f, 2.f)));
	target->Physics()->SetInverseMass(0.02f);
	target->Physics()->SetInverseInertia(target->Physics()->GetCollisionShape()->BuildInverseInertia(0.02f));
	target->Physics()->SetPosition(Vector3(0.0f, 10.0f, -15.0f));

	Vector3 planeNormal = Vector3(-1, 0, 0);
	plane = new Plane(planeNormal, Vector3::Dot(planeNormal, target->Physics()->GetPosition()));

	//toggle to stop UpdatePhysicsObject function, when collision happened, toggle again to reactivate
	target->Physics()->ToggleEnable();
	m_scene->AddGameObject(target);

	target = new SimpleMeshObject("mPlane_contrast");
	target->SetMesh(AssetsManager::Cube(), false);
	target->SetTexture(AssetsManager::m_TargetTexture, false);
	target->SetLocalTransform(Matrix4::Scale(Vector3(0.1f, 2.0f, 2.f)));
	target->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	target->SetBoundingRadius(4.0f);

	target->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(0.1f, 2.0f, 2.f)));
	target->Physics()->SetInverseMass(0.02f);
	target->Physics()->SetInverseInertia(target->Physics()->GetCollisionShape()->BuildInverseInertia(0.02f));
	target->Physics()->SetPosition(Vector3(0.0f, 10.0f, -22.0f));

	target->Physics()->ToggleEnable();
	m_scene->AddGameObject(target);

	//Sphere in Rest State
	m_Sphere = new SimpleMeshObject("mSphere");

	m_Sphere->SetMesh(AssetsManager::Sphere(), false);
	m_Sphere->SetLocalTransform(Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));
	m_Sphere->SetColour(Vector4(1.0f, 0.2f, 0.5f, 1.0f));
	m_Sphere->SetBoundingRadius(1.0f);

	m_Sphere->Physics()->SetPosition(Vector3(0.0f, 10.0f, -12.f));
	m_Sphere->Physics()->SetCollisionShape(new SphereCollisionShape(0.5f));
	m_Sphere->Physics()->SetInverseMass(1.f);
	m_Sphere->Physics()->SetInverseInertia(m_Sphere->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f));

	m_Sphere->Physics()->ToggleEnable();
	m_scene->AddGameObject(m_Sphere);

	m_Sphere = new SimpleMeshObject("mSphere_contrast");
	m_Sphere->SetMesh(AssetsManager::Sphere(), false);
	m_Sphere->SetLocalTransform(Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));
	m_Sphere->SetColour(Vector4(1.0f, 0.2f, 0.5f, 1.0f));
	m_Sphere->SetBoundingRadius(1.0f);

	m_Sphere->Physics()->SetPosition(Vector3(0.0f, 10.0f, -10.f));
	m_Sphere->Physics()->SetCollisionShape(new SphereCollisionShape(0.5f));
	m_Sphere->Physics()->SetInverseMass(1.f);
	m_Sphere->Physics()->SetInverseInertia(m_Sphere->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f));

	m_Sphere->Physics()->ToggleEnable();
	m_scene->AddGameObject(m_Sphere);

	//box
	{
		target = new SimpleMeshObject("box");
		target->SetMesh(AssetsManager::Cube(), false);
		target->SetLocalTransform(Matrix4::Scale(Vector3(0.1f, 2.0f, 2.f)));
		target->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		target->SetBoundingRadius(4.0f);

		target->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(0.1f, 2.0f, 2.f)));
		target->Physics()->SetInverseMass(0.0002f);
		target->Physics()->SetInverseInertia(target->Physics()->GetCollisionShape()->BuildInverseInertia(0.0002f));
		target->Physics()->SetPosition(Vector3(10.0f, 2.0f, -15.0f));
		m_scene->AddGameObject(target);
		target = new SimpleMeshObject("box");
		target->SetMesh(AssetsManager::Cube(), false);
		target->SetLocalTransform(Matrix4::Scale(Vector3(0.1f, 2.0f, 2.f)));
		target->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		target->SetBoundingRadius(4.0f);

		target->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(0.1f, 2.0f, 2.f)));
		target->Physics()->SetInverseMass(0.0002f);
		target->Physics()->SetInverseInertia(target->Physics()->GetCollisionShape()->BuildInverseInertia(0.0002f));
		target->Physics()->SetPosition(Vector3(8.0f, 2.0f, -17.0f));
		Quaternion rot = target->Physics()->GetOrientation() *
			Quaternion::AxisAngleToQuaterion(Vector3(0.0f, 1.0f, 0.0f), 90.0f);
		target->Physics()->SetOrientation(rot);
		m_scene->AddGameObject(target);
		target = new SimpleMeshObject("box");
		target->SetMesh(AssetsManager::Cube(), false);
		target->SetLocalTransform(Matrix4::Scale(Vector3(0.1f, 2.0f, 2.f)));
		target->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		target->SetBoundingRadius(4.0f);

		target->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(0.1f, 2.0f, 2.f)));
		target->Physics()->SetInverseMass(0.0002f);
		target->Physics()->SetInverseInertia(target->Physics()->GetCollisionShape()->BuildInverseInertia(0.0002f));
		target->Physics()->SetPosition(Vector3(8.0f, 2.0f, -13.0f));
		rot = target->Physics()->GetOrientation() *
			Quaternion::AxisAngleToQuaterion(Vector3(0.0f, 1.0f, 0.0f), 90.0f);
		target->Physics()->SetOrientation(rot);
		m_scene->AddGameObject(target);
		target = new SimpleMeshObject("box");
		target->SetMesh(AssetsManager::Cube(), false);
		target->SetLocalTransform(Matrix4::Scale(Vector3(0.1f, 2.0f, 2.f)));
		target->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		target->SetBoundingRadius(4.0f);

		target->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(0.1f, 2.0f, 2.f)));
		target->Physics()->SetInverseMass(0.0002f);
		target->Physics()->SetInverseInertia(target->Physics()->GetCollisionShape()->BuildInverseInertia(0.0002f));
		target->Physics()->SetPosition(Vector3(8.0f, 4.2f, -15.0f));
		rot = target->Physics()->GetOrientation() *
			Quaternion::AxisAngleToQuaterion(Vector3(0.0f, 0.0f, 1.0f), 90.0f);
		target->Physics()->SetOrientation(rot);
		m_scene->AddGameObject(target);
	}

	//The goal
	Vector3 Target_Pos = Vector3(0.0f, 4.0f, 0.0f);

	goal = new SimpleMeshObject("goal_shape");
	goal->SetMesh(AssetsManager::Tardis(), false);
	goal->SetLocalTransform(Matrix4::Scale(Vector3(0.75f, 0.75f, 0.75f)));
	goal->SetColour(Vector4(0.2f, 0.2f, 1.0f, 1.0f));
	goal->SetBoundingRadius(2.5f);
	goal->Physics()->SetPosition(Target_Pos - Vector3(0.0f, 1.5f, 0.0f));
	m_scene->AddGameObject(goal);

	goal = new SimpleMeshObject("goal");
	goal->SetMesh(AssetsManager::Cube(), false);
	goal->SetLocalTransform(Matrix4::Scale(Vector3(0.0f, 0.0f, 0.0f)));
	goal->SetColour(Vector4(0.0f, 0.0f, 0.0f, 0.0f));
	goal->Physics()->SetPosition(Target_Pos + Vector3(0.0f, 0.5f, 0.0f));
	goal->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 2.0f, 1.0f)));
	m_scene->AddGameObject(goal);

	goal = new SimpleMeshObject("bulb");
	goal->SetMesh(AssetsManager::Cube(), false);
	goal->SetColour(Vector4(0.0f, 0.0f, 0.0f, 0.0f));
	goal->SetLocalTransform(Matrix4::Scale(Vector3(0.0f, 0.0f, 0.0f)));
	goal->Physics()->SetPosition(Target_Pos + Vector3(0.0f, 2.7f, 0.0f));
	goal->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(0.1f, 0.15f, 0.1f)));
	m_scene->AddGameObject(goal);

	//The goal keeper
	target = new SimpleMeshObject("gk");
	target->SetMesh(AssetsManager::Cube(), false);
	target->SetTexture(AssetsManager::m_TargetTexture, false);
	target->SetLocalTransform(Matrix4::Scale(Vector3(0.1f, 0.7f, 0.7f)));
	target->SetColour(Vector4(0.4f, 0.4f, 0.6f, 1.0f));
	target->SetBoundingRadius(2.0f);

	Vector3 GK_Init_Pos = Vector3(-4.0f, 5.3f, 0.0f);
	target->Physics()->SetPosition(Vector3(-4.0f, 5.5f, 0.0f));
	target->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(0.1f, 0.7f, 0.7f)));
	target->Physics()->SetInverseMass(0.05f);
	target->Physics()->colarch.push_back(false);
	m_scene->AddGameObject(target);

	SimpleMeshObject* point = new SimpleMeshObject("point");
	point->SetMesh(AssetsManager::Sphere(), false);
	point->SetLocalTransform(Matrix4::Scale(Vector3(0.001f, 0.001f, 0.001f)));
	point->SetColour(Vector4(0.1f, 0.1f, 0.1f, 0.0f));
	point->SetBoundingRadius(0.1f);

	point->Physics()->SetPosition(Target_Pos + Vector3(-2.3f, 2.0f, 0.0f));
	m_scene->AddGameObject(point);

	

	DistanceConstraint* cons = new DistanceConstraint(m_scene->m_RootGameObject->FindGameObject("point")->Physics(),
		m_scene->m_RootGameObject->FindGameObject("gk")->Physics(),
		m_scene->m_RootGameObject->FindGameObject("point")->Physics()->GetPosition(),
		m_scene->m_RootGameObject->FindGameObject("gk")->Physics()->GetPosition());
	cons->softness = 5.0f;
	PhysicsEngine::Instance()->AddConstraint(cons);

	point = new SimpleMeshObject("point_2");
	point->SetMesh(AssetsManager::Sphere(), false);
	point->SetLocalTransform(Matrix4::Scale(Vector3(0.001f, 0.001f, 0.001f)));
	point->SetColour(Vector4(0.1f, 0.1f, 0.1f, 0.0f));
	point->SetBoundingRadius(0.1f);

	point->Physics()->SetPosition(Target_Pos + Vector3(-2.3f, 0.5f, 0.0f));
	m_scene->AddGameObject(point);

	DistanceConstraint* cons_5 = new DistanceConstraint(m_scene->m_RootGameObject->FindGameObject("point_2")->Physics(),
		m_scene->m_RootGameObject->FindGameObject("gk")->Physics(),
		m_scene->m_RootGameObject->FindGameObject("point_2")->Physics()->GetPosition(),
		m_scene->m_RootGameObject->FindGameObject("gk")->Physics()->GetPosition());
	cons->softness = 40.0f;
	PhysicsEngine::Instance()->AddConstraint(cons_5);

	//tardis structure
	{
		Vector3 offset = Vector3(0.0f, 2.0f, 0.0f);
		float softness_offset = 2.0f;

		throw_S = new SimpleMeshObject("tardis_top");
		throw_S->SetMesh(AssetsManager::Cube(), false);
		throw_S->SetColour(Vector4(1.0f, 0.3f, 0.5f, 0.0f));
		throw_S->SetBoundingRadius(1.0f);
		throw_S->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 0.2f, 1.0f)));
		throw_S->Physics()->SetPosition(Vector3(-20.0f, 2.8f, 0.0f) + offset);
		throw_S->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 0.2f, 1.0f)));

		std::vector<GameObject*> subshapes;
		subshapes.push_back(throw_S);
		m_scene->AddGameObject(throw_S);
		SimpleMeshObject* lastObject = throw_S;

		throw_S = new SimpleMeshObject("tardis_body");
		throw_S->SetMesh(AssetsManager::Cube(), false);
		throw_S->SetColour(Vector4(1.0f, 0.3f, 0.5f, 0.0f));
		throw_S->SetBoundingRadius(1.0f);
		throw_S->SetLocalTransform(Matrix4::Scale(Vector3(0.7f, 1.1f, 0.7f)));

		throw_S->Physics()->SetPosition(Vector3(-20.0f, 1.5f, 0.0f) + offset);
		throw_S->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(0.7f, 1.1f, 0.7f)));

		throw_S->Physics()->SetInverseInertia(
			throw_S->Physics()->GetCollisionShape()->BuildInverseInertia(2.0f));

		subshapes.push_back(throw_S);
		m_scene->AddGameObject(throw_S);

		DistanceConstraint* cons_1 = new DistanceConstraint(throw_S->Physics(), lastObject->Physics(),
			throw_S->Physics()->GetPosition() + Vector3(0.7f, 0.0f, 0.0f),
			lastObject->Physics()->GetPosition() + Vector3(0.7f, 0.0f, 0.0f));
		cons->softness = softness_offset;
		PhysicsEngine::Instance()->AddConstraint(cons_1);

		DistanceConstraint* cons_2 = new DistanceConstraint(throw_S->Physics(), lastObject->Physics(),
			throw_S->Physics()->GetPosition() + Vector3(-0.7f, 0.0f, 0.0f),
			lastObject->Physics()->GetPosition() + Vector3(-0.7f, 0.0f, 0.0f));
		cons->softness = softness_offset;
		PhysicsEngine::Instance()->AddConstraint(cons_2);
		lastObject = throw_S;

		throw_S = new SimpleMeshObject("tardis_bot");
		throw_S->SetMesh(AssetsManager::Cube(), false);
		throw_S->SetColour(Vector4(1.0f, 0.3f, 0.5f, 0.0f));
		throw_S->SetBoundingRadius(1.0f);
		throw_S->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 0.2f, 1.0f)));
		throw_S->Physics()->SetPosition(Vector3(-20.0f, 0.2f, 0.0f) + offset);
		throw_S->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 0.2f, 1.0f)));

		throw_S->Physics()->SetInverseInertia(
			throw_S->Physics()->GetCollisionShape()->BuildInverseInertia(2.0f));

		subshapes.push_back(throw_S);
		m_scene->AddGameObject(throw_S);

		DistanceConstraint* cons_3 = new DistanceConstraint(throw_S->Physics(), lastObject->Physics(),
			throw_S->Physics()->GetPosition() + Vector3(0.7f, 0.0f, 0.0f),
			lastObject->Physics()->GetPosition() + Vector3(0.7f, 0.0f, 0.0f));
		cons->softness = softness_offset;
		PhysicsEngine::Instance()->AddConstraint(cons_3);

		DistanceConstraint* cons_4 = new DistanceConstraint(throw_S->Physics(), lastObject->Physics(),
			throw_S->Physics()->GetPosition() + Vector3(-0.7f, 0.0f, 0.0f),
			lastObject->Physics()->GetPosition() + Vector3(-0.7f, 0.0f, 0.0f));
		cons->softness = softness_offset;
		PhysicsEngine::Instance()->AddConstraint(cons_4);
	}
}
