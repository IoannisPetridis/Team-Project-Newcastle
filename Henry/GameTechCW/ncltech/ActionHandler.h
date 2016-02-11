#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "SimpleMeshObject.h"
#include "../nclgl/Window.h"

//class Player;

class ActionHandler : public TSingleton<ActionHandler> {
	friend class TSingleton < ActionHandler>;
public:
	ActionHandler() = default;
	
	void SetDefaultScene(Scene* scene);


	void ControllerHandle(/*Player* Player*/);
	void ControllerHandle();


	void AIPort();

	Scene* GetScene() const { return m_scene; }

	void Update(float dt);

protected:
	Scene* m_scene; 
};

//class Player : public SimpleMeshObject {
//	friend class ActionHandler;
//public:
//	Player(const std::string& name);
//protected:
//	void	OnUpdateObject(float dt) override;
//};