/******************************************************************************
Class:GLMMatrix4
Implements:
Author:Rich Davison
Description:VERY simple 4 by 4 matrix class. Students are encouraged to modify 
this as necessary! Overloading the [] operator to allow acces to the values
array in a neater way might be a good start, as the floats that make the matrix 
up are currently public.

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////
#pragma once

#include <iostream>
#include "common.h"
#include "Vector3.h"
#include "Vector4.h"

class GLMVector3;
class GLMMatrix3;


class GLMMatrix4	{
public:
	GLMMatrix4(void);
	GLMMatrix4(float elements[16]);
	GLMMatrix4(const GLMMatrix3& mat33);
	~GLMMatrix4(void);

	float	values[16];

	//Set all matrix values to zero
	void	ToZero();
	//Sets matrix to identity matrix (1.0 down the diagonal)
	void	ToIdentity();

	//Gets the OpenGL position vector (floats 12,13, and 14)
	GLMVector3 GetPositionVector() const;
	//Sets the OpenGL position vector (floats 12,13, and 14)
	void	SetPositionVector(const GLMVector3 in);

	//Gets the scale vector (floats 1,5, and 10)
	GLMVector3 GetScalingVector() const;
	//Sets the scale vector (floats 1,5, and 10)
	void	SetScalingVector(const GLMVector3 &in);

	//Creates a rotation matrix that rotates by 'degrees' around the 'axis'
	//Analogous to glRotatef
	static GLMMatrix4 Rotation(float degrees, const GLMVector3 &axis);

	//Creates a scaling matrix (puts the 'scale' vector down the diagonal)
	//Analogous to glScalef
	static GLMMatrix4 Scale(const GLMVector3 &scale);

	//Creates a translation matrix (identity, with 'translation' vector at
	//floats 12, 13, and 14. Analogous to glTranslatef
	static GLMMatrix4 Translation(const GLMVector3 &translation);

	//Creates a perspective matrix, with 'znear' and 'zfar' as the near and 
	//far planes, using 'aspect' and 'fov' as the aspect ratio and vertical
	//field of vision, respectively.
	static GLMMatrix4 Perspective(float znear, float zfar, float aspect, float fov);

	//Creates an orthographic matrix with 'znear' and 'zfar' as the near and 
	//far planes, and so on. Descriptive variable names are a good thing!
	static GLMMatrix4 Orthographic(float znear, float zfar,float right, float left, float top, float bottom);

	//Builds a view matrix suitable for sending straight to the vertex shader.
	//Puts the camera at 'from', with 'lookingAt' centered on the screen, with
	//'up' as the...up axis (pointing towards the top of the screen)
	static GLMMatrix4 BuildViewMatrix(const GLMVector3 &from, const GLMVector3 &lookingAt, const GLMVector3 up = GLMVector3(0,1,0));

	GLMMatrix4 GetRotation() const;
	GLMMatrix4 GetTransposedRotation() const;

	//Multiplies 'this' matrix by matrix 'a'. Performs the multiplication in 'OpenGL' order (ie, backwards)
	inline GLMMatrix4 operator*(const GLMMatrix4 &a) const{	
		GLMMatrix4 out;
		//Students! You should be able to think up a really easy way of speeding this up...
		for(unsigned int r = 0; r < 4; ++r) {
			for(unsigned int c = 0; c < 4; ++c) {
				out.values[c + (r*4)] = 0.0f;
				for(unsigned int i = 0; i < 4; ++i) {
					out.values[c + (r*4)] += this->values[c+(i*4)] * a.values[(r*4)+i];
				}
			}
		}
		return out;
	}

	inline GLMVector3 operator*(const GLMVector3 &v) const {
		GLMVector3 vec;

		float temp;

		vec.x = v.x*values[0] + v.y*values[4] + v.z*values[8]  + values[12];
		vec.y = v.x*values[1] + v.y*values[5] + v.z*values[9]  + values[13];
		vec.z = v.x*values[2] + v.y*values[6] + v.z*values[10] + values[14];

		temp =  v.x*values[3] + v.y*values[7] + v.z*values[11] + values[15];

		vec.x = vec.x/temp;
		vec.y = vec.y/temp;
		vec.z = vec.z/temp;

		return vec;
	};

		inline GLMVector4 operator*(const GLMVector4 &v) const {
		return GLMVector4(
			v.x*values[0] + v.y*values[4] + v.z*values[8]  +v.w * values[12],
			v.x*values[1] + v.y*values[5] + v.z*values[9]  +v.w * values[13],
			v.x*values[2] + v.y*values[6] + v.z*values[10] +v.w * values[14],
			v.x*values[3] + v.y*values[7] + v.z*values[11] +v.w * values[15]
		);
	};

	//Handy string output for the matrix. Can get a bit messy, but better than nothing!
	inline friend std::ostream& operator<<(std::ostream& o, const GLMMatrix4& m){
		o << "Mat4(";
		o << "\t"	<< m.values[0] << "," << m.values[1] << "," << m.values[2] << "," << m.values [3] << std::endl;
		o << "\t\t" << m.values[4] << "," << m.values[5] << "," << m.values[6] << "," << m.values [7] << std::endl;
		o << "\t\t" << m.values[8] << "," << m.values[9] << "," << m.values[10] << "," << m.values [11] << std::endl;
		o << "\t\t" << m.values[12] << "," << m.values[13] << "," << m.values[14] << "," << m.values [15] << " )" <<std::endl;
		return o;
	}
};

