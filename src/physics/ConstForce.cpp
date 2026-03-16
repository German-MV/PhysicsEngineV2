#include "physics/ConstForce.h"

START_PHYSICS_NAMESPACE

ConstForce::ConstForce(glm::vec3 force, const std::shared_ptr<ApplicationPoint>& target)
	: Force(), force(force), target(target)
{}

void ConstForce::applyForce()
{
	target.lock()->applyForce(force);
}

void ConstForce::setForce(glm::vec3 newForce)
{
	force = newForce;
}

glm::vec3 ConstForce::getForce()
{
	return force;
}

END_PHYSICS_NAMESPACE