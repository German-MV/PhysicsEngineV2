#include "physics/Wind.h"

START_PHYSICS_NAMESPACE

Wind::Wind(const glm::vec3& direction, float strength, std::vector<std::shared_ptr<Particle>> tarjects) :
	Force(), direction(glm::normalize(direction)), strength(strength)
{
	for (const auto& p : tarjects) {
		this->tarjects.push_back(p);
	}
}

#include <time.h>

void Wind::applyForce()
{
	for (const auto& weakP : tarjects) {
		if (auto p = weakP.lock()) {
			glm::vec3 windForce = direction * strength * (float)(std::cos(time(NULL)/100.f)+1.f)*0.5f;
			p->applyForce(windForce);
		}
	}
}

void Wind::setDirection(const glm::vec3& direction)
{
	this->direction = glm::normalize(direction);
}

void Wind::setStrength(float strength)
{
	this->strength = strength;
}

glm::vec3 Wind::getDirection() const
{
	return direction;
}

float Wind::getStrength() const
{
	return strength;
}

END_PHYSICS_NAMESPACE