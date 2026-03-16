#pragma once

#include "physics/ApplicationPoint.h"
#include "physics/Particle.h"

START_PHYSICS_NAMESPACE

template <>
class AppPoint<Particle> : public ApplicationPoint
{
public:
	AppPoint(const std::shared_ptr<Particle>& particle);

	void applyForce(const glm::vec3& force) override;

	glm::vec3 getPosition() const override;

	glm::vec3 getVelocity() const override;

	float getMass() const override;

	float getEffectiveInverseMass(const glm::vec3& n) const override;

	void applyConstraintCorrection(const glm::vec3& n, float deltaLambda, float invMass=-1.f) const override;

protected:
	std::weak_ptr<Particle> particle;
};

END_PHYSICS_NAMESPACE
