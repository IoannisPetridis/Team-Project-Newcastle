#include "Camera.h"
#include <iostream>
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))
/*
Polls the camera for keyboard / mouse movement.
Should be done once per frame! Pass it the msec since
last frame (default value is for simplicities sake...)
*/
void Camera::UpdateCamera(float msec, PS4Input* input)	{
	//right control
	if ((input->GetAxis(1).y >= -1 && input->GetAxis(1).y <= 1) && !((input->GetAxis(1).y >= -0.1f) && (input->GetAxis(1).y <= 0.1f)))
	{
		pitch += 0.01f * -(input->GetAxis(1).y);
	}
	if ((input->GetAxis(1).x >= -1 && input->GetAxis(1).x <= 1) && !((input->GetAxis(1).x >= -0.1f) && (input->GetAxis(1).x <= 0.1f)))
	{
		yaw += 0.01f *- (input->GetAxis(1).x);
	}
	
		//Bounds check the pitch, to be between straight up and straight down ;)
		pitch = min(pitch, 90.0f);
		pitch = max(pitch, -90.0f);


		/*	if (yaw <0) {
			yaw += 360.0f;
		}
		if (yaw > 360.0f) {
			yaw -= 360.0f;
		}*/

		//std::cout << yaw << std::endl;

		/*if ((input->GetAxis(1).y >= -1 && input->GetAxis(1).y <= 1) && !((input->GetAxis(1).y >= -0.1f) && (input->GetAxis(1).y <= 0.1f)))
		{
			pitch += 0.01f * input->GetAxis(1).y;
		}
		if ((input->GetAxis(1).x >= -1 && input->GetAxis(1).x <= 1) && !((input->GetAxis(1).x >= -0.1f) && (input->GetAxis(1).x <= 0.1f)))
		{
			yaw += 0.01f *input->GetAxis(1).x;
		}*/

		if ((input->GetAxis(0).y >= -1 && input->GetAxis(0).y <= 1) && !((input->GetAxis(0).y >= -0.1f) && (input->GetAxis(0).y <= 0.1f)))
		{
			position += Matrix4::rotationY(yaw) * Vector3(0, 0, 1)  * input->GetAxis(0).y * speed;
			position += Matrix4::rotationY(yaw) * Vector3(1, 0, 0)  * input->GetAxis(0).x * speed;
		}
		if ((input->GetAxis(0).x >= -1 && input->GetAxis(0).x <= 1) && !((input->GetAxis(0).x >= -0.1f) && (input->GetAxis(0).x <= 0.1f)))
		{
			position += Matrix4::rotationY(yaw) * Vector3(0, 0, 1)  * input->GetAxis(0).y * speed;
			position += Matrix4::rotationY(yaw) * Vector3(1, 0, 0)  * input->GetAxis(0).x * speed;

		}
		

		/*if (input->GetAxis(0).y == -1) {
			position += Matrix4::rotationY(yaw) * Vector3(0, 0, -1) * speed;
		}
		if (input->GetAxis(0).y == 1) {
			position -= Matrix4::rotationY(yaw) * Vector3(0, 0, -1)  * speed;
		}

		if (input->GetAxis(0).x == -1) {
			position += Matrix4::rotationY(yaw) * Vector3(-1, 0, 0) * speed;
		}
		if (input->GetAxis(0).x == 1) {
			position -= Matrix4::rotationY(yaw) * Vector3(-1, 0, 0) * speed;
		}*/


		if (input->GetButton(6)) {
			position.setY(position.getY() + (msec* speed));
		}
		if (input->GetButton(7)) {
			position.setY(position.getY() - (msec* speed));
		}
		if (input->GetButton(5)) {
			speed = 1.0f;
		}
		if (!input->GetButton(5)) {
			speed = 0.2f;
		}

	}
	/*
	Generates a view matrix for the camera's viewpoint. This matrix can be sent
	straight to the shader...it's already an 'inverse camera' matrix.
	*/
	Matrix4 Camera::BuildViewMatrix()	{
		//Why do a complicated matrix inversion, when we can just generate the matrix
		//using the negative values ;). The matrix multiplication order is important!
		return	Matrix4::rotationX(-pitch) *Matrix4::rotationY(-yaw) *	Matrix4::translation(-Vector3(position.getX(), position.getY(), position.getZ()));
		
	};

