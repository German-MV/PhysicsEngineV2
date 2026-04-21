#include "physics/Rope.h"
#include "physics/PhysicsEngine.h"

START_PHYSICS_NAMESPACE

Rope::Rope(
	const std::shared_ptr<ApplicationPoint>& startPoint,
	const std::shared_ptr<ApplicationPoint>& endPoint,
	float length,
	float mass,
	unsigned int nParticles
)
{
	particles.resize(nParticles);
	appPoints.resize(nParticles);
	constraints.resize(nParticles + 1);

	glm::vec3 startPos = startPoint->getPosition();
	glm::vec3 endPos = endPoint->getPosition();
	glm::vec3 delta = endPos - startPos;
	glm::vec3 segmentDir = glm::normalize(delta);

	float initialSegmentLength = glm::length(delta) / static_cast<float>(nParticles + 1);
	float segmentMass = mass / static_cast<float>(nParticles);

	for (unsigned int i = 0; i < nParticles; ++i)
	{
		glm::vec3 segmentPos = startPos + segmentDir * (initialSegmentLength * (i + 1));
		particles[i] = std::make_shared<Particle>(segmentMass, segmentPos);
		appPoints[i] = std::make_shared<AppPoint<Particle>>(particles[i]);
	}

	float segmentLength = length / static_cast<float>(nParticles + 1);

	constraints[0] = std::make_shared<DistConstraint>(startPoint, appPoints[0], segmentLength);
	for (unsigned int i = 1; i < nParticles; ++i)
	{
		constraints[i] = std::make_shared<DistConstraint>(appPoints[i - 1], appPoints[i], segmentLength);
	}
	constraints[nParticles] = std::make_shared<DistConstraint>(appPoints[nParticles - 1], endPoint, segmentLength);
}

void Rope::addToEngine(class PhysicsEngine& engine)
{
	for (auto& particle : particles)
		engine.addExisting(particle);
	for (auto& appPoint : appPoints)
		engine.addExisting(appPoint);
	for (auto& constraint : constraints)
		engine.addExisting(constraint);
}

void Rope::removeFromEngine(class PhysicsEngine& engine)
{
	for (auto& particle : particles)
		engine.remove(particle);
	for (auto& appPoint : appPoints)
		engine.remove(appPoint);
	for (auto& constraint : constraints)
		engine.remove(constraint);
}

END_PHYSICS_NAMESPACE