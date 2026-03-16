#pragma once

#include "physics/Constraint.h"
#include "physics/ApplicationPoint.h"

START_PHYSICS_NAMESPACE

class DistConstraint : public Constraint
{
public:
	DistConstraint(
		const std::shared_ptr<ApplicationPoint>& point1,
		const std::shared_ptr<ApplicationPoint>& point2,
		float restLength
	) : 
		restLength(restLength),
		p1(point1),
		p2(point2)
	{}

	DistConstraint(
		const std::shared_ptr<ApplicationPoint>& point1,
		const std::shared_ptr<ApplicationPoint>& point2
	) :
		restLength(glm::length(point1->getPosition() - point2->getPosition())),
		p1(point1),
		p2(point2)
	{}

protected:
	void solve(float deltaTime) override;

	float restLength;

	std::weak_ptr<ApplicationPoint> p1, p2;
};

END_PHYSICS_NAMESPACE