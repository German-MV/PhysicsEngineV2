#pragma once

#include <glm/gtx/norm.hpp>
#include "physics/Object.h"

START_PHYSICS_NAMESPACE

template<typename T>
class AppPoint;

class RigidBody : public Object
{
public:
	RigidBody(
		float mass,
		float I1, float I2, float I3,
		const glm::vec3& position = glm::vec3(0.f),
		const glm::quat& orientation = glm::quat(1.f, 0.f, 0.f, 0.f),
		const glm::vec3& velocity = glm::vec3(0.f),
		const glm::vec3& angularVelocity = glm::vec3(0.f)
	);

	void update(float deltaTime) override;

	void applyAcceleration(const glm::vec3& acceleration) override;
	void applyForce(const glm::vec3& newForce, const glm::vec3& point = glm::vec3(0.f));
	void applyTorque(const glm::vec3& newTorque);

	void resetForces();

	void setMass(float newMass);
	void setLocalInertiaTensor(float newI1, float newI2, float newI3);
	void setWorldInertiaTensor(const glm::mat3& inertiaTensor);

	void setPosition(const glm::vec3& newPosition);
	void setOrientation(const glm::quat& newOrientation);

	void setVelocity(const glm::vec3& newVelocity);
	void setLocalAngularVelocity(const glm::vec3& newLocalAngularVelocity);
	void setWorldAngularVelocity(const glm::vec3& newWorldAngularVelocity);

	float getMass() const override;
	// float getCharge() const override { return 0.f; }
	float getI1() const;
	float getI2() const;
	float getI3() const;
	glm::vec3 getLocalInertiaDiag() const;
	glm::mat3 getLocalInertiaTensor() const;
	glm::mat3 getWorldInertiaTensor() const;
	glm::mat3 getLocalInvInertiaTensor() const;
	glm::mat3 getWorldInvInertiaTensor() const;

	glm::vec3 getPosition() const;
	glm::quat getOrientation() const;

	glm::vec3 getVelocity() const;
	glm::vec3 getLocalAngularVelocity() const;
	glm::vec3 getWorldAngularVelocity() const;

	glm::vec3 localToWorld(const glm::vec3& localPoint) const;
	glm::vec3 worldToLocal(const glm::vec3& worldPoint) const;

protected:
	void correctVel(float deltaTime) override;

	float mass;
	float I1, I2, I3;  // inertia tensor diagonal elements

	glm::vec3 position;
	glm::quat orientation;

	glm::vec3 prevPosition;
	glm::quat prevOrientation;

	glm::vec3 velocity;
	glm::vec3 angularVelocity; // world space
	
	glm::vec3 force = glm::vec3(0.f);
	glm::vec3 torque = glm::vec3(0.f);

	friend class AppPoint<RigidBody>;
	friend RigidBody Merge(const RigidBody& rb1, const RigidBody& rb2); // TODO: test this function
};

std::pair<glm::quat, glm::vec3> jacobiDiagonalization(const glm::mat3& matrix, const int nIters = 10);

END_PHYSICS_NAMESPACE