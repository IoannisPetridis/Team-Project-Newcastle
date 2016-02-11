#pragma once

#include "Scene.h"
#include <ncltech\SimpleMeshObject.h>
#include <nclgl\Camera.h>

class Player : public SimpleMeshObject {
public:
	Player(const std::string& name, Camera* cameraInstance);
	Player();
	~Player();

	virtual void OnUpdateObject(float dt) override;

private:
	Camera* camera;
};