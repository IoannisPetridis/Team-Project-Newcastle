#pragma once
#include <ncltech\PhysicsObject.h>
#include <nclgl\Vector3.h>
class Constraint
{
public:
	Constraint();
	Constraint(PhysicsObject* objA, PhysicsObject* objB, Vector3 j1, Vector3 j2, Vector3 j3, Vector3 j4, float b );
	void ApplyImpulse(); //Apply delta update

	virtual void PreSolverStep(float dt){}
	virtual void DebugDraw() const{}
	
public:
	PhysicsObject *objA, *objB;
	Vector3 j1, j2, j3, j4; // Jacobian diagonals
	float b; //Bias term

	float delta; // Constaint Delta

	float impulseSum;
	//Accumulated delta over the whole solver iteration

	float impulseSumMin, impulseSumMax; // max  and  min value to clamp
	//impulse sum to (defult -MAX_INFINITY, +MAX_INFINITY)
	
	float softness;
	//Value that scale the constaint applies (relate to mass of both objects combined)
};

