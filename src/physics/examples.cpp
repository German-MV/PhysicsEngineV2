#include "physics/examples.h"
#include "physics/PhysicsEngine.h"

START_PHYSICS_NAMESPACE

DoublePendulum::DoublePendulum(const glm::vec3& pivotPoint, float rodLength1, float rodLength2, float mass1, float mass2)
{
	particle1 = std::make_shared<Particle>(mass1, glm::vec3(pivotPoint.x + rodLength1, pivotPoint.y, pivotPoint.z));
	particle2 = std::make_shared<Particle>(mass2, glm::vec3(pivotPoint.x + rodLength1 + rodLength2, pivotPoint.y, pivotPoint.z));

	appPart1 = std::make_shared<AppPoint<Particle>>(particle1);
	appPart2 = std::make_shared<AppPoint<Particle>>(particle2);

	pivot = std::make_shared<StaticAppPoint>(pivotPoint);
	constraint1 = std::make_shared<DistConstraint>(pivot, appPart1, rodLength1);
	constraint2 = std::make_shared<DistConstraint>(appPart1, appPart2, rodLength2);
}

std::pair<glm::vec3, glm::vec3> DoublePendulum::getPositions() const
{
	return { getPosition1(), getPosition2() };
}

glm::vec3 DoublePendulum::getPosition1() const
{
	return appPart1->getPosition();
}

glm::vec3 DoublePendulum::getPosition2() const
{
	return appPart2->getPosition();
}

void DoublePendulum::addToEngine(class PhysicsEngine& engine)
{
	engine.addExisting(particle1);
	engine.addExisting(particle2);
	engine.addExisting(appPart1);
	engine.addExisting(appPart2);
	engine.addExisting(pivot);
	engine.addExisting(constraint1);
	engine.addExisting(constraint2);
}

END_PHYSICS_NAMESPACE