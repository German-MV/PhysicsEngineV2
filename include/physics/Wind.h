#pragma once

#include "physics/Force.h"
#include <physics/Particle.h>
#include <vector>

START_PHYSICS_NAMESPACE

// TODO: search a better model to simulate wind

class Wind : public Force
{
public:
	Wind(const glm::vec3& direction, float strength, std::vector<std::shared_ptr<Particle>> tarjects);

	void applyForce() override;

	void setDirection(const glm::vec3& direction);
	void setStrength(float strength);

	glm::vec3 getDirection() const;
	float getStrength() const;

private:
	glm::vec3 direction;
	float strength;
	std::vector<std::weak_ptr<Particle>> tarjects;
};

END_PHYSICS_NAMESPACE