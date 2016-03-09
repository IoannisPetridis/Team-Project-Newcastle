/*
Class:Vector4
Implements:
Author:Rich Davison
Description:VERY simple Vector4 class. Students are encouraged to modify this as necessary!

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*/
#pragma once

#include "Vector3.h"

	class GLMVector4	{
	public:
		GLMVector4(void) {
			x = y = z = w = 1.0f;
		}
		GLMVector4(float x, float y, float z, float w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		GLMVector3 ToVector3() const {
			return GLMVector3(x, y, z);
		}

		~GLMVector4(void){}

		float x;
		float y;
		float z;
		float w;
	};

