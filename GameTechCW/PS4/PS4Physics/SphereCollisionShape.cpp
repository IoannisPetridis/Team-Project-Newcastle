#include "SphereCollisionShape.h"
#include "PhysicsObject.h"
#include "GameObject.h"
#include "Matrix3.h"
#include "NCLDebug.h"

SphereCollisionShape::SphereCollisionShape()
{
	m_Radius = 1.0f;
}

SphereCollisionShape::SphereCollisionShape(float radius)
{
	m_Radius = radius;
}

SphereCollisionShape::~SphereCollisionShape()
{

}

GLMMatrix3 SphereCollisionShape::BuildInverseInertia(float invMass) const
{
	//float i = 2.5f * invMass * m_Radius * m_Radius; //SOLID
	float i = 1.5f * invMass * m_Radius * m_Radius; //HOLLOW

	GLMMatrix3 inertia;
	inertia._11 = i;
	inertia._22 = i;
	inertia._33 = i;

	return inertia;
}

void SphereCollisionShape::GetCollisionAxes(const PhysicsObject* currentObject, std::vector<GLMVector3>* out_axes) const
{
	/* There is infinite edges so handle seperately */
}

void SphereCollisionShape::GetEdges(const PhysicsObject* currentObject, std::vector<CollisionEdge>* out_edges) const
{
	/* There is infinite edges on a sphere so handle seperately */
}

void SphereCollisionShape::GetMinMaxVertexOnAxis(const PhysicsObject* currentObject, const GLMVector3& axis, GLMVector3* out_min, GLMVector3* out_max) const
{
	if (out_min)
		*out_min = currentObject->GetPosition() - axis * m_Radius;

	if (out_max)
		*out_max = currentObject->GetPosition() + axis * m_Radius;
}

void SphereCollisionShape::GetIncidentReferencePolygon(const PhysicsObject* currentObject, const GLMVector3& axis, std::list<GLMVector3>* out_face, GLMVector3* out_normal, std::vector<Plane>* out_adjacent_planes) const
{
	if (out_face)
	{
		out_face->push_back(currentObject->GetPosition() + axis * m_Radius);
	}

	if (out_normal)
	{
		*out_normal = axis;
	}
}

void SphereCollisionShape::DebugDraw(const PhysicsObject* currentObject) const
{
	GLMVector3 pos = currentObject->GetPosition();

	//Draw Filled Circle
	//NCLDebug::DrawPoint(pos, m_Radius, Vector4(1.0f, 1.0f, 1.0f, 0.2f));

	//Draw Perimeter Axes
	GLMVector3 lastX = pos + GLMVector3(0.0f, 1.0f, 0.0f) * m_Radius;
	GLMVector3 lastY = pos + GLMVector3(1.0f, 0.0f, 0.0f) * m_Radius;
	GLMVector3 lastZ = pos + GLMVector3(1.0f, 0.0f, 0.0f) * m_Radius;
	for (int itr = 1; itr < 21; ++itr)
	{
		float angle = itr / 20.0f * 6.2831853f;
		float alpha = cosf(angle) * m_Radius;
		float beta = sinf(angle) * m_Radius;

		GLMVector3 newX = pos + GLMVector3(0.0f, alpha, beta);
		GLMVector3 newY = pos + GLMVector3(alpha, 0.0f, beta);
		GLMVector3 newZ = pos + GLMVector3(alpha, beta, 0.0f);

		//NCLDebug::DrawThickLine(lastX, newX, 0.02f, Vector4(1.0f, 0.3f, 1.0f, 1.0f));
		//NCLDebug::DrawThickLine(lastY, newY, 0.02f, Vector4(1.0f, 0.3f, 1.0f, 1.0f));
		//NCLDebug::DrawThickLine(lastZ, newZ, 0.02f, Vector4(1.0f, 0.3f, 1.0f, 1.0f));

		lastX = newX;
		lastY = newY;
		lastZ = newZ;
	}
}