#include "PlayerControlledObject.h"

PlayerControlledObject::PlayerControlledObject(const std::string& name) : SimpleMeshObject(name) {
	//here want to use assets manager to set up its collision shape mesh texture etc etc, not swure exactlyt how that works currently
}

PlayerControlledObject::~PlayerControlledObject() {
	//destructor
}

void PlayerControlledObject::OnUpdateObject(float dt) {
	//player inputs, will vary depeding on controller use, keyboard, ps4 pc maybe?
	//use #defines to call different functions depending on an at load time declaration of control scheme perhapse. 
}