#pragma once
/*
Class:Vector3
Implements:
Author:Rich Davison
Description:VERY simple Vector3 class. Students are encouraged to modify this as necessary!

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*/
#include <cmath>
#include <iostream>



	class GLMVector3	{
	public:
		GLMVector3(void) {
			ToZero();
		}

		GLMVector3(const float x, const float y, const float z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		~GLMVector3(void){}

		float x;
		float y;
		float z;

		void			Normalise() {
			float length = Length();

			if (length != 0.0f)	{
				length = 1.0f / length;
				x = x * length;
				y = y * length;
				z = z * length;
			}
		}

		void		ToZero() {
			x = y = z = 0.0f;
		}

		float			Length() const {
			return sqrt((x*x) + (y*y) + (z*z));
		}

		float			LengthSquared() const {
			return (x*x + y*y + z*z);
		}

		void			Invert() {
			x = -x;
			y = -y;
			z = -z;
		}

		GLMVector3			Inverse() const{
			return GLMVector3(-x, -y, -z);
		}

		static float	Dot(const GLMVector3 &a, const GLMVector3 &b) {
			return (a.x*b.x) + (a.y*b.y) + (a.z*b.z);
		}

		static GLMVector3	Cross(const GLMVector3 &a, const GLMVector3 &b) {
			return GLMVector3((a.y*b.z) - (a.z*b.y), (a.z*b.x) - (a.x*b.z), (a.x*b.y) - (a.y*b.x));
		}

		inline friend std::ostream& operator<<(std::ostream& o, const GLMVector3& v) {
			o << "GLMVector3(" << v.x << "," << v.y << "," << v.z << ")" << std::endl;
			return o;
		}

		inline GLMVector3  operator+(const GLMVector3  &a) const{
			return GLMVector3(x + a.x, y + a.y, z + a.z);
		}

		inline GLMVector3  operator-(const GLMVector3  &a) const{
			return GLMVector3(x - a.x, y - a.y, z - a.z);
		}

		inline GLMVector3  operator-() const{
			return GLMVector3(-x, -y, -z);
		}

		inline void operator+=(const GLMVector3  &a){
			x += a.x;
			y += a.y;
			z += a.z;
		}

		inline void operator-=(const GLMVector3  &a){
			x -= a.x;
			y -= a.y;
			z -= a.z;
		}

		inline GLMVector3  operator*(const float a) const{
			return GLMVector3(x * a, y * a, z * a);
		}

		inline GLMVector3  operator*(const GLMVector3  &a) const{
			return GLMVector3(x * a.x, y * a.y, z * a.z);
		}

		inline GLMVector3  operator/(const GLMVector3  &a) const{
			return GLMVector3(x / a.x, y / a.y, z / a.z);
		};

		inline GLMVector3  operator/(const float v) const{
			return GLMVector3(x / v, y / v, z / v);
		};

		inline bool	operator==(const GLMVector3 &A)const { return (A.x == x && A.y == y && A.z == z) ? true : false; };
		inline bool	operator!=(const GLMVector3 &A)const { return (A.x == x && A.y == y && A.z == z) ? false : true; };
	};

