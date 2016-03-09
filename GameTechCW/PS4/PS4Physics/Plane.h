/******************************************************************************
Class:Plane
Implements:
Author:Rich Davison	<richard.davison4@newcastle.ac.uk>
Description:VERY simple Plane class. Students are encouraged to modify 
this as necessary!

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "vector3.h"

class Plane	{
public:
	Plane(void){};
	Plane(const GLMVector3 &normal, float distance, bool normalise = false);
	~Plane(void){};

	//Sets the planes normal, which should be UNIT LENGTH!!!
	void	SetNormal(const GLMVector3 &normal) {this->normal = normal;}
	//Gets the planes normal.
	GLMVector3 GetNormal() const				 {return normal;}
	//Sets the planes distance from the origin
	void	SetDistance(float dist)	{distance = dist;}
	//Gets the planes distance from the origin
	float	GetDistance() const		{return distance;}
	//Performs a simple sphere / plane test
	bool SphereInPlane(const GLMVector3 &position, float radius) const; 
	//Performs a simple sphere / point test
	bool PointInPlane(const GLMVector3 &position) const;

protected:
	//Unit-length plane normal
	GLMVector3 normal;
	//Distance from origin
	float	distance;
};