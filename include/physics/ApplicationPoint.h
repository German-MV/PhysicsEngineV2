#pragma once

#include "PhysicBase.h"
#include "Object.h"

START_PHYSICS_NAMESPACE

class ApplicationPoint : public PhysicBase
{
public:
	ApplicationPoint();

	virtual void applyForce(const glm::vec3& force) = 0;
	
	virtual glm::vec3 getPosition() const;

	virtual glm::vec3 getVelocity() const;

	virtual float getMass() const;

	virtual float getEffectiveInverseMass(const glm::vec3& n) const;

	virtual void applyConstraintCorrection(const glm::vec3& delta, float deltaLambda, float invMass=-1.f) const;
};


template <typename T>
class AppPoint : public ApplicationPoint {};

END_PHYSICS_NAMESPACE