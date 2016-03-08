#include "CollisionDetection.h"
#include "GameObject.h"
#include "Matrix3.h"
#include "Plane.h"
#include "SphereCollisionShape.h"
#include "PhysicsEngine.h"
#include "NCLDebug.h"


bool CollisionDetection::CheckSphereSphereCollision(const PhysicsObject* obj1, const PhysicsObject* obj2, const CollisionShape* shape1, const CollisionShape* shape2, CollisionData* out_coldata) const
{
	/**
	TUTORIAL 5 CODE - Simple Collision Detection Checks
	*/

	const SphereCollisionShape* sphere1 =
		dynamic_cast<const SphereCollisionShape*>(shape1);
	const SphereCollisionShape* sphere2 =
		dynamic_cast<const SphereCollisionShape*>(shape2);

	if (sphere1 == NULL || sphere2 == NULL) {
		return false;
	}

	//sphere-sphere check 

	float sum_radius = sphere1->GetRadius() + sphere2->GetRadius();
	float sum_radius_squared = sum_radius * sum_radius;

	Vector3 ab = obj2->GetPosition() - obj1->GetPosition();
	float distance_squared = Vector3::Dot(ab, ab);

	//true meaning collision
	return (distance_squared <= sum_radius_squared);
	
	//return false;
}


void AddPossibleCollisionAxis(Vector3& axis, std::vector<Vector3>* possible_collision_axes)
{
	const float epsilon = 0.0001f;

	//is axis 0,0,0??
	if (Vector3::Dot(axis, axis) < epsilon)
		return;

	axis.Normalise();

	for (const Vector3& p_axis : *possible_collision_axes)
	{
		//Is axis very close to the same as a previous axis already in the list of axes??
		if (Vector3::Dot(axis, p_axis) >= 1.0f - epsilon)
			return;
	}

	possible_collision_axes->push_back(axis);
}

bool CollisionDetection::CheckCollision(const PhysicsObject* obj1, const PhysicsObject* obj2, const CollisionShape* shape1, const CollisionShape* shape2, CollisionData* out_coldata) const
{
	CollisionData cur_colData;
	CollisionData best_colData;
	//in case the overhead
	best_colData.penetration = -FLT_MAX;

	//first we need the collision axes of both shapes
	std::vector<Vector3> possible_collision_axes;

	shape1->GetCollisionAxes(obj1, &possible_collision_axes);
	shape2->GetCollisionAxes(obj2, &possible_collision_axes);

	//Now we need to check the edge-edge cases
	//between the two convex hulls
	std::vector<CollisionEdge> shape1_edges;
	std::vector<CollisionEdge> shape2_edges;
	shape1->GetEdges(obj1, &shape1_edges);
	shape2->GetEdges(obj2, &shape2_edges);


	//Now we need to check the edge-edge cases
	//between the two convex hulls
	for (const CollisionEdge& edge1 : shape1_edges) {
		for (const CollisionEdge& edge2 : shape2_edges)
		{
			Vector3 e1 = edge1.posB - edge1.posA;
			Vector3 e2 = edge2.posB - edge2.posA;

			e1.Normalise();
			e2.Normalise();

			AddPossibleCollisionAxis(Vector3::Cross(e1, e2),
				&possible_collision_axes);
		}
	}

	//Now we have to handle the specifc case of sphere,
	//which have infinite collision axes and edges

	bool shape1_isSphere = shape1_edges.empty();
	bool shape2_isSphere = shape2_edges.empty();

	//if both are spehere, then the only axes we have to
	//check is between the two centre points
	if (shape1_isSphere && shape2_isSphere) {
		Vector3 axis = obj2->GetPosition() - obj1->GetPosition();
		axis.Normalise();
		AddPossibleCollisionAxis(axis, &possible_collision_axes);
	}
	else if (shape1_isSphere) //only if shape1 is a sphere
	{
		Vector3 p =
			GetClosestPointOnEdges(obj1->GetPosition(), shape2_edges);
		//NCLDebug::drawPoint(p, 0.1f);
		Vector3 p_t = obj1->GetPosition() - p;
		p_t.Normalise();
		AddPossibleCollisionAxis(p_t, &possible_collision_axes);
	}
	else if (shape2_isSphere) //only if shape2 is a sphere
	{
		Vector3 p =
			GetClosestPointOnEdges(obj2->GetPosition(), shape1_edges);
		Vector3 p_t = obj2->GetPosition() - p;
		//NCLDebug::DrawPoint(p, 0.1f);
		p_t.Normalise();
		AddPossibleCollisionAxis(p_t, &possible_collision_axes);
	}


	//for all possible axes, check each one until a seperating axis
	//between the two objects can be found - such proving the objects
	//cannot be colliding

	for (const Vector3& axis : possible_collision_axes) {
		//if the collision axis does not intersect then return
		//immediately as we know that atleast in one direction/axis
		//the two objects do not intersect

		if (!CheckCollisionAxis(axis, obj1, obj2, shape1, shape2, &cur_colData))
			return false;

		//judge from the penetration each colData has
		//the deepest one take over and set the collision normal to it
		if (cur_colData.penetration >= best_colData.penetration) {
			best_colData = cur_colData;
		}
	}

	//NCLDebug::DrawHairLine(obj2->GetPosition(), obj2->GetPosition() + best_colData.normal,
	//	Vector4(1.0f, .0f, 1.f, 1.f));

	if (out_coldata)
		*out_coldata = best_colData;

	return true;
}

bool CollisionDetection::CheckDistance(const PhysicsObject* obj1, const PhysicsObject* obj2, const CollisionShape* shape1, const CollisionShape* shape2, float& penetration) const
{
	float best_penetration = 0;
	float cur_penetration = 0;

	std::vector<Vector3> possible_collision_axes;

	shape1->GetCollisionAxes(obj1, &possible_collision_axes);
	shape2->GetCollisionAxes(obj2, &possible_collision_axes);

	std::vector<CollisionEdge> shape1_edges;
	std::vector<CollisionEdge> shape2_edges;
	shape1->GetEdges(obj1, &shape1_edges);
	shape2->GetEdges(obj2, &shape2_edges);

	for (const CollisionEdge& edge1 : shape1_edges) {
		for (const CollisionEdge& edge2 : shape2_edges)
		{
			Vector3 e1 = edge1.posB - edge1.posA;
			Vector3 e2 = edge2.posB - edge2.posA;

			e1.Normalise();
			e2.Normalise();

			AddPossibleCollisionAxis(Vector3::Cross(e1, e2),
				&possible_collision_axes);
		}
	}

	bool shape1_isSphere = shape1_edges.empty();
	bool shape2_isSphere = shape2_edges.empty();

	if (shape1_isSphere && shape2_isSphere) {
		Vector3 axis = obj2->GetPosition() - obj1->GetPosition();
		axis.Normalise();
		AddPossibleCollisionAxis(axis, &possible_collision_axes);
	}
	else if (shape1_isSphere)
	{
		Vector3 p =
			GetClosestPointOnEdges(obj1->GetPosition(), shape2_edges);
		Vector3 p_t = obj1->GetPosition() - p;
		p_t.Normalise();
		AddPossibleCollisionAxis(p_t, &possible_collision_axes);
	}
	else if (shape2_isSphere) 
	{
		Vector3 p =
			GetClosestPointOnEdges(obj2->GetPosition(), shape1_edges);
		Vector3 p_t = obj2->GetPosition() - p;
		p_t.Normalise();
		AddPossibleCollisionAxis(p_t, &possible_collision_axes);
	}

	for (const Vector3& axis : possible_collision_axes) {
		cur_penetration = CheckDisAxis(axis, obj1, obj2, shape1, shape2);
		if (cur_penetration >= best_penetration){
			best_penetration = cur_penetration;
		}
	}
	
	penetration = best_penetration;

	return true;
}

float CollisionDetection::CheckDisAxis(const Vector3& axis, const PhysicsObject* obj1, const PhysicsObject* obj2, const CollisionShape* shape1, const CollisionShape* shape2) const {
	Vector3 min1, min2, max1, max2;

	shape1->GetMinMaxVertexOnAxis(obj1, axis, &min1, &max1);
	shape2->GetMinMaxVertexOnAxis(obj2, axis, &min2, &max2);

	float minCorrelation1 = Vector3::Dot(axis, min1);
	float maxCorrelation1 = Vector3::Dot(axis, max1);
	float minCorrelation2 = Vector3::Dot(axis, min2);
	float maxCorrelation2 = Vector3::Dot(axis, max2);

	if (minCorrelation1 <= minCorrelation2
		&& maxCorrelation1 <= minCorrelation2) return (minCorrelation2 - maxCorrelation1);
	if (minCorrelation2 <= minCorrelation1
		&& maxCorrelation2 <= minCorrelation1) return (minCorrelation1 - maxCorrelation2);
	else return 0;
}


bool CollisionDetection::CheckCollisionAxis(const Vector3& axis, const PhysicsObject* obj1, const PhysicsObject* obj2, const CollisionShape* shape1, const CollisionShape* shape2, CollisionData* out_coldata) const
{
	Vector3 min1, min2, max1, max2;

	shape1->GetMinMaxVertexOnAxis(obj1, axis, &min1, &max1);
	shape2->GetMinMaxVertexOnAxis(obj2, axis, &min2, &max2);

	float minCorrelation1 = Vector3::Dot(axis, min1);
	float maxCorrelation1 = Vector3::Dot(axis, max1);
	float minCorrelation2 = Vector3::Dot(axis, min2);
	float maxCorrelation2 = Vector3::Dot(axis, max2);

	if (minCorrelation1 <= minCorrelation2
		&& maxCorrelation1 >= minCorrelation2) {
		if (out_coldata != NULL) {
			out_coldata->normal = axis;
			out_coldata->penetration =
				minCorrelation2 - maxCorrelation1;
			out_coldata->pointOnPlane =
				max1 + out_coldata->normal * out_coldata->penetration;
		}

		return true;
	}

	if (minCorrelation2 <= minCorrelation1
		&& maxCorrelation2 > minCorrelation1) {
		if (out_coldata != NULL) {
			out_coldata->normal = -axis;
			out_coldata->penetration =
				minCorrelation1 - maxCorrelation2;
			out_coldata->pointOnPlane =
				min1 + out_coldata->normal * out_coldata->penetration;
		}

		return true;
	}
	return false;
}


bool CollisionDetection::BuildCollisionManifold(const PhysicsObject* obj1, const PhysicsObject* obj2, const CollisionShape* shape1, const CollisionShape* shape2, const CollisionData& coldata, Manifold* manifold) const
{
	/*
	TUTORIAL 8 CODE - Collision Manifolds
	*/
	if (!manifold)
		return false;

	//Get the required face information for the two shapes
	//around the collision normal

	std::list<Vector3> polygon1, polygon2;
	Vector3 normal1, normal2;
	std::vector<Plane> adjPlanes1, adjPlanes2;

	shape1->GetIncidentReferencePolygon(obj1, coldata.normal,
		&polygon1, &normal1, &adjPlanes1);
	shape2->GetIncidentReferencePolygon(obj2, -coldata.normal,
		&polygon2, &normal2, &adjPlanes2);

	//if either shape1 or shape2 returned a single point, then 
	//it must be on a curve and thus the only contact point to 
	//generate is already availbe

	if (polygon1.size() == 0 || polygon2.size() == 0) {
		return false;
	}
	else if (polygon1.size() == 1) {
		manifold->AddContact(polygon1.front(),
			polygon1.front() - coldata.normal * coldata.penetration,
			coldata.normal, coldata.penetration);
	}
	else if (polygon2.size() == 1) {
		manifold->AddContact(polygon2.front() +
			coldata.normal * coldata.penetration, polygon2.front(),
			coldata.normal, coldata.penetration);
	}
	else{
		//otherwise use clipping to cut down the incident face to 
		//fit inside the reference planes using the surounding face
		//planes

		bool flipped;
		std::list<Vector3> *incPolygon;
		Vector3 *incNormal;
		std::vector<Plane> *refAdjPlanes;
		Plane refPlane;

		//Get the incident and reference polygons
		if (fabs(Vector3::Dot(coldata.normal, normal1)) >
			fabs(Vector3::Dot(coldata.normal, normal2))) {
			float planeDist = -Vector3::Dot(-normal1, polygon1.front());
			refPlane = Plane(-normal1, planeDist);
			refAdjPlanes = &adjPlanes1;

			incPolygon = &polygon2;
			incNormal = &normal2;

			flipped = false;
		}
		else
		{
			float planeDist = -Vector3::Dot(-normal2, polygon2.front());
			refPlane = Plane(-normal2, planeDist);
			refAdjPlanes = &adjPlanes2;

			incPolygon = &polygon1;
			incNormal = &normal1;

			flipped = true;
		}

		//Clip the incident face to the adjacent edges of the 
		//reference face

		SutherlandHodgesonClipping(*incPolygon, refAdjPlanes->size(),
			&(*refAdjPlanes)[0], incPolygon, false);

		//finally clip (and remove) any contact points that are above
		//the reference face

		SutherlandHodgesonClipping(*incPolygon, 1, &refPlane, incPolygon, true);

		//Now we are left with a selection of valid contact points
		//to be sued for the manifold 

		Vector3 startPoint = incPolygon->back();
		for (const Vector3& endPoint : *incPolygon) {
			float contact_penetration;
			Vector3 globalOnA, globalOnB;

			if (flipped) {
				// calculate distance to ref plane/face
				contact_penetration = -(Vector3::Dot(endPoint, coldata.normal)
					- Vector3::Dot(coldata.normal, polygon2.front()));

				//contact_penetration = min(contact_penetration, 0.0f);

				globalOnA = endPoint + coldata.normal * contact_penetration;
				globalOnB = endPoint;
			}

			else{
				//calculate distance to ref plane/face
				contact_penetration =
					Vector3::Dot(endPoint, coldata.normal) -
					Vector3::Dot(coldata.normal, polygon1.front());

				//contact_penetration = min(contact_penetration, 0.0f);

				globalOnA = endPoint;
				globalOnB = endPoint
					- coldata.normal * contact_penetration;
			}

			manifold->AddContact(globalOnA, globalOnB,
				coldata.normal, contact_penetration);

			startPoint = endPoint;
		}
	}

	return true;
}



/*
Additional geometric functions such as clipping point to a line, clipping edges to a series of planes
*/
Vector3 CollisionDetection::GetClosestPointOnEdges(const Vector3& target, const std::vector<CollisionEdge>& edges) const
{
	Vector3 closest_point, temp_closest_point;
	float closest_distsq = FLT_MAX;

	for (const CollisionEdge& edge : edges)
	{
		Vector3 a_t = target - edge.posA;
		Vector3 a_b = edge.posB - edge.posA;

		float magnitudeAB = Vector3::Dot(a_b, a_b);   //Magnitude of AB vector (it's length squared)     
		float ABAPproduct = Vector3::Dot(a_t, a_b);   //The DOT product of a_to_t and a_to_b     
		float distance = ABAPproduct / magnitudeAB; //The normalized "distance" from a to your closest point  

		if (distance < 0.0f)     //Clamp returned point to be on the line, e.g if the closest point is beyond the AB return either A or B as closest points  
		{
			temp_closest_point = edge.posA;

		}
		else if (distance > 1) {
			temp_closest_point = edge.posB;
		}
		else
		{
			temp_closest_point = edge.posA + a_b * distance;
		}

		Vector3 c_t = target - temp_closest_point;
		float temp_distsq = Vector3::Dot(c_t, c_t);

		if (temp_distsq < closest_distsq)
		{
			closest_distsq = temp_distsq;
			closest_point = temp_closest_point;
		}
	}

	return closest_point;
}

Vector3 CollisionDetection::PlaneEdgeIntersection(const Plane& plane, const Vector3& start, const Vector3& end) const
{
	float start_dist = Vector3::Dot(start, plane.GetNormal()) + plane.GetDistance();
	float end_dist = Vector3::Dot(end, plane.GetNormal()) + plane.GetDistance();

	Vector3 ab = end - start;

	float ab_p = Vector3::Dot(plane.GetNormal(), ab);

	if (fabs(ab_p) > 0.0001f)
	{
		Vector3 p_co = plane.GetNormal() * (-plane.GetDistance());

		Vector3 w = start - p_co;
		float fac = -Vector3::Dot(plane.GetNormal(), w) / ab_p;
		ab = ab * fac;

		return start + ab;
	}

	return start;
}

void CollisionDetection::SutherlandHodgesonClipping(const std::list<Vector3>& input_polygon, int num_clip_planes, const Plane* clip_planes, std::list<Vector3>* out_polygon, bool removePoints) const
{
	if (!out_polygon)
		return;

	std::list<Vector3> ppPolygon1, ppPolygon2;
	std::list<Vector3> *input = &ppPolygon1, *output = &ppPolygon2;

	*output = input_polygon;
	for (int iterations = 0; iterations < num_clip_planes; ++iterations)
	{
		if (output->empty())
			break;

		const Plane& plane = clip_planes[iterations];

		std::swap(input, output);
		output->clear();

		Vector3 startPoint = input->back();
		for (const Vector3& endPoint : *input)
		{
			bool startInPlane = plane.PointInPlane(startPoint);
			bool endInPlane = plane.PointInPlane(endPoint);

			if (removePoints)
			{
				if (endInPlane)
					output->push_back(endPoint);
			}
			else
			{
				//if entire edge is within the clipping plane, keep it as it is
				if (startInPlane && endInPlane)
					output->push_back(endPoint);

				//if edge interesects the clipping plane, cut the edge along clip plane
				else if (startInPlane && !endInPlane)
				{
					output->push_back(PlaneEdgeIntersection(plane, startPoint, endPoint));
				}
				else if (!startInPlane && endInPlane)
				{
					output->push_back(PlaneEdgeIntersection(plane, endPoint, startPoint));					
					output->push_back(endPoint);
				}
			}

			//..otherwise the edge is entirely outside the clipping plane and should be removed


			startPoint = endPoint;
		}
	}

	*out_polygon = *output;
}
