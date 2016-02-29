#include "PowerUps.h"

//SimpleMeshObject*  Banana = NULL;
string PowerUps::AndroidPowerUp = "0";
Vector4 PowerUps::tempcolour;
GameTimer PowerUps::InvisTimer;
SimpleMeshObject* PowerUps::BananaPU = NULL;
SimpleMeshObject* PowerUps::PowerUpBox = NULL;
bool PowerUps::PlayerPickup = false;

std::function<bool(PhysicsObject*)> bananaSpin = [&](PhysicsObject* otherObject) {
	if (otherObject->name == "car"){
		otherObject->SetAngularVelocity(Vector3(0.f, 8.f, 0.f));
		otherObject->SetLinearVelocity(otherObject->GetLinearVelocity()*0.85);
		PowerUps::BananaPU->Physics()->SetPosition(Vector3(1000.f, 0.f, 0.f));
		//PowerUps::BananaPU->RemoveFromScene();
		PhysicsEngine::Instance()->RemovePhysicsObject(PowerUps::BananaPU->Physics());
		//PowerUps::BananaPU->deletemesh();

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
			PowerUps::SetPlayerPickup(true);
			PowerUps::PowerUpBox->Physics()->SetPosition(Vector3(200.f, 0.f, 0.f));
			PhysicsEngine::Instance()->RemovePhysicsObject(PowerUps::PowerUpBox->Physics());
			return false;
		}
		else{
			PowerUps::PowerUpBox->Physics()->SetPosition(Vector3(1000.f, 0.f, 0.f));
			PhysicsEngine::Instance()->RemovePhysicsObject(PowerUps::PowerUpBox->Physics());
			return false;
		}
	}
	else{
		return true;
	}
};

std::function<bool(PhysicsObject*)> AndroidPowerUpCallback = [&](PhysicsObject* otherObject) {
	if (otherObject->name == "car"){
		if (AssetsManager::Player_1->GetPowerUpState() == "No PowerUp"){
			AssetsManager::Player_1->SetPowerUpState(PowerUps::AndroidPowerUp);
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
	InvisTimer.GetTimedMS();
	player->SetColour(Vector4(player->GetColour().x, player->GetColour().y, player->GetColour().z, 0.0f));
	player->SetPowerUpState("No PowerUp");
	player->invisible = true;
}

void PowerUps::BananaPowerUp(Player* player, Scene* m_Scene){
	BananaPU = new SimpleMeshObject("powerup_banana");
	BananaPU->SetMesh(AssetsManager::Banana(), false);
	BananaPU->SetBoundingRadius(1.0f * 1.f);
	BananaPU->SetLocalTransform(Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));
	BananaPU->Physics()->name = "powerup_banana";
	BananaPU->Physics()->SetInverseMass(0.06f);
	BananaPU->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(0.5f, 0.5f, 0.5f)));
	BananaPU->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f);
	BananaPU->Physics()->SetPosition(AssetsManager::Player_1->Physics()->GetPosition() + Vector3(0.0f, 4.0f, 0.0f));
	BananaPU->Physics()->SetLinearVelocity((AssetsManager::Player_1->Physics()->GetOrientation().ToMatrix3() * Vector3(0.0f, 0.0f, 1.0f)) * 10);
	BananaPU->Physics()->SetOnCollisionCallback(bananaSpin);
	m_Scene->AddGameObject(BananaPU);
	
	AssetsManager::Player_1->SetPowerUpState("No PowerUp");
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
	if (player->GetPowerUpState() == "boost"){
		Boost(player);
	}
}

void PowerUps::AddRandomPowerUp(Scene* m_Scene){
	int x = (rand() % 360) - 180;
	int y = 10;
	int z = (rand() % 240) - 120;
	PowerUpBox = new SimpleMeshObject("powerup_powerup");
	PowerUpBox->SetMesh(AssetsManager::Cube(), false);
	PowerUpBox->SetBoundingRadius(1.0f);
	PowerUpBox->SetLocalTransform(Matrix4::Scale(Vector3(1.f, 1.f, 1.f)));
	PowerUpBox->SetTexture(AssetsManager::m_CubeTex,false);
	PowerUpBox->Physics()->name = "powerup_powerup";
	PowerUpBox->Physics()->SetInverseMass(0.06f);
	PowerUpBox->SetColour(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	PowerUpBox->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.f, 1.f, 1.f)));
	PowerUpBox->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f);
	PowerUpBox->Physics()->SetPosition(Vector3(x, y, z));
	PowerUpBox->Physics()->SetOnCollisionCallback(PowerUpCallback);

	m_Scene->AddGameObject(PowerUpBox);
}

void PowerUps::AddAndroidPowerUp(float x, float z, Scene* m_Scene, string powerupselect){
	int y = 10;
	SimpleMeshObject* powerup = new SimpleMeshObject("powerup");
	powerup->SetMesh(AssetsManager::Cube(), false);
	powerup->SetBoundingRadius(1.0f * 1.f);
	powerup->SetLocalTransform(Matrix4::Scale(Vector3(1.f, 1.f, 1.f)));
	powerup->SetColour(Vector4(0.0f, 1.0f, 0.0f, .5f));
	powerup->Physics()->name = "powerup";
	powerup->Physics()->SetInverseMass(0.06f);
	powerup->Physics()->SetPosition(Vector3(x, y, z));
	powerup->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.f, 1.f, 1.f)));
	powerup->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f);
	AndroidPowerUp = powerupselect;
	powerup->Physics()->SetOnCollisionCallback(PowerUpCallback);
	m_Scene->AddGameObject(powerup);
}

string PowerUps::PowerUpSelector(){
	int x = rand() % 3;
	switch (x){
	case 0:
		return "invisibility";
	case 1:
		return "banana";
	case 2:
		return "boost";
	}
}

void PowerUps::Boost(Player* player){
	player->Physics()->SetLinearVelocity(player->Physics()->GetLinearVelocity() * 4);
	player->SetPowerUpState("No PowerUp");
}