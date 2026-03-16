#include "physics/ApplicationPoint.h"

START_PHYSICS_NAMESPACE

glm::vec3 ApplicationPoint::getPosition() const { return glm::vec3(0.f); }

glm::vec3 ApplicationPoint::getVelocity() const { return glm::vec3(0.f); }

float ApplicationPoint::getMass() const { return -1.f; }

float ApplicationPoint::getEffectiveInverseMass(const glm::vec3& n) const { return 0.f; }

void ApplicationPoint::applyConstraintCorrection(const glm::vec3& n, float deltaLambda, float invMass) const {}

ApplicationPoint::ApplicationPoint()
	: Physic(PhysicType::APPLICATION_POINT)
{}

END_PHYSICS_NAMESPACE