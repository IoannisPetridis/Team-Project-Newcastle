#pragma once

#include "CollisionShape.h"
#include "Hull.h"
#include "PhysicsObject.h"
#include "Matrix3.h"
#include <vector>

struct CySide {
	int* list4 = new int[4]();
	Vector3 normal;
};

class CylinderCollisionShape : public CollisionShape
{
public:
	CylinderCollisionShape();
	CylinderCollisionShape(const float length, const float radius, Vector3 halfdim);
	~CylinderCollisionShape();

	//Collision Shape Functionality
	virtual Matrix3 BuildInverseInertia(float invMass) const override ;

	virtual void GetCollisionAxes(const PhysicsObject* currentObject, std::vector<Vector3>* out_axes) const override ;
	virtual void GetEdges(const PhysicsObject* currentObject, std::vector<CollisionEdge>* out_edges) const override ;

	virtual void GetMinMaxVertexOnAxis(const PhysicsObject* currentObject, const Vector3& axis, Vector3* out_min, Vector3* out_max) const override ;
	virtual void GetIncidentReferencePolygon(const PhysicsObject* currentObject, const Vector3& axis, std::list<Vector3>* out_face,
		Vector3* out_normal, std::vector<Plane>* out_adjacent_planes) const override ;

	virtual void DebugDraw(const PhysicsObject* currentObject) const override ;

protected:
	//Constructs the static cube hull 
	void ConstructCubeHull();

protected:
	static Hull			 m_CubeHull;

	float				 m_Radius;
	float				 m_length;
	float				 m_Invprecision;

	int* list3_Top;
	int* list3_Bottom;
	CySide* cyside;

	Vector3 m_CuboidHalfDimensions;
	
};

