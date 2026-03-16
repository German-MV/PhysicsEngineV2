#include "physics/AppPointParticle.h"

START_PHYSICS_NAMESPACE

AppPoint<Particle>::AppPoint(const std::shared_ptr<Particle>& particle)
	: ApplicationPoint(), particle(particle)
{
	
}

void AppPoint<Particle>::applyForce(const glm::vec3& force)
{
	particle.lock()->applyForce(force);
}

glm::vec3 AppPoint<Particle>::getPosition() const
{
	return particle.lock()->getPosition();
}

glm::vec3 AppPoint<Particle>::getVelocity() const
{
	return particle.lock()->getVelocity();
}

float AppPoint<Particle>::getEffectiveInverseMass(const glm::vec3& n) const
{
	return 1.f / particle.lock()->getMass();
}

float AppPoint<Particle>::getMass() const
{
	return particle.lock()->getMass();
}

void AppPoint<Particle>::applyConstraintCorrection(const glm::vec3& n, float deltaLambda, float invMass) const
{
	auto p = particle.lock();
	if (!p) return;

	if(invMass < 0.f)
		invMass = getEffectiveInverseMass(n);

	p->position -= (invMass * deltaLambda) * n;
}

END_PHYSICS_NAMESPACE