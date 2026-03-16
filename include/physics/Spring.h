#pragma once

#include "physics/Force.h"
#include "physics/ApplicationPoint.h"

START_PHYSICS_NAMESPACE

class Spring : public Force
{
public:
	Spring(
		const std::shared_ptr<ApplicationPoint>& p1, 
		const std::shared_ptr<ApplicationPoint>& p2,
		float stiffness = 1.f, float restLength = 0.f, float damping = 0.f
	) :
		p1(p1), p2(p2), stiffness(stiffness), restLength(restLength), damping(damping)
	{}

	virtual void applyForce();

protected:

	// Must be pointers because ApplicationPoint is abstract
	std::weak_ptr<ApplicationPoint> p1, p2;
	float stiffness, restLength, damping;

	friend float getPotentialEnergy(const Spring& spring);
};

float getPotentialEnergy(const Spring& spring);

END_PHYSICS_NAMESPACE