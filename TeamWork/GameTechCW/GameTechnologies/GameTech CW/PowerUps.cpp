#include "PowerUps.h"


SimpleMeshObject*  Banana = NULL;


std::function<bool(PhysicsObject*)> bananaSpin = [&](PhysicsObject* otherObject) {


	if (otherObject->name == "car"){
		otherObject->SetAngularVelocity(Vector3(0.f, 8.f, 0.f));
		otherObject->SetLinearVelocity(otherObject->GetLinearVelocity()*0.85);
		return false;
	}
	else{

		return true;
	}
};

std::function<bool(PhysicsObject*)> PowerUpCallback = [&](PhysicsObject* otherObject) {


	if (otherObject->name == "car"){
		if (AssetsManager::Player_1->GetPowerUpState() == "No PowerUp"){
			AssetsManager::Player_1->SetPowerUpState(PowerUps::PowerUpSelector());
			return false;
		}

	else{
		return false;
	}
	}
	else{

		return true;
	}
};


void PowerUps::LoadPowerUps(Player* player){



}

void PowerUps::Invisibility(Player* player){

	player->SetColour(Vector4(0.f, 0.f,0.f, 0.0f));
}

void PowerUps::BananaPowerUp(Player* player, Scene* m_Scene){
	Banana = new SimpleMeshObject("banana");
	Banana->SetMesh(AssetsManager::Banana(), false);
	/*Banana->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	Banana->SetColour(Vector4(0.2f, 10.0f, 10.5f, 1.0f));*/
	Banana->SetBoundingRadius(1.0f * 1.f);
	Banana->SetLocalTransform(Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));

	Banana->Physics()->name = "banana";
	Banana->Physics()->SetInverseMass(0.06f);
	Banana->Physics()->SetPosition(player->Physics()->GetPosition() + Vector3(0.0f, 2.0f, 0.0f));
	Banana->Physics()->SetForce(player->Physics()->GetOrientation().ToMatrix3() * Vector3(0.0f, 0.0f, 1.0f));
	Banana->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(0.5f, 0.5f, 0.5f)));
	Banana->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f);
	Banana->Physics()->SetOnCollisionCallback(bananaSpin);
	m_Scene->AddGameObject(Banana);
	
}



void PowerUps::SetPowerUp(string powerupname, Player* player){
	player->SetPowerUpState(powerupname);
}

void PowerUps::UsePowerUp(Player* player, Scene* m_Scene){
	if (player->GetPowerUpState() == "invisibility"){
			Invisibility(player);
	}
	if (player->GetPowerUpState() == "banana"){
		BananaPowerUp(player, m_Scene);
	}
}

void PowerUps::AddPowerUp(Scene* m_Scene){
	int x = rand() % 100;
	int y = 10;
	int z = rand() % 100;
	SimpleMeshObject* powerup = new SimpleMeshObject("powerup");
	powerup->SetMesh(AssetsManager::Cube(), false);
	powerup->SetBoundingRadius(1.0f * 1.f);
	powerup->SetLocalTransform(Matrix4::Scale(Vector3(1.f, 1.f, 1.f)));
	powerup->Physics()->name = "powerup";
	powerup->Physics()->SetInverseMass(0.06f);
	powerup->Physics()->SetPosition(Vector3(x, y, z));
	powerup->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.f, 1.f, 1.f)));
	powerup->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f);
	powerup->Physics()->SetOnCollisionCallback(PowerUpCallback);
	m_Scene->AddGameObject(powerup);

}

string PowerUps::PowerUpSelector(){

	int x = rand() % 2;
	
	switch (x){

	case 0:
		return "invisibility";
	case 1:
		return "banana";
	}
}