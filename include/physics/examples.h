#pragma once

#include "physics/System.h"
#include "physics/Particle.h"
#include "physics/AppPointParticle.h"
#include "physics/StaticAppPoint.h"
#include "physics/DistConstraint.h"

START_PHYSICS_NAMESPACE

class DoublePendulum : public System
{
	using PtrParticle = std::shared_ptr<Particle>;

public:
	DoublePendulum(const glm::vec3& pivotPoint, float rodLength1, float rodLength2, float mass1, float mass2);

	std::pair<glm::vec3, glm::vec3> getPositions() const;
	glm::vec3 getPosition1() const;
	glm::vec3 getPosition2() const;

	std::shared_ptr<Particle> particle1, particle2;
	std::shared_ptr<AppPoint<Particle>> appPart1, appPart2;
	std::shared_ptr<StaticAppPoint> pivot;
	std::shared_ptr<DistConstraint> constraint1, constraint2;

private:
	void addToEngine(class PhysicsEngine& engine) override;
};

END_PHYSICS_NAMESPACE