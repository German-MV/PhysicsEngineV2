#pragma once

#include "physics/Force.h"
#include "physics/Object.h"

#include <vector>

START_PHYSICS_NAMESPACE

class ConstGravity : public Force
{
public:
	ConstGravity(const glm::vec3& gravity, std::vector<std::shared_ptr<Object>> object);
	
	void applyForce() override;

	glm::vec3 getGravity() const { return gravity; }

protected:
	glm::vec3 gravity;
	std::vector<std::weak_ptr<Object>> targets;
};

END_PHYSICS_NAMESPACE