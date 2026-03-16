#include "physics/StaticAppPoint.h"

START_PHYSICS_NAMESPACE

StaticAppPoint::StaticAppPoint(const glm::vec3& position)
	: ApplicationPoint(), position(position), prevPosition(position), velocity(glm::vec3(0.f))
{}


glm::vec3 StaticAppPoint::getPosition() const { return position; }

glm::vec3 StaticAppPoint::getVelocity() const { return velocity; }

float StaticAppPoint::getEffectiveInverseMass(const glm::vec3& n) const { return 0.f; }

void StaticAppPoint::applyConstraintCorrection(const glm::vec3& n, float deltaLambda, float invMass) const
{
	// Static point does not move
	(void)n;
}

void StaticAppPoint::setPosition(const glm::vec3& newPosition)
{
	prevPosition = position;
	position = newPosition;

	velocity = glm::vec3(0.f);
}

void StaticAppPoint::setPosition(const glm::vec3& newPosition, float deltaTime)
{
	prevPosition = position;
	position = newPosition;

	velocity = position - prevPosition;
}

void StaticAppPoint::applyForce(const glm::vec3& force)
{
	// Static point does not respond to forces
	(void)force;
}

END_PHYSICS_NAMESPACE