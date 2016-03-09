#include "Plane.h"

Plane::Plane(const GLMVector3 &normal, float distance, bool normalise) {
	if(normalise) {
		float length = GLMVector3::Dot(normal,normal);

		this->normal   = normal		/ length;
		this->distance = distance	/ length;
	}
	else{
		this->normal = normal;
		this->distance = distance;
	}
}

bool Plane::SphereInPlane(const GLMVector3 &position, float radius) const {
	if(GLMVector3::Dot(position,normal)+distance <= -radius) {
		return false;
	}

	return true;	
}

bool Plane::PointInPlane(const GLMVector3 &position) const {
	float test = GLMVector3::Dot(position,normal);
	float test2 = test + distance;

	if(GLMVector3::Dot(position,normal)+distance < -0.0001f) {
		return false;
	}

	return true;
}