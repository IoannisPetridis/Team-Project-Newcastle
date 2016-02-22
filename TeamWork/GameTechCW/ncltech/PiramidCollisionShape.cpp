#include "PiramidCollisionShape.h"
#include "PhysicsObject.h"
#include "GameObject.h"
#include <nclgl/Matrix3.h>
#include <nclgl/OGLRenderer.h>

Hull PiramidCollisionShape::m_CubeHull = Hull();

PiramidCollisionShape::PiramidCollisionShape()
{
	m_CuboidHalfDimensions = Vector3(0.5f, 0.5f, 0.5f);

	if (m_CubeHull.GetNumVertices() == 0)
	{
		ConstructCubeHull();
	}
}
PiramidCollisionShape::PiramidCollisionShape(const Vector3& halfdims)
{
	m_CuboidHalfDimensions = halfdims;

	if (m_CubeHull.GetNumVertices() == 0)
	{
		ConstructCubeHull();
	}
}

PiramidCollisionShape::~PiramidCollisionShape()
{
}

Matrix3 PiramidCollisionShape::BuildInverseInertia(float invMass) const
{
	Matrix3 inertia;

	Vector3 dimsSq = (m_CuboidHalfDimensions + m_CuboidHalfDimensions);
	dimsSq = dimsSq * dimsSq;

	inertia._11 = 12.f * invMass * 1.f / (dimsSq.y + dimsSq.z);
	inertia._22 = 12.f * invMass * 1.f / (dimsSq.x + dimsSq.z);
	inertia._33 = 12.f * invMass * 1.f / (dimsSq.x + dimsSq.y);
	
	//inertia._11 = (5.f * invMass * dimsSq.y) + (((3.0f/80.0f) * invMass)*dimsSq.z);
	//inertia._22 = (5.f * invMass * dimsSq.x) + (((3.0f / 80.0f) * invMass)*dimsSq.z);
	//inertia._33 = (5.f * invMass)*(dimsSq.x + dimsSq.y);


	return inertia;
}

void PiramidCollisionShape::GetCollisionAxes(const PhysicsObject* currentObject, std::vector<Vector3>* out_axes) const
{
	if (out_axes)
	{
		Matrix3 objOrientation = currentObject->GetOrientation().ToMatrix3();
		out_axes->push_back(objOrientation * Vector3(1.0f, 0.0f, 0.0f)); //X - Axis
		out_axes->push_back(objOrientation * Vector3(0.0f, 1.0f, 0.0f)); //Y - Axis
		out_axes->push_back(objOrientation * Vector3(0.0f, 0.0f, 1.0f)); //Z - Axis
	}
}

void PiramidCollisionShape::GetEdges(const PhysicsObject* currentObject, std::vector<CollisionEdge>* out_edges) const
{
	if (out_edges)
	{
		Matrix4 transform = currentObject->GetWorldSpaceTransform() * Matrix4::Scale(Vector3(m_CuboidHalfDimensions));
		for (unsigned int i = 0; i < m_CubeHull.GetNumEdges(); ++i)
		{
			const HullEdge& edge = m_CubeHull.GetEdge(i);
			Vector3 A = transform * m_CubeHull.GetVertex(edge.vStart).pos;
			Vector3 B = transform * m_CubeHull.GetVertex(edge.vEnd).pos;

			out_edges->push_back(CollisionEdge(A, B));
		}
	}
}

void PiramidCollisionShape::GetMinMaxVertexOnAxis(const PhysicsObject* currentObject, const Vector3& axis, Vector3* out_min, Vector3* out_max) const
{
	Matrix4 wsTransform = currentObject->GetWorldSpaceTransform() * Matrix4::Scale(m_CuboidHalfDimensions);

	Matrix3 invNormalMatrix = Matrix3::Transpose(Matrix3(wsTransform));
	Vector3 local_axis = invNormalMatrix * axis;

	int vMin, vMax;
	m_CubeHull.GetMinMaxVerticesInAxis(local_axis, &vMin, &vMax);

	if (out_min) *out_min = wsTransform * m_CubeHull.GetVertex(vMin).pos;
	if (out_max) *out_max = wsTransform * m_CubeHull.GetVertex(vMax).pos;
}

void PiramidCollisionShape::GetIncidentReferencePolygon(const PhysicsObject* currentObject, const Vector3& axis, std::list<Vector3>* out_face, Vector3* out_normal, std::vector<Plane>* out_adjacent_planes) const
{
	Matrix4 wsTransform = currentObject->GetWorldSpaceTransform() * Matrix4::Scale(m_CuboidHalfDimensions);

	Matrix3 invNormalMatrix = Matrix3::Inverse(Matrix3(wsTransform));
	Matrix3 normalMatrix = Matrix3::Transpose(invNormalMatrix);

	Vector3 local_axis = invNormalMatrix * axis;

	int minVertex, maxVertex;
	m_CubeHull.GetMinMaxVerticesInAxis(local_axis, &minVertex, &maxVertex);

	const HullVertex& vert = m_CubeHull.GetVertex(maxVertex);

	const HullFace* best_face = 0;
	float best_correlation = -FLT_MAX;
	for (int faceIdx : vert.enclosing_faces)
	{
		const HullFace* face = &m_CubeHull.GetFace(faceIdx);
		float temp_correlation = Vector3::Dot(local_axis, face->normal);
		if (temp_correlation > best_correlation)
		{
			best_correlation = temp_correlation;
			best_face = face;
		}
	}

	if (out_normal)
	{
		*out_normal = normalMatrix * best_face->normal;
		(*out_normal).Normalise();
	}

	if (out_face)
	{
		for (int vertIdx : best_face->vert_ids)
		{
			const HullVertex& vert = m_CubeHull.GetVertex(vertIdx);
			out_face->push_back(wsTransform * vert.pos);
		}
	}

	if (out_adjacent_planes)
	{
		//Add the reference face itself to the list of adjacent planes
		Vector3 wsPointOnPlane = wsTransform * m_CubeHull.GetVertex(m_CubeHull.GetEdge(best_face->edge_ids[0]).vStart).pos;
		Vector3 planeNrml = -(normalMatrix * best_face->normal);
		planeNrml.Normalise();
		float planeDist = -Vector3::Dot(planeNrml, wsPointOnPlane);

		out_adjacent_planes->push_back(Plane(planeNrml, planeDist));


		for (int edgeIdx : best_face->edge_ids)
		{
			const HullEdge& edge = m_CubeHull.GetEdge(edgeIdx);

			wsPointOnPlane = wsTransform * m_CubeHull.GetVertex(edge.vStart).pos;

			for (int adjFaceIdx : edge.enclosing_faces)
			{
				if (adjFaceIdx != best_face->idx)
				{
					const HullFace& adjFace = m_CubeHull.GetFace(adjFaceIdx);

					planeNrml = -(normalMatrix * adjFace.normal);
					planeNrml.Normalise();
					planeDist = -Vector3::Dot(planeNrml, wsPointOnPlane);

					out_adjacent_planes->push_back(Plane(planeNrml, planeDist));
				}
			}
		}
	}
}


void PiramidCollisionShape::DebugDraw(const PhysicsObject* currentObject) const
{
	Matrix4 transform = currentObject->GetWorldSpaceTransform() * Matrix4::Scale(m_CuboidHalfDimensions);
	m_CubeHull.DebugDraw(transform);
}

void PiramidCollisionShape::ConstructCubeHull()
{
	//Vertices

	m_CubeHull.AddVertex(Vector3(-1.0f, -1.0f, 1.0f));		// 1
	m_CubeHull.AddVertex(Vector3(1.0f, -1.0f, 1.0f));		// 2
	m_CubeHull.AddVertex(Vector3(-1.0f, -1.0f, -1.0f));		// 3
	m_CubeHull.AddVertex(Vector3(1.0f, -1.0f, -1.0f));		// 4
	m_CubeHull.AddVertex(Vector3(0.0f, 1.0f, 0.0f));		// 5

	Vector3* point = new Vector3[5];

	point[0] = Vector3(-1.0f, -1.0f, 1.0f);
	point[1] = Vector3(1.0f, -1.0f, 1.0f);
	point[2] = Vector3(-1.0f, -1.0f, -1.0f);
	point[3] = Vector3(1.0f, -1.0f, -1.0f);
	point[4] = Vector3(0.0f, 1.0f, 0.0f);

	Vector3* normal = new Vector3[4];
	
	int face[4][3] = { { 0, 1, 4 }, { 1, 3, 4 }, {3,2,4 }, {  2,0, 4 } };

	/*face[1][] = { 0, 1, 4 };
	int face2[] = { 1,3,4 };
	int face3[] = { 2, 3,4 };
	int face4[] = { 0,2,4};*/

	int face5[] = { 0,1,3,2 };

	for (int i = 0; i < 4;i++)
	{
			Vector3 U = point[face[i][1]] - point[face[i][0]];
			Vector3 V = point[face[i][2]] - point[face[i][0]];
			normal[i] = Vector3::Cross(U, V);
	
			normal[i].Normalise();
			
	}
	


	//Faces
	m_CubeHull.AddFace(normal[0], 3, face[0]);
	m_CubeHull.AddFace(normal[1], 3, face[1]);
	m_CubeHull.AddFace(normal[2], 3, face[2]);
	m_CubeHull.AddFace(normal[3], 3, face[3]);
	
	//Vector3 temp = Vector3::Cross(point[0], point[1]);
	//temp.Normalise();

		//m_CubeHull.AddFace(temp, 4, face5);

	m_CubeHull.AddFace(Vector3(0.0f, -1.0f, 0.0f), 4, face5);

	//delete normal;
	//delete point;

////second version
//	//Vertices
//	Vector3 v0 = Vector3(-1.0f, -1.0f, 1.0f);
//	Vector3 v1 = Vector3(-1.0f, -1.0f, -1.0f);
//	Vector3 v2 = Vector3(1.0f, -1.0f, -1.0f);
//	Vector3 v3 = Vector3(1.0f, -1.0f, 1.0f);
//	Vector3 v4 = Vector3(0.0f, 1.0f, 0.0f);
//
//	m_CubeHull.AddVertex(v0);		// 0
//	m_CubeHull.AddVertex(v1);		// 1
//	m_CubeHull.AddVertex(v2);		// 2
//	m_CubeHull.AddVertex(v3);		// 3
//	m_CubeHull.AddVertex(v4);		// 4
//
//	int face1[] = { 0, 1, 2, 3 };
//	int face2[] = { 0, 1, 4 };
//	int face3[] = { 1, 2, 4 };
//	int face4[] = { 2, 3, 4 };
//	int face5[] = { 3, 0, 4 };
//
//	//Faces
//	Vector3 n1 = Vector3::Cross((v4 - v1), (v0 - v1));
//	Vector3 n2 = Vector3::Cross((v4 - v2), (v1 - v2));
//	Vector3 n3 = Vector3::Cross((v4 - v3), (v2 - v3));
//	Vector3 n4 = Vector3::Cross((v4 - v0), (v3 - v0));
//
//	n1.Normalise();
//	n2.Normalise();
//	n3.Normalise();
//	n4.Normalise();
//
//
//	m_CubeHull.AddFace(Vector3(0.0f, -1.0f, 0.0f), 4, face1);
//	m_CubeHull.AddFace(n1, 3, face2);
//	m_CubeHull.AddFace(n2, 3, face3);
//	m_CubeHull.AddFace(n3, 3, face4);
//	m_CubeHull.AddFace(n4, 3, face5);
}
