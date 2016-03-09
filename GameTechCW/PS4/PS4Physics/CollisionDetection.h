#pragma once
#include "TSingleton.h"
#include "PhysicsObject.h"
#include "CollisionShape.h"
#include "Manifold.h"

struct CollisionData
{
	float penetration;
	GLMVector3 normal;
	GLMVector3 pointOnPlane;
};

class CollisionDetection : public TSingleton < CollisionDetection >
{
	friend class TSingleton < CollisionDetection > ;

public:
	bool CheckSphereSphereCollision(const PhysicsObject* obj1, const PhysicsObject* obj2, const CollisionShape* shape1, const CollisionShape* shape2, CollisionData* out_coldata = NULL) const;
	bool CheckCollision(const PhysicsObject* obj1, const PhysicsObject* obj2, const CollisionShape* shape1, const CollisionShape* shape2, CollisionData* out_coldata = NULL) const;
	bool BuildCollisionManifold(const PhysicsObject* obj1, const PhysicsObject* obj2, const CollisionShape* shape1, const CollisionShape* shape2, const CollisionData& coldata, Manifold* out_manifold) const;
	
	//yields the distance between wall and a seleted object
	bool CheckDistance(const PhysicsObject* obj1, const PhysicsObject* obj2, const CollisionShape* shape1, const CollisionShape* shape2, float& penetration) const;

protected:
	bool CheckCollisionAxis(const GLMVector3& axis, const PhysicsObject* obj1, const PhysicsObject* obj2, const CollisionShape* shape1, const CollisionShape* shape2, CollisionData* out_coldata) const;
	
	//yields the distance between wall and a selected object, called by checkdistance
	float CheckDisAxis(const GLMVector3& axis, const PhysicsObject* obj1, const PhysicsObject* obj2, const CollisionShape* shape1, const CollisionShape* shape2) const;

	GLMVector3 GetClosestPointOnEdges(const GLMVector3& target, const std::vector<CollisionEdge>& edges) const;
	GLMVector3 PlaneEdgeIntersection(const Plane& plane, const GLMVector3& start, const GLMVector3& end) const;
	void	SutherlandHodgesonClipping(const std::list<GLMVector3>& input_polygon, int num_clip_planes, const Plane* clip_planes, std::list<GLMVector3>* out_polygon, bool removePoints) const;
	void AddPossibleCollisionAxis(const GLMVector3& axis, std::vector<GLMVector3>& possible_collision_axes) const;
};