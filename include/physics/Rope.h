#pragma once

#include "physics/System.h"
#include "physics/Particle.h"
#include "physics/AppPointParticle.h"
#include "physics/DistConstraint.h"

START_PHYSICS_NAMESPACE

class Rope : public System
{
public:
	Rope(
		const std::shared_ptr<ApplicationPoint>& startPoint,
		const std::shared_ptr<ApplicationPoint>& endPoint,
		float length,
		float mass,
		unsigned int nParticles = 20
	);

	std::vector<std::shared_ptr<Particle>> particles;

protected:
	void addToEngine(class PhysicsEngine& engine) override;
	void removeFromEngine(class PhysicsEngine& engine) override;

	std::vector<std::shared_ptr<AppPoint<Particle>>> appPoints;
	std::vector<std::shared_ptr<DistConstraint>> constraints;
};

END_PHYSICS_NAMESPACE