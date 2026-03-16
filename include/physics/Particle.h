#pragma once

#include "physics/Object.h"

START_PHYSICS_NAMESPACE

template<typename T>
class AppPoint;

class Particle : public Object {
public:
	Particle(
		float mass = 1.f, 
		glm::vec3 position = glm::vec3(0.f), 
		glm::vec3 velocity = glm::vec3(0.f)
	);

	void update(float deltaTime) override;

	void setMass(float newMass);
	void setCharge(float newCharge);
	void setPosition(const glm::vec3& newPosition);
	void setVelocity(const glm::vec3& newVelocity);

	float getMass() const;
	float getCharge() const;
	glm::vec3 getPosition() const;
	glm::vec3 getVelocity() const;
	glm::vec3 getPrevPosition() const;

	void applyForce(glm::vec3 newForce);
	void applyAcceleration(const glm::vec3& acceleration) override;

protected:
	void correctVel(float deltaTime) override;

	// Parameters
	float mass, charge = 0.f;
	glm::vec3 position;
	glm::vec3 velocity;
	
	// Auxiliary parameters
	glm::vec3 prevPosition;
	glm::vec3 force;

	friend class AppPoint<Particle>;
};

float getKineticEnergy(const Particle& particle);

END_PHYSICS_NAMESPACE