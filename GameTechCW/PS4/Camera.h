/******************************************************************************
Class:Camera
Implements:
Author:Rich Davison	<richard.davison4@newcastle.ac.uk>
Description:FPS-Style camera. Uses the mouse and keyboard from the Window
class to get movement values!

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////
#pragma once

#include "./vectormath/scalar_cpp/vectormath_aos.h"
#include "PS4RendererBase.h"
#include "PS4Input.h"

using namespace sce::Vectormath::Scalar::Aos;
class Camera 	{
public:
	Camera(void){
		yaw		= 0.0f;
		pitch	= 0.0f;
	};

	Camera(float pitch, float yaw, Vector4 position){
		this->pitch		= pitch;
		this->yaw		= yaw;
		this->position	= position;
	}

	~Camera(void){};

	void UpdateCamera(float msec, PS4Input* input);

	//Builds a view matrix for the current camera variables, suitable for sending straight
	//to a vertex shader (i.e it's already an 'inverse camera matrix').
	Matrix4 BuildViewMatrix();

	//Gets position in world space
	Vector4 GetPosition() const { return position;}
	//Sets position in world space
	void	SetPosition(Vector4 val) { position = val;}

	//Gets yaw, in degrees
	float	GetYaw()   const { return yaw;}
	//Sets yaw, in degrees
	void	SetYaw(float y) {yaw = y;}

	//Gets pitch, in degrees
	float	GetPitch() const { return pitch;}
	//Sets pitch, in degrees
	void	SetPitch(float p) {pitch = p;}

protected:
	float	yaw;
	float	pitch;
	float speed =1.0f;
	Vector4 position;
};