//Player controlled object, OnUpdateObject is be overridden so that player inputs define its motion 
//Would also include more specific aspoects of player controlled objects motion, eg a jump method, or a rotate method for example 

#pragma once

#include <ncltech\SimpleMeshObject.h>

class PlayerControlledObject : public SimpleMeshObject {
public:
	PlayerControlledObject(const std::string& name);
	PlayerControlledObject();
	~PlayerControlledObject();

	virtual void OnUpdateObject(float dt) override;

private:

};