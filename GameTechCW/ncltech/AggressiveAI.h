#pragma once

#include <ncltech\SimpleMeshObject.h>
#include <nclgl\Camera.h>

class AggressiveBaseState; //foreward declaration of base state so compiler is awware of base states existance

class AggressiveAI : public SimpleMeshObject { //ArbitraryAI object inherits from simplemeshobject and holds information of AI's hitbox and physics
public:
	AggressiveAI(const std::string& name, Scene* m_scene); //on instantiation must pass its constructor name string to be given to simplemesh object (as its constructor requires it)
	AggressiveAI();
	~AggressiveAI();

	virtual void OnUpdateObject(float dt) override; //actions to be performed each update of the object, ie each frame

	virtual void SetState(int newStateEnum); //sets the state of the AI, used by trigger check methods 

	void UpdateAI();
	Vector3 DirectionCalculation(Vector3 to, Vector3 from);
	void RotationCalculation(Vector3 defendnode);
	void ForwardBackwardCalculation(float disttonode);

	Scene* scene;

	bool left, right, reverse, forward;
	Vector3 Node, DirectionVector;
private:
	AggressiveBaseState* currentState;
	int iterator;
};
