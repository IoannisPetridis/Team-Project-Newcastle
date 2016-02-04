#pragma once

#include "CollisionShape.h"
#include "Hull.h"

class PyramidCollisionShape : public CollisionShape
{
public:
	PyramidCollisionShape();
	PyramidCollisionShape(const Vector3& halfdims);
	~PyramidCollisionShape();

	//Collision Shape Functionality
	virtual Matrix3 BuildInverseInertia(float invMass) const override;

	virtual void GetCollisionAxes(const PhysicsObject* currentObject, std::vector<Vector3>* out_axes) const override;
	virtual void GetEdges(const PhysicsObject* currentObject, std::vector<CollisionEdge>* out_edges) const override;

	virtual void GetMinMaxVertexOnAxis(const PhysicsObject* currentObject, const Vector3& axis, Vector3* out_min, Vector3* out_max) const override;
	virtual void GetIncidentReferencePolygon(const PhysicsObject* currentObject, const Vector3& axis, std::list<Vector3>* out_face, Vector3* out_normal, std::vector<Plane>* out_adjacent_planes) const override;

	virtual void DebugDraw(const PhysicsObject* currentObject) const override;


	//Set Cuboid Dimensions
	void SetHalfWidth(float half_width)		{ m_PyramidHalfDimensions.x = fabs(half_width); }
	void SetHalfHeight(float half_height)	{ m_PyramidHalfDimensions.y = fabs(half_height); }
	void SetHalfDepth(float half_depth)		{ m_PyramidHalfDimensions.z = fabs(half_depth); }

	//Get Cuboid Dimensions
	float GetHalfWidth()	const { return m_PyramidHalfDimensions.x; }
	float GetHalfHeight()	const { return m_PyramidHalfDimensions.y; }
	float GetHalfDepth()	const { return m_PyramidHalfDimensions.z; }

protected:
	//Constructs the static cube hull 
	static void ConstructPyramidHull();

protected:
	Vector3				 m_PyramidHalfDimensions;
	static Hull			 m_PyramidHull;
};