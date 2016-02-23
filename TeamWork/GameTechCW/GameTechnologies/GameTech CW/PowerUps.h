#pragma once

#include "../../ncltech/GameObjectMag.h"

class PowerUps{
	friend class ObjectManager;
	friend class Scene;

public:

	static string PowerUpSelector();
	static void AddPowerUp(Scene* m_Scene);

	static void Invisibility(Player* player);
	static void BananaPowerUp(Player* player,Scene* m_Scene);
	static void NoBreak(Player* player);
	static void SetPowerUp(string powerupname, Player* player);

	static void PlayerPowerUpState(Player* player);
	static void UsePowerUp(Player* player, Scene* m_Scene);
	static void LoadPowerUps(Player* player);

	//static SimpleMeshObject*  Banana;
	





};