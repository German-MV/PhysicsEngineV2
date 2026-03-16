#pragma once

#include "physics/ApplicationPoint.h"

START_PHYSICS_NAMESPACE

class StaticAppPoint : public ApplicationPoint
{
public:
	StaticAppPoint(const glm::vec3& position);

	glm::vec3 getPosition() const override;

	glm::vec3 getVelocity() const override;

	float getEffectiveInverseMass(const glm::vec3& n) const override;

	void applyConstraintCorrection(const glm::vec3& n, float deltaLambda, float invMass=0.f) const override;

	void setPosition(const glm::vec3& newPosition);

	void setPosition(const glm::vec3& newPosition, float deltaTime);

	void applyForce(const glm::vec3& force) override;

protected:
	glm::vec3 position;
	glm::vec3 prevPosition;
	glm::vec3 velocity;

};

END_PHYSICS_NAMESPACE