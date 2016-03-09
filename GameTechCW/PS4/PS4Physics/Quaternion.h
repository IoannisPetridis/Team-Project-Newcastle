/******************************************************************************
Class:Quaternion
Implements:
Author:Rich Davison
Description:VERY simple Quaternion class. Students are encouraged to modify 
this as necessary...if they dare.

Quaternions aren't really discussed much in the graphics module, but the 
MD5Mesh class uses them internally, as MD5 files store their rotations
as quaternions.

I hate Quaternions.

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <iostream>
#include "common.h"
#include "Matrix4.h"
#include "Matrix3.h"

class GLMMatrix4;

class Quaternion	{
public:
	Quaternion(void);
	Quaternion(float x, float y, float z, float w);

	~Quaternion(void);

	float x;
	float y;
	float z;
	float w;

	void	Normalise();

	GLMMatrix4 ToMatrix4() const;
	GLMMatrix3 ToMatrix3() const;

	Quaternion	Conjugate() const;
	void		GenerateW();	//builds 4th component when loading in shortened, 3 component quaternions

	static Quaternion EulerAnglesToQuaternion(float pitch, float yaw, float roll);
	static Quaternion AxisAngleToQuaterion(const GLMVector3& vector, float degrees);

	static void RotatePointByQuaternion(const Quaternion &q, GLMVector3 &point);

	static Quaternion FromMatrix(const GLMMatrix4 &m);
	static Quaternion FromMatrix(const GLMMatrix3 &m);

	static float Dot(const Quaternion &a, const Quaternion &b);

	Quaternion operator *(const Quaternion &a) const;
	Quaternion operator *(const GLMVector3 &a) const;

	Quaternion operator+(const Quaternion &a) const {
		return Quaternion(x + a.x, y + a.y, z + a.z, w + a.w);
	}

	Quaternion Interpolate(const Quaternion& pStart, const Quaternion& pEnd, float pFactor);

	inline friend std::ostream& operator<<(std::ostream& o, const Quaternion& q){
		o << "Quat(" << q.x << "," << q.y << "," << q.z <<  "," << q.w << ")" << std::endl;
		return o;
	}
};