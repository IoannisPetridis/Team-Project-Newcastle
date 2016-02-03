#pragma once
#include <ncltech\GameObject.h>
#include <ncltech\NCLDebug.h>


class   OcTree;
typedef bool(*callback)(const OcTree &o, void *data);


class   OcTree
{
public:
	// Construction/Destruction
	OcTree();

	virtual                         ~OcTree();

	// Accessors

	
	inline  OcTree*         GetChild(int index) const { return _child[index]; }

	
	//vector<PhysicsObject*> * getPhysicsObjectsList(){ return _physicObjectsVecList; };

	float GetRadius(){ return _radius; }
	Vector3 GetCenter(){ return _center; }

	inline  const   unsigned int    GetpointCount() const { return _pointCount; }
	void    SetpointCount(int in) { _pointCount = in; }
	//virtual void checkOverlapUpdate(OcTree* tree);
	// Implementation

	virtual const   bool            build(vector<PhysicsObject*> physicsObjects,vector<PhysicsObject*> referenceObject, const unsigned int threshold, const unsigned int maximumDepth
		, Vector3 center, float radius, const unsigned int currentDepth = 0);

	//static  const   Bounds          calcCubicBounds(const Point * const * points,const unsigned int count);
	virtual const   bool            traverse(callback proc, void *data) const;
	virtual void getCollisionPair(vector<CollisionPair> &m_BroadphaseCollisionPairs);
	//virtual void pushToChild2(OcTree* tree, PhysicsObject* physicsObject, Vector3 objMin, Vector3 objMax);
	//virtual void OcTree::pushToParent2(OcTree* tree, PhysicsObject* physicsObject, Vector3 objMin, Vector3 objMax);
	virtual void DebugDraw() const {

		Vector3 bottomRightFront = Vector3(_center.x + _radius, _center.y + _radius, _center.z - _radius);
		Vector3 bottomLeftFront = Vector3(_center.x - _radius, _center.y + _radius, _center.z - _radius);
		Vector3 bottomLeftBack = Vector3(_center.x - _radius, _center.y - _radius, _center.z - _radius);
		Vector3 bottomRightBack = Vector3(_center.x + _radius, _center.y - _radius, _center.z - _radius);
		Vector3 topRightFront = Vector3(_center.x + _radius, _center.y + _radius, _center.z + _radius);
		Vector3 topLeftFront = Vector3(_center.x - _radius, _center.y + _radius, _center.z + _radius);
		Vector3 topLeftBack = Vector3(_center.x - _radius, _center.y - _radius, _center.z + _radius);
		Vector3 topRightBack = Vector3(_center.x + _radius, _center.y - _radius, _center.z + _radius);
		Vector4 col = Vector4(0, 0, 0, 1);
		float thinkness = 0.05f*(_currentDepth + 1);
		NCLDebug::DrawThickLine(bottomRightFront, bottomLeftFront, thinkness, col);
		NCLDebug::DrawThickLine(bottomLeftFront, bottomLeftBack, thinkness, col);
		NCLDebug::DrawThickLine(bottomLeftBack, bottomRightBack, thinkness, col);
		NCLDebug::DrawThickLine(bottomRightBack, bottomRightFront, thinkness, col);
		NCLDebug::DrawThickLine(topRightFront, topLeftFront, thinkness, col);
		NCLDebug::DrawThickLine(topLeftFront, topLeftBack, thinkness, col);
		NCLDebug::DrawThickLine(topLeftBack, topRightBack, thinkness, col);
		NCLDebug::DrawThickLine(topRightBack, topRightFront, thinkness, col);
		NCLDebug::DrawThickLine(bottomRightFront, topRightFront, thinkness, col);
		NCLDebug::DrawThickLine(bottomRightBack, topRightBack, thinkness, col);
		NCLDebug::DrawThickLine(bottomLeftFront, topLeftFront, thinkness, col);
		NCLDebug::DrawThickLine(bottomLeftBack, topLeftBack, thinkness, col);
		//draw children
		for (int i = 0; i < 8; i++) {
			if (_child[i]) _child[i]->DebugDraw();
		}
	}
	void setParent(OcTree* ParentTree){ _parent = ParentTree; }
	OcTree* getParent(){ return _parent; }
	static bool showOctree;
protected:
	OcTree                  *_child[8];
	OcTree					*_parent;
	unsigned int            _pointCount;
	Vector3                   _center;
	float                  _radius;
	double _currentDepth;
	
	//---------------------------------------

	vector<PhysicsObject*> _physicObjectsVecList;
	vector<PhysicsObject*> _referenceObjectList;
	Vector3 _centerVec;
};

// -----------------------------------------------------------------------------
// Construction -- Just "nullify" the class
// -----------------------------------------------------------------------------
bool OcTree::showOctree = true;


OcTree::OcTree()
{
	_pointCount = 0;
	_center.x = 0;
	_center.y = 0;
	_center.z = 0;
	_radius = 0.0f;
	memset(_child, 0, sizeof(_child));
}
// -----------------------------------------------------------------------------
// Destruction -- free up memory
// -----------------------------------------------------------------------------

OcTree::~OcTree()
{
	delete[] _child;
	delete _parent;
}

void OcTree::getCollisionPair(vector<CollisionPair> &m_BroadphaseCollisionPairs)
{

	// 1. Do I have any POs? => Create collision pairs
	//    Otherwise, I know I'll have children.

	if (this->_physicObjectsVecList.size() > 0)// this is child node
	{
		PhysicsObject *objA, *objB;

		//create pair in between all object in child node with it self
		for (size_t i = 0; i < _physicObjectsVecList.size()-1; ++i)
		{
			for (size_t j = i + 1; j < _physicObjectsVecList.size(); ++j)
			{
				//one of the  object must be wake in order to create a pair
				//we do not compair sleep object with sleep object
				if (_physicObjectsVecList[i]->GetIsWake() || _physicObjectsVecList[j]->GetIsWake() )
				{
					objA = _physicObjectsVecList[i];
					objB = _physicObjectsVecList[j];
					CollisionPair cp;
					cp.objectA = objA;
					cp.objectB = objB;
					m_BroadphaseCollisionPairs.push_back(cp);
				}
			}
		}
		// create pair between all object in child node with the referencelist
		for (int i = 0; i < _physicObjectsVecList.size();i++)
		{	
			for (int j = 0; j < _referenceObjectList.size(); j++)
			{
				//one of the  object must be wake in order to create a pair
				//we do not compair sleep object with sleep object
				if (_physicObjectsVecList[i]->GetIsWake() || _referenceObjectList[j]->GetIsWake())
				{
					objA = _physicObjectsVecList[i];
					objB = _referenceObjectList[j];
					CollisionPair cp;
					cp.objectA = objA;
					cp.objectB = objB;
					m_BroadphaseCollisionPairs.push_back(cp);
				}
			}
		}
	}
	else // this node is not a child
	{
		for (int i = 0; i < 8; i++)
		{
			if (_child[i] != NULL)
			{
				//go though all the child recursivly
				_child[i]->getCollisionPair(m_BroadphaseCollisionPairs);
			}
		}
	}


}
const   bool    OcTree::build(vector<PhysicsObject*> physicsObjects, vector<PhysicsObject*> referenceObject, const unsigned int threshold, const unsigned int maximumDepth,
	Vector3 center, float radius, const unsigned int currentDepth)
{
	//Drew center
	if (showOctree)
	{
		NCLDebug::DrawPoint(center, 0.2, Vector4(1, 0, 0, 1));
	}
			

	_center = center;
	_currentDepth = currentDepth;
	_radius = radius;

	// You know you're a leaf when...
	//
	// 1. The number of points is <= the threshold
	// 2. We've recursed too deep into the tree
	//    (current Depth >= maximumDepth)
	//
	//    NOTE: We specifically use ">=" for the depth comparison so that we
	//          can set the maximumDepth depth to 0 if we want a tree with
	//          no depth.

	//if objects in this node is less than threshold stop build node and push every objects in this node into the list
	if (physicsObjects.size() <= threshold || currentDepth >= maximumDepth)
	{
		// Just store the points in the node, making it a leaf
		_physicObjectsVecList.insert(_physicObjectsVecList.end(), physicsObjects.begin(), physicsObjects.end());
		_referenceObjectList.insert(_referenceObjectList.end(), referenceObject.begin(), referenceObject.end());
		_pointCount = physicsObjects.size();
		
		return true;
	}

	
	// Classify each point to a child node
	// Recursively call build() for each of the 8 children
	Vector3   boundsOffsetTableVec3[8] =
	{
		{ -0.5, -0.5, -0.5 },
		{ +0.5, -0.5, -0.5 },
		{ -0.5, +0.5, -0.5 },
		{ +0.5, +0.5, -0.5 },
		{ -0.5, -0.5, +0.5 },
		{ +0.5, -0.5, +0.5 },
		{ -0.5, +0.5, +0.5 },
		{ +0.5, +0.5, +0.5 }
	};
	//calculate new radius
	float newRadius = radius * 0.5f;
	

	//run through 8 new child nodes
	for (int i = 0; i < 8; i++)
	{
		//calculate the center
		Vector3 offsetVec3 = boundsOffsetTableVec3[i] * radius;
		Vector3 newCenter = _center + offsetVec3;

		vector<PhysicsObject*> main;
		vector<PhysicsObject*> ref;

		//calculate the AABB of center of new node
		Vector3 cenMin = newCenter - Vector3(newRadius, newRadius, newRadius);
		Vector3 cenMax = newCenter + Vector3(newRadius, newRadius, newRadius);

		
		for (int j = 0; j < referenceObject.size(); j++)
		{
			//calculate AABB of each object
			float t_radius = referenceObject[j]->GetParent()->GetBoundingRadius(); //bounding radius is always gonna be bigger than the object
			Vector3 objMin = referenceObject[j]->GetPosition() - Vector3(t_radius, t_radius, t_radius);
			Vector3 objMax = referenceObject[j]->GetPosition() + Vector3(t_radius, t_radius, t_radius);

			//if there is any reference object check if it collide with the new node
			if (objMax.x > cenMin.x && objMin.x < cenMax.x &&
				objMax.y > cenMin.y && objMin.y < cenMax.y &&
				objMax.z > cenMin.z && objMin.z < cenMax.z)
			{
				ref.push_back(referenceObject[j]);
			}
		}
		
		//run through every object in this parent node
		for (unsigned int j = 0; j < physicsObjects.size(); j++)
		{
			//calculate AABB of each object
			float t_radius = physicsObjects[j]->GetParent()->GetBoundingRadius(); //bounding radius is always gonna be bigger than the object
			Vector3 objMin = physicsObjects[j]->GetPosition() - Vector3(t_radius, t_radius, t_radius);
			Vector3 objMax = physicsObjects[j]->GetPosition() + Vector3(t_radius, t_radius, t_radius);
			
			// check the collision between object and the child node
			if (objMax.x > cenMin.x && objMin.x < cenMax.x &&
				objMax.y > cenMin.y && objMin.y < cenMax.y &&
				objMax.z > cenMin.z && objMin.z < cenMax.z)
			{
				//check the collsion between the center point of object and the child node
				//in order to check if this object belong to this node or it just a reference object
				if (physicsObjects[j]->GetPosition().x > cenMin.x && physicsObjects[j]->GetPosition().x < cenMax.x &&
					physicsObjects[j]->GetPosition().y > cenMin.y && physicsObjects[j]->GetPosition().y < cenMax.y &&
					physicsObjects[j]->GetPosition().z > cenMin.z && physicsObjects[j]->GetPosition().z < cenMax.z)
				{
					main.push_back(physicsObjects[j]);
				}
				else
				{
					ref.push_back(physicsObjects[j]);
				}
			}
		}
		//this mean there is zero object in this node sp drop it out
		if (main.size()==0) continue;

		//create a new child node
		_child[i] = new OcTree();
		_child[i]->setParent(this);
		_child[i]->build(main,ref,  threshold, maximumDepth, newCenter, newRadius, currentDepth + 1);
	}

	return true;
}

// -----------------------------------------------------------------------------
// Generic tree traversal
// -----------------------------------------------------------------------------

const bool OcTree::traverse(callback proc, void *data) const
{
	// Call the callback for this node (if the callback returns false, then
	// stop traversing.

	if (!proc(*this, data)) return false;

	// If I'm a node, recursively traverse my children

	if (!_pointCount)
	{
		for (unsigned int i = 0; i < 8; i++)
		{
			// We store incomplete trees (i.e. we're not guaranteed
			// that a node has all 8 children)

			if (!_child[i]) continue;

			if (!_child[i]->traverse(proc, data)) return false;
		}
	}

	return true;
}

