#include "physics/Cloth.h"

#include "physics/PhysicsEngine.h"

START_PHYSICS_NAMESPACE

// TODO: REVISAR QUE LO HA HECHO COPILOT
Cloth::Cloth(
	unsigned int nWidthParticles,
	unsigned int nHeightParticles,
	float width,
	float height,
	float mass
)
{
	particles.resize(nWidthParticles * nHeightParticles);
	appPoints.resize(nWidthParticles * nHeightParticles);
	constraints.reserve((nWidthParticles - 1) * nHeightParticles + nWidthParticles * (nHeightParticles - 1));

	glm::vec3 origin = glm::vec3(-width / 2.f, height / 2.f, 0.f);
	glm::vec3 step = glm::vec3(width / (nWidthParticles - 1), -height / (nHeightParticles - 1), 0.f);

	float particleMass = mass / static_cast<float>(nWidthParticles * nHeightParticles);

	for (unsigned int y = 0; y < nHeightParticles; ++y)
	{
		for (unsigned int x = 0; x < nWidthParticles; ++x)
		{
			glm::vec3 position = origin + glm::vec3(step.x * x, step.y * y, 0.f);
			unsigned int index = y * nWidthParticles + x;
			particles[index] = std::make_shared<Particle>(particleMass, position);
			appPoints[index] = std::make_shared<AppPoint<Particle>>(particles[index]);
		}
	}

	float restLengthX = step.x;
	float restLengthY = -step.y;

	for (unsigned int y = 0; y < nHeightParticles; ++y)
	{
		for (unsigned int x = 0; x < nWidthParticles; ++x)
		{
			unsigned int index = y * nWidthParticles + x;
			if (x < nWidthParticles - 1)
			{
				unsigned int rightIndex = y * nWidthParticles + (x + 1);
				constraints.push_back(std::make_shared<DistConstraint>(appPoints[index], appPoints[rightIndex], restLengthX));
			}
			if (y < nHeightParticles - 1)
			{
				unsigned int belowIndex = (y + 1) * nWidthParticles + x;
				constraints.push_back(std::make_shared<DistConstraint>(appPoints[index], appPoints[belowIndex], restLengthY));
			}
		}
	}
}

void Cloth::addToEngine(class PhysicsEngine& engine)
{
	for (auto& particle : particles)
		engine.addExisting(particle);
	for (auto& appPoint : appPoints)
		engine.addExisting(appPoint);
	for (auto& constraint : constraints)
		engine.addExisting(constraint);
}

END_PHYSICS_NAMESPACE