#include "Matrix4.h"
#include "Matrix3.h"

	GLMMatrix4::GLMMatrix4(void)	{
		ToIdentity();
	}

	GLMMatrix4::GLMMatrix4(float elements[16])	{
		memcpy(this->values, elements, 16 * sizeof(float));
	}

	GLMMatrix4::GLMMatrix4(const GLMMatrix3& mat33)
	{
		const unsigned int size = 3 * sizeof(float);
		memcpy(&values[0], &mat33.mat_array[0], size);
		memcpy(&values[4], &mat33.mat_array[3], size);
		memcpy(&values[8], &mat33.mat_array[6], size);
	}

	GLMMatrix4::~GLMMatrix4(void)	{
		ToIdentity();
	}

	void GLMMatrix4::ToIdentity() {
		ToZero();
		values[0] = 1.0f;
		values[5] = 1.0f;
		values[10] = 1.0f;
		values[15] = 1.0f;
	}

	void GLMMatrix4::ToZero()	{
		for (int i = 0; i < 16; i++)	{
			values[i] = 0.0f;
		}
	}

	GLMVector3 GLMMatrix4::GetPositionVector() const{
		return GLMVector3(values[12], values[13], values[14]);
	}

	void	GLMMatrix4::SetPositionVector(const GLMVector3 in) {
		values[12] = in.x;
		values[13] = in.y;
		values[14] = in.z;
	}

	GLMVector3 GLMMatrix4::GetScalingVector() const{
		return GLMVector3(values[0], values[5], values[10]);
	}

	void	GLMMatrix4::SetScalingVector(const GLMVector3 &in) {
		values[0] = in.x;
		values[5] = in.y;
		values[10] = in.z;
	}

	GLMMatrix4 GLMMatrix4::Perspective(float znear, float zfar, float aspect, float fov) {
		GLMMatrix4 m;

		const float h = 1.0f / tan(fov*PI_OVER_360);
		float neg_depth = znear - zfar;

		m.values[0] = h / aspect;
		m.values[5] = h;
		m.values[10] = (zfar + znear) / neg_depth;
		m.values[11] = -1.0f;
		m.values[14] = 2.0f*(znear*zfar) / neg_depth;
		m.values[15] = 0.0f;

		return m;
	}

	//http://www.opengl.org/sdk/docs/man/xhtml/glOrtho.xml
	GLMMatrix4 GLMMatrix4::Orthographic(float znear, float zfar, float right, float left, float top, float bottom)	{
		GLMMatrix4 m;

		m.values[0] = 2.0f / (right - left);
		m.values[5] = 2.0f / (top - bottom);
		m.values[10] = -2.0f / (zfar - znear);

		m.values[12] = -(right + left) / (right - left);
		m.values[13] = -(top + bottom) / (top - bottom);
		m.values[14] = -(zfar + znear) / (zfar - znear);
		m.values[15] = 1.0f;

		return m;
	}

	GLMMatrix4 GLMMatrix4::BuildViewMatrix(const GLMVector3 &from, const GLMVector3 &lookingAt, const GLMVector3 up /*= GLMVector3(1,0,0)*/)	{
		GLMMatrix4 r;
		r.SetPositionVector(GLMVector3(-from.x, -from.y, -from.z));

		GLMMatrix4 m;

		GLMVector3 f = (lookingAt - from);
		f.Normalise();

		GLMVector3 s = GLMVector3::Cross(f, up);
		GLMVector3 u = GLMVector3::Cross(s, f);

		s.Normalise();
		u.Normalise();

		m.values[0] = s.x;
		m.values[4] = s.y;
		m.values[8] = s.z;

		m.values[1] = u.x;
		m.values[5] = u.y;
		m.values[9] = u.z;

		m.values[2] = -f.x;
		m.values[6] = -f.y;
		m.values[10] = -f.z;

		return m*r;
	}

	GLMMatrix4 GLMMatrix4::Rotation(float degrees, const GLMVector3 &inaxis)	 {
		GLMMatrix4 m;

		GLMVector3 axis = inaxis;

		axis.Normalise();

		float c = cos((float)DegToRad(degrees));
		float s = sin((float)DegToRad(degrees));

		m.values[0] = (axis.x * axis.x) * (1.0f - c) + c;
		m.values[1] = (axis.y * axis.x) * (1.0f - c) + (axis.z * s);
		m.values[2] = (axis.z * axis.x) * (1.0f - c) - (axis.y * s);

		m.values[4] = (axis.x * axis.y) * (1.0f - c) - (axis.z * s);
		m.values[5] = (axis.y * axis.y) * (1.0f - c) + c;
		m.values[6] = (axis.z * axis.y) * (1.0f - c) + (axis.x * s);

		m.values[8] = (axis.x * axis.z) * (1.0f - c) + (axis.y * s);
		m.values[9] = (axis.y * axis.z) * (1.0f - c) - (axis.x * s);
		m.values[10] = (axis.z * axis.z) * (1.0f - c) + c;

		return m;
	}

	GLMMatrix4 GLMMatrix4::Scale(const GLMVector3 &scale)	{
		GLMMatrix4 m;

		m.values[0] = scale.x;
		m.values[5] = scale.y;
		m.values[10] = scale.z;

		return m;
	}

	GLMMatrix4 GLMMatrix4::Translation(const GLMVector3 &translation)	{
		GLMMatrix4 m;

		m.values[12] = translation.x;
		m.values[13] = translation.y;
		m.values[14] = translation.z;

		return m;
	}

	GLMMatrix4 GLMMatrix4::GetRotation() const
	{
		GLMMatrix4 temp;
		temp.values[0] = values[0];
		temp.values[5] = values[5];
		temp.values[10] = values[10];
		temp.values[1] = values[1];
		temp.values[4] = values[4];
		temp.values[2] = values[2];
		temp.values[8] = values[8];
		temp.values[6] = values[6];
		temp.values[9] = values[9];
		return temp;
	}

	GLMMatrix4 GLMMatrix4::GetTransposedRotation() const {
		GLMMatrix4 temp;
		temp.values[0] = values[0];
		temp.values[5] = values[5];
		temp.values[10] = values[10];
		temp.values[1] = values[4];
		temp.values[4] = values[1];
		temp.values[2] = values[8];
		temp.values[8] = values[2];
		temp.values[6] = values[9];
		temp.values[9] = values[6];
		return temp;
	}

