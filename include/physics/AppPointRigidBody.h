#pragma once

#include "ApplicationPoint.h"
#include "RigidBody.h"

START_PHYSICS_NAMESPACE

template <>
class AppPoint<RigidBody> : public ApplicationPoint
{
public:
	AppPoint(const std::shared_ptr<RigidBody>& rigidBody, glm::vec3 point = glm::vec3(0.f));

	void applyForce(const glm::vec3& force) override;

	glm::vec3 getPosition() const override;

	glm::vec3 getVelocity() const override;

	float getMass() const override;

	float getEffectiveInverseMass(const glm::vec3& n) const override;

	void applyConstraintCorrection(const glm::vec3& n, float deltaLambda, float invMass=-1.f) const override;

protected:
	std::weak_ptr<RigidBody> rigidBody;
	glm::vec3 point;
};

END_PHYSICS_NAMESPACE