#pragma once

#include "../../ncltech/GameObjectMag.h"

class PowerUps{
	friend class ObjectManager;
	friend class Scene;

public:

	static string PowerUpSelector();
	static void AddRandomPowerUp(Scene* m_Scene);
	static void AddAndroidPowerUp(float x, float y, Scene* m_Scene, string powerup);

	static void Invisibility(Player* player);
	static void BananaPowerUp(Player* player,Scene* m_Scene);
	static void NoBreak(Player* player);
	static void SetPowerUp(string powerupname, Player* player);
	static void Boost(Player* player);

	static void PlayerPowerUpState(Player* player);
	static void UsePowerUp(Player* player, Scene* m_Scene);
	static void LoadPowerUps(Player* player);

	//static SimpleMeshObject*  Banana;
	static string AndroidPowerUp;





};