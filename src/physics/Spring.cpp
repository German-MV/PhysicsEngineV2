#include "physics/Spring.h"

START_PHYSICS_NAMESPACE	

void Spring::applyForce()
{
	if (auto appPoint1 = p1.lock())
	{
		if (auto appPoint2 = p2.lock())
		{
			glm::vec3 pos1 = appPoint1->getPosition();
			glm::vec3 pos2 = appPoint2->getPosition();

			glm::vec3 deltaPos = pos2 - pos1;
			float currentLength = glm::length(deltaPos);

			if (currentLength == 0.f)
				return; // Prevent division by zero

			glm::vec3 direction = deltaPos / currentLength;
			float displacement = currentLength - restLength;
			
			// Hooke's law: F = -k * x
			glm::vec3 springForce = -stiffness * displacement * direction;
			
			glm::vec3 vel1 = appPoint1->getVelocity();
			glm::vec3 vel2 = appPoint2->getVelocity();
			glm::vec3 relativeVelocity = vel2 - vel1;

			// Damping force
			glm::vec3 dampingForce = -damping * glm::dot(relativeVelocity, direction) * direction;

			glm::vec3 totalForce = springForce + dampingForce;

			appPoint1->applyForce(-totalForce);
			appPoint2->applyForce( totalForce);
		}
	}
}

float getPotentialEnergy(const Spring& spring)
{
	if (auto appPoint1 = spring.p1.lock())
	{
		if (auto appPoint2 = spring.p2.lock())
		{
			glm::vec3 pos1 = appPoint1->getPosition();
			glm::vec3 pos2 = appPoint2->getPosition();
			float currentLength = glm::length(pos2 - pos1);
			float displacement = currentLength - spring.restLength;
			// Potential energy stored in the spring: U = 0.5 * k * x^2
			return 0.5f * spring.stiffness * displacement * displacement;
		}
	}
	return 0.f;
}

END_PHYSICS_NAMESPACE