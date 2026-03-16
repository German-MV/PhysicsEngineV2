#include "physics/PhysicsEngine.h"

START_PHYSICS_NAMESPACE

void PhysicsEngine::update(float deltaTime, const unsigned int nSubsteps, const unsigned int nSolverIterations)
{
	// XPBD Algorithm: https://youtu.be/RhEkKDEQEYM?si=KwPEvyjMdwowUKyp

	float subDelta = deltaTime / ((float)nSubsteps);

	for (unsigned int substep = 0; substep < nSubsteps; ++substep)
	{
		for (auto& constraint : constraints)
			constraint->resetLambda();

		for (auto& force : forces)
			force->applyForce();

		for (auto& object : objects)
			object->update(subDelta);

		for (unsigned int iter = 0; iter < nSolverIterations; ++iter)
			for (auto& constraint : constraints)
				constraint->solve(subDelta);

		for (auto& object : objects)
			object->correctVel(subDelta);
	}
}

template<>
std::vector<PhysicsEngine::PtrObj> PhysicsEngine::getEvery()
{
	return objects;
}

template<>
std::vector<PhysicsEngine::PtrFrc> PhysicsEngine::getEvery()
{
	return forces;
}

template<>
std::vector<PhysicsEngine::PtrApp> PhysicsEngine::getEvery()
{
	return appPoints;
}

template<>
std::vector<PhysicsEngine::PtrCst> PhysicsEngine::getEvery()
{
	return constraints;
}

END_PHYSICS_NAMESPACE