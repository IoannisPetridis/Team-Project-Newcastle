

#pragma once

#include "Constraint.h"
#include "NCLDebug.h"
#include "PhysicsEngine.h"

class DistanceConstraint : public Constraint
{
public:
	DistanceConstraint(PhysicsObject* objA, PhysicsObject* objB,
		const GLMVector3& globalOnA, const GLMVector3& globalOnB)
	{
		this->objA = objA;
		this->objB = objB;

		GLMVector3 ab = globalOnB - globalOnA;
		this->distance = ab.Length();

		GLMVector3 r1 = (globalOnA - objA->GetPosition());
		GLMVector3 r2 = (globalOnB - objB->GetPosition());
		//physical representation
		localOnA = GLMMatrix3::Transpose(objA->GetOrientation().ToMatrix3()) * r1;
		localOnB = GLMMatrix3::Transpose(objB->GetOrientation().ToMatrix3()) * r2;

		delta = 0.0f;
		impulseSum = 0.0f;
		impulseSumMin = -FLT_MAX;
		impulseSumMax = FLT_MAX;
	}


	virtual void PreSolverStep(float dt)
	{
		/*
		TUTORIAL4 CODE - Constraints
		*/
		GLMVector3 r1 = objA->GetOrientation().ToMatrix3() * localOnA;	//translate back to global
		GLMVector3 r2 = objB->GetOrientation().ToMatrix3() * localOnB;

		GLMVector3 globalOnA = r1 + objA->GetPosition();
		GLMVector3 globalOnB = r2 + objB->GetPosition();

		GLMVector3 ab = globalOnB - globalOnA;
		GLMVector3 abn = ab;
		abn.Normalise();

		this->j1 = -abn;
		this->j2 = GLMVector3::Cross(-r1, abn);
		this->j3 = abn;
		this->j4 = GLMVector3::Cross(r2, abn);

		// baumgarte offset (adds energy to the system to counter slight
		// solving errors that accumulate over time - known as constraint drift)

		{
			float distance_offset = distance - ab.Length();
			float baumgarte_scalar = 0.1f;
			b = -(baumgarte_scalar / PhysicsEngine::Instance()->GetDeltaTime()) *
				distance_offset;
		}
	}

	virtual void DebugDraw() const
	{
		GLMVector3 globalOnA = objA->GetOrientation().ToMatrix3() * localOnA + objA->GetPosition();
		GLMVector3 globalOnB = objB->GetOrientation().ToMatrix3() * localOnB + objB->GetPosition();

		NCLDebug::DrawThickLine(globalOnA, globalOnB, 0.02f, GLMVector4(0.5f, 0.0f, 0.3f, 1.0f));
		NCLDebug::DrawPoint(globalOnA, 0.05f, GLMVector4(1.0f, 0.8f, 1.0f, 1.0f));
		NCLDebug::DrawPoint(globalOnB, 0.05f, GLMVector4(1.0f, 0.8f, 1.0f, 1.0f));
	}

protected:
	float   distance;
	GLMVector3 localOnA, localOnB;
};