#include "physics/Gravity.h"
#include "utils.h"

START_PHYSICS_NAMESPACE

void Gravity::applyForce()
{
	if (auto appPoint1 = p1.lock())
	{
		if (auto appPoint2 = p2.lock())
		{
			glm::vec3 pos1 = appPoint1->getPosition();
			glm::vec3 pos2 = appPoint2->getPosition();
			float m1 = appPoint1->getMass();
			float m2 = appPoint2->getMass();

			glm::vec3 deltaPos = pos2 - pos1;

			float distanceSquared = glm::dot(deltaPos, deltaPos);

			if (distanceSquared < EPSILON)
				return; // Prevent division by zero
			
			glm::vec3 direction = glm::normalize(deltaPos);

			// Gravitational force magnitude: F = G * (m1 * m2) / r^2
			float forceMagnitude = gravitationalConst * m1 * m2 / distanceSquared;
			glm::vec3 force = forceMagnitude * direction;
			
			appPoint1->applyForce(force);
			appPoint2->applyForce(-force);
		}
	}
}

float getPotentialEnergy(const Gravity& gravity)
{
	if (auto appPoint1 = gravity.p1.lock())
	{
		if (auto appPoint2 = gravity.p2.lock())
		{
			glm::vec3 pos1 = appPoint1->getPosition();
			glm::vec3 pos2 = appPoint2->getPosition();
			
			// TODO
		}
	}
	return 0.f;
}

END_PHYSICS_NAMESPACE