#pragma once

#include "physics/Physic.h"

START_PHYSICS_NAMESPACE

class Constraint : public Physic
{
public:
	Constraint() : Physic(PhysicType::CONSTRAINT) {}

	virtual void solve(float deltaTime) = 0;

	void setCompliance(float newCompliance);
	float getCompliance() const;

protected:
	void resetLambda();

	float lambda = 0.f;
	float compliance = 0.f; //0.001f;

	friend class PhysicsEngine;
};

END_PHYSICS_NAMESPACE