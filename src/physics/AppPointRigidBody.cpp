#include "physics/AppPointRigidBody.h"

START_PHYSICS_NAMESPACE

AppPoint<RigidBody>::AppPoint(const std::shared_ptr<RigidBody>& rigidBody, glm::vec3 point)
	: ApplicationPoint(), rigidBody(rigidBody), point(point)
{}

void AppPoint<RigidBody>::applyForce(const glm::vec3& force)
{
	auto rb = rigidBody.lock();
	if (!rb) return;

	rb->applyForce(force, rb->localToWorld(point)); // TODO: revisar
}

glm::vec3 AppPoint<RigidBody>::getPosition() const
{
	auto rb = rigidBody.lock();
	if (!rb) return glm::vec3(0.f);
	return rb->localToWorld(point);
}

glm::vec3 AppPoint<RigidBody>::getVelocity() const
{
	auto rb = rigidBody.lock();
	if (!rb) return glm::vec3(0.f);
	return rb->getVelocity() + glm::cross(rb->getWorldAngularVelocity(), rb->getOrientation() * point);
}

float AppPoint<RigidBody>::getEffectiveInverseMass(const glm::vec3& n) const
{
	auto rb = rigidBody.lock();
	if (!rb) return 0.f;

	glm::vec3 r = rb->localToWorld(point) - rb->getPosition();
	glm::vec3 rxn = glm::cross(r, n);
	glm::mat3 invInertia = rb->getWorldInvInertiaTensor();

	return 1.f / rb->getMass() + glm::dot(rxn, invInertia * rxn);
}

float AppPoint<RigidBody>::getMass() const
{
	auto rb = rigidBody.lock();
	if (!rb) return 0.f;
	return rb->getMass();
}

void AppPoint<RigidBody>::applyConstraintCorrection(const glm::vec3& n, float deltaLambda, float invMass) const
{
	auto rb = rigidBody.lock();
	if (!rb) return;

	if (invMass < 0.f)
		invMass = getEffectiveInverseMass(n);

	glm::vec3 r = rb->getOrientation() * point;

	rb->position -= (invMass * deltaLambda) * n;

	glm::mat3 invInertia = rb->getWorldInvInertiaTensor();
	glm::vec3 rxn = glm::cross(r, n);
	glm::vec3 deltaOmega = deltaLambda * (invInertia * rxn);
	/*glm::vec3 deltaMomentum = deltaLambda * n;
	glm::vec3 deltaTorque = glm::cross(r, deltaMomentum);
	glm::vec3 deltaOmega = invInertia * deltaTorque;*/
	
	glm::quat deltaQ = 0.5f * glm::quat(0.0f, deltaOmega) * rb->orientation;

	rb->orientation -= deltaQ;
	rb->orientation = glm::normalize(rb->orientation);
}

END_PHYSICS_NAMESPACE