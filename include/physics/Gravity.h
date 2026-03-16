#pragma once

#include "physics/Force.h"
#include "physics/ApplicationPoint.h"

START_PHYSICS_NAMESPACE

class Gravity : public Force
{
public:
	Gravity(
		const std::shared_ptr<ApplicationPoint>& p1,
		const std::shared_ptr<ApplicationPoint>& p2,
		float gravitationalConst
	) :
		p1(p1), p2(p2), gravitationalConst(gravitationalConst)
	{}

	virtual void applyForce();

protected:

	// Must be pointers because ApplicationPoint is abstract
	std::weak_ptr<ApplicationPoint> p1, p2;
	float gravitationalConst;

	friend float getPotentialEnergy(const Gravity& gravity);
};

float getPotentialEnergy(const Gravity& gravity);

END_PHYSICS_NAMESPACE
