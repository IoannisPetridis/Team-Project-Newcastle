#pragma once
#include <../nclgl\Vector4.h>
#include <../nclgl\Vector3.h>
#include <../nclgl\Mesh.h>


class Light
{
public:
	Light()
	{
	}
	Light(Vector3 position, Vector4 colour, float radius, float bright, Vector3 isOn)
	{
		this->position = position;
		this->colour = colour;
		this->radius = radius;
		this->bright = bright;
		this->isOn = isOn;
	}
	~Light(){};
	
	Vector3 GetPosition() const{ return position; }
	void SetPosition(Vector3 val){ position = val; }

	Vector4 GetColour() const{ return colour; }
	void SetColour(Vector4 val){ colour = val; }

	float GetRadius() const{ return radius; }
	
	void SetRadius(float val){ radius = val; }

	float GetBright() const{ return bright; }
	void SetBright(float val){ bright = val; }

	Vector3 GetIsOn() const{ return isOn; }
	void SetIsOn(Vector3 val){ isOn = val; }
	
	Matrix4 GetlightViewProjMat() const{ return lightViewProjMat; }
	void SetlightViewProjMat(Matrix4 val){ lightViewProjMat = val; }


protected:
	Vector3 position;
	float radius;
	Vector4 colour;	
	float bright;
	Vector3 isOn;
	Matrix4 lightViewProjMat;
};

