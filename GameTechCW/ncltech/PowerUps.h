#pragma once

#include "GameObjectMag.h"

class PowerUps{
	friend class ObjectManager;
	friend class Scene;

public:

	static string PowerUpSelector();
	static void AddRandomPowerUp(Scene* m_Scene,SimpleMeshObject* PowerUpBox);
	static void AddAndroidPowerUp(float x, float y, Scene* m_Scene, string powerup);
	static void RandomPowerUpPosition(SimpleMeshObject* PowerUpBox);

	static void Invisibility(Player* player);
	static void BananaPowerUp(Player* player, Scene* m_Scene);
	static void NoBreak(Player* player);
	static void SetPowerUp(string powerupname, Player* player);
	static void Boost(Player* player);

	static void PlayerPowerUpState(Player* player);
	static void UsePowerUp(Player* player, Scene* m_Scene);
	static bool GetPlayerPickup(){ return PlayerPickup; }
	static void SetPlayerPickup(bool a){ PlayerPickup = a; }

	static string AndroidPowerUp;

	static Vector4 tempcolour;
	static GameTimer InvisTimer;

	static void deletepowerup(PhysicsObject* obj){ delete obj; }

	static bool PlayerPickup;

	
};