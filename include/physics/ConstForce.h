#pragma once

#include "physics/Force.h"
#include "physics/ApplicationPoint.h"

START_PHYSICS_NAMESPACE

class ConstForce : public Force
{
public:
	ConstForce(glm::vec3 force, const std::shared_ptr<ApplicationPoint>& target);

	void applyForce() override;

	void setForce(glm::vec3 newForce);

	glm::vec3 getForce();

protected:
	glm::vec3 force;
	std::weak_ptr<ApplicationPoint> target;
};

END_PHYSICS_NAMESPACE