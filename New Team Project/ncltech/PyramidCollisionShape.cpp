#include "PyramidCollisionShape.h"
#include "PhysicsObject.h"
#include "GameObject.h"
#include <nclgl/Matrix3.h>
#include <nclgl/OGLRenderer.h>

Hull PyramidCollisionShape::m_PyramidHull = Hull();

PyramidCollisionShape::PyramidCollisionShape()
{
	m_PyramidHalfDimensions = Vector3(0.5f, 0.5f, 0.5f);

	if (m_PyramidHull.GetNumVertices() == 0)
	{
		ConstructPyramidHull();
	}
}

PyramidCollisionShape::PyramidCollisionShape(const Vector3& halfdims)
{
	m_PyramidHalfDimensions = halfdims;

	if (m_PyramidHull.GetNumVertices() == 0)
	{
		ConstructPyramidHull();
	}
}

PyramidCollisionShape::~PyramidCollisionShape()
{

}

Matrix3 PyramidCollisionShape::BuildInverseInertia(float invMass) const
{
	Matrix3 inertia;

	float hSquared = 1 * 1;
	float rSquared = 0.5 * 0.5;

	float i = ((5.0f * invMass) / rSquared) + ((26.66f * invMass) / hSquared);
	float k = ((5.0f * invMass) / (rSquared + rSquared));


	inertia._11 = i;
	inertia._22 = i;
	inertia._33 = k;

	return inertia;
}

void PyramidCollisionShape::GetCollisionAxes(const PhysicsObject* currentObject, std::vector<Vector3>* out_axes) const
{
	if (out_axes)
	{
		Matrix3 objOrientation = currentObject->GetOrientation().ToMatrix3();
		out_axes->push_back(objOrientation * Vector3(1.0f, 0.0f, 0.0f)); //X - Axis
		out_axes->push_back(objOrientation * Vector3(0.0f, 1.0f, 0.0f)); //Y - Axis
		out_axes->push_back(objOrientation * Vector3(0.0f, 0.0f, 1.0f)); //Z - Axis
	}
}

void PyramidCollisionShape::GetEdges(const PhysicsObject* currentObject, std::vector<CollisionEdge>* out_edges) const
{
	if (out_edges)
	{
		Matrix4 transform = currentObject->GetWorldSpaceTransform() * Matrix4::Scale(Vector3(m_PyramidHalfDimensions));
		for (unsigned int i = 0; i < m_PyramidHull.GetNumEdges(); ++i)
		{
			const HullEdge& edge = m_PyramidHull.GetEdge(i);
			Vector3 A = transform * m_PyramidHull.GetVertex(edge.vStart).pos;
			Vector3 B = transform * m_PyramidHull.GetVertex(edge.vEnd).pos;

			out_edges->push_back(CollisionEdge(A, B));
		}
	}
}

void PyramidCollisionShape::GetMinMaxVertexOnAxis(const PhysicsObject* currentObject, const Vector3& axis, Vector3* out_min, Vector3* out_max) const
{
	Matrix4 wsTransform = currentObject->GetWorldSpaceTransform() * Matrix4::Scale(m_PyramidHalfDimensions);

	Matrix3 invNormalMatrix = Matrix3::Transpose(Matrix3(wsTransform));
	Vector3 local_axis = invNormalMatrix * axis;

	int vMin, vMax;
	m_PyramidHull.GetMinMaxVerticesInAxis(local_axis, &vMin, &vMax);

	if (out_min) *out_min = wsTransform * m_PyramidHull.GetVertex(vMin).pos;
	if (out_max) *out_max = wsTransform * m_PyramidHull.GetVertex(vMax).pos;
}

void PyramidCollisionShape::GetIncidentReferencePolygon(const PhysicsObject* currentObject, const Vector3& axis, std::list<Vector3>* out_face, Vector3* out_normal, std::vector<Plane>* out_adjacent_planes) const
{
	Matrix4 wsTransform = currentObject->GetWorldSpaceTransform() * Matrix4::Scale(m_PyramidHalfDimensions);

	Matrix3 invNormalMatrix = Matrix3::Inverse(Matrix3(wsTransform));
	Matrix3 normalMatrix = Matrix3::Transpose(invNormalMatrix);

	Vector3 local_axis = invNormalMatrix * axis;

	int minVertex, maxVertex;
	m_PyramidHull.GetMinMaxVerticesInAxis(local_axis, &minVertex, &maxVertex);

	const HullVertex& vert = m_PyramidHull.GetVertex(maxVertex);

	const HullFace* best_face = 0;
	float best_correlation = -FLT_MAX;
	for (int faceIdx : vert.enclosing_faces)
	{
		const HullFace* face = &m_PyramidHull.GetFace(faceIdx);
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
			const HullVertex& vert = m_PyramidHull.GetVertex(vertIdx);
			out_face->push_back(wsTransform * vert.pos);
		}
	}

	if (out_adjacent_planes)
	{
		//Add the reference face itself to the list of adjacent planes
		Vector3 wsPointOnPlane = wsTransform * m_PyramidHull.GetVertex(m_PyramidHull.GetEdge(best_face->edge_ids[0]).vStart).pos;
		Vector3 planeNrml = -(normalMatrix * best_face->normal);
		planeNrml.Normalise();
		float planeDist = -Vector3::Dot(planeNrml, wsPointOnPlane);

		out_adjacent_planes->push_back(Plane(planeNrml, planeDist));


		for (int edgeIdx : best_face->edge_ids)
		{
			const HullEdge& edge = m_PyramidHull.GetEdge(edgeIdx);

			wsPointOnPlane = wsTransform * m_PyramidHull.GetVertex(edge.vStart).pos;

			for (int adjFaceIdx : edge.enclosing_faces)
			{
				if (adjFaceIdx != best_face->idx)
				{
					const HullFace& adjFace = m_PyramidHull.GetFace(adjFaceIdx);

					planeNrml = -(normalMatrix * adjFace.normal);
					planeNrml.Normalise();
					planeDist = -Vector3::Dot(planeNrml, wsPointOnPlane);

					out_adjacent_planes->push_back(Plane(planeNrml, planeDist));
				}
			}
		}
	}
}


void PyramidCollisionShape::DebugDraw(const PhysicsObject* currentObject) const
{
	Matrix4 transform = currentObject->GetWorldSpaceTransform() * Matrix4::Scale(m_PyramidHalfDimensions);
	m_PyramidHull.DebugDraw(transform);
}

void PyramidCollisionShape::ConstructPyramidHull()
{
	Vector3 zero = Vector3(-1, -1, 1);
	Vector3 one = Vector3(1, -1, 1);
	Vector3 two = Vector3(1, -1, -1);
	Vector3 three = Vector3(-1, -1, -1);
	Vector3 four = Vector3(0, 1, 0);

	//Vertices
	m_PyramidHull.AddVertex(zero);		// 0
	m_PyramidHull.AddVertex(one);		// 1
	m_PyramidHull.AddVertex(two);		// 2
	m_PyramidHull.AddVertex(three);		// 3
	m_PyramidHull.AddVertex(four);		// 4

	int face1[] = { 0, 1, 2, 3 };
	int face2[] = { 0, 1, 4 };
	int face3[] = { 1, 2, 4 };
	int face4[] = { 2, 3, 4 };
	int face5[] = { 3, 0, 4 };

	//Faces
	m_PyramidHull.AddFace(Vector3::Cross((zero - one), (two - one)).Normalise(), 4, face1);
	m_PyramidHull.AddFace(Vector3::Cross((one - zero), (four - zero)).Normalise(), 3, face2);
	m_PyramidHull.AddFace(Vector3::Cross((two - one), (four - one)).Normalise(), 3, face3);
	m_PyramidHull.AddFace(Vector3::Cross((three - two), (four - two)).Normalise(), 3, face4);
	m_PyramidHull.AddFace(Vector3::Cross((zero - three), (four - three)).Normalise(), 3, face5);

}