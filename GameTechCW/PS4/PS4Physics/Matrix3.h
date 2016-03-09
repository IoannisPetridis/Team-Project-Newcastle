#ifndef MAT33_H
#define MAT33_H

#include "Vector3.h"

class GLMMatrix4;

	class GLMMatrix3
	{
	public:

		static const GLMMatrix3 Identity;
		static const GLMMatrix3 ZeroMatrix;

		//ctor
		GLMMatrix3();

		GLMMatrix3(float elements[9]);

		GLMMatrix3(const  GLMVector3& c1, const  GLMVector3& c2, const  GLMVector3& c3);

		GLMMatrix3(float a1, float a2, float a3,
			float b1, float b2, float b3,
			float c1, float c2, float c3);

		GLMMatrix3(const GLMMatrix4& mat44);

		~GLMMatrix3(void);




		//Default States
		void	ToZero();
		void	ToIdentity();



		//Default Accessors
		inline float   operator[](int index) const        { return mat_array[index]; }
		inline float&  operator[](int index)              { return mat_array[index]; }
		inline float   operator()(int row, int col) const { return mat_array[row + col * 3]; }
		inline float&  operator()(int row, int col)       { return mat_array[row + col * 3]; }

		inline const  GLMVector3&	GetCol(int idx) const				{ return *(( GLMVector3*)&mat_array[idx * 3]); }
		inline void				SetCol(int idx, const  GLMVector3& row)	{ memcpy(&mat_array[idx * 3], &row.x, 3 * sizeof(float)); }

		inline  GLMVector3			GetRow(int idx)	const				{ return  GLMVector3(mat_array[idx], mat_array[3 + idx], mat_array[6 + idx]); }
		inline void				SetRow(int idx, const  GLMVector3& col)	{ mat_array[idx] = col.x; mat_array[3 + idx] = col.y; mat_array[6 + idx] = col.z; }



		//Common Matrix Properties
		inline  GLMVector3			GetScalingVector() const			{ return  GLMVector3(_11, _22, _33); }
		inline void				SetScalingVector(const  GLMVector3& in)	{ _11 = in.x, _22 = in.y, _33 = in.z; }



		//Transformation Matrix
		static GLMMatrix3 Rotation(float degrees, const  GLMVector3 &axis);
		static GLMMatrix3 Scale(const  GLMVector3 &scale);



		// Standard Matrix Functionality
		static GLMMatrix3 Inverse(const GLMMatrix3& rhs);
		static GLMMatrix3 Transpose(const GLMMatrix3& rhs);
		static GLMMatrix3 Adjugate(const GLMMatrix3& m);

		static GLMMatrix3 OuterProduct(const  GLMVector3& a, const  GLMVector3& b);



		// Additional Functionality
		float Trace() const;
		float Determinant() const;


		void DebugDrawMatrix(const  GLMVector3& position);


		//Other representation of data.
		union
		{
			float	mat_array[9];
			struct {
				float _11, _12, _13;
				float _21, _22, _23;
				float _31, _32, _33;
			};
		};
	};

	GLMMatrix3& operator+=(GLMMatrix3& a, const GLMMatrix3& rhs);
	GLMMatrix3& operator-=(GLMMatrix3& a, const GLMMatrix3& rhs);

	GLMMatrix3 operator+(const GLMMatrix3& a, const GLMMatrix3& rhs);
	GLMMatrix3 operator-(const GLMMatrix3& a, const GLMMatrix3& rhs);
	GLMMatrix3 operator*(const GLMMatrix3& a, const GLMMatrix3& rhs);


	GLMMatrix3& operator+=(GLMMatrix3& a, const float b);
	GLMMatrix3& operator-=(GLMMatrix3& a, const float b);
	GLMMatrix3& operator*=(GLMMatrix3& a, const float b);
	GLMMatrix3& operator/=(GLMMatrix3& a, const float b);

	GLMMatrix3 operator+(const GLMMatrix3& a, const float b);
	GLMMatrix3 operator-(const GLMMatrix3& a, const float b);
	GLMMatrix3 operator*(const GLMMatrix3& a, const float b);
	GLMMatrix3 operator/(const GLMMatrix3& a, const float b);

	GLMVector3 operator*(const GLMMatrix3& a, const GLMVector3& b);

#endif //MAT33_H

