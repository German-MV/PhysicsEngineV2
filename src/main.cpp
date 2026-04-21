#include "physics/physics.h"
#include "physics/examples.h"

#include "ConsolePixels.h"

#include <chrono> 
#include <iostream>
#include <fstream>

#include <thread>
#include <mutex>

#include "utils.h"

using namespace Physics;

int main() {
	PhysicsEngine physics;

	glm::vec3 point = glm::vec3(0.f, 5.f, 0.f);
	auto dp = physics.add<DoublePendulum>(point, 5.f, 5.f, 10.f, 10.f);
	
	glm::vec3 point1(-15.f, 3.f, 0.f), point2(-10.f, 0.f, 0.f);
	float length = 5.f;
	float dist = glm::length(point1 - point2);
	glm::vec3 delta = length * glm::normalize(glm::vec3(1.f, 1.f, 0.f));
	auto pivot1 = physics.add<StaticAppPoint>(point1);
	auto pivot2 = physics.add<StaticAppPoint>(point2);
	auto particle1 = physics.add<Particle>(1.f, point1 + delta);
	auto particle2 = physics.add<Particle>(1.f, point2 + delta);
	auto appParticle1 = physics.add<AppPoint<Particle>>(particle1);
	auto appParticle2 = physics.add<AppPoint<Particle>>(particle2);
	auto constraint11 = physics.add<DistConstraint>(pivot1, appParticle1);
	auto constraint12 = physics.add<DistConstraint>(appParticle1, appParticle2);
	auto constraint22 = physics.add<DistConstraint>(pivot2, appParticle2);
	//auto constraintTriag = physics.add<DistConstraint>(pivot1, appParticle2);
	auto constraintAux = physics.add<DistConstraint>(appParticle2, dp->appPart2);
	//auto springAux = physics.add<Spring>(appParticle2, dp->appPart2, 1000.f, glm::length(appParticle2->getPosition() - dp->appPart2->getPosition()));

	auto ropePart = physics.add<Particle>(10.f, glm::vec3(10.f, 5.f, 0.f));
	auto ropeAppPart = physics.add<AppPoint<Particle>>(ropePart);
	auto ropeStaticPoint = physics.add<StaticAppPoint>(glm::vec3(15.f, 5.f, 0.f));
	auto rope = physics.add<Rope>(ropeAppPart, ropeStaticPoint, 10.f, 5.f, 30);

	auto cloth = physics.add<Cloth>(10, 10, 12.f, 12.f, 20.f);
	
	auto staticAppPoint1 = physics.add<StaticAppPoint>(cloth->particles[0]->getPosition());
	auto clothAppPoint1 = physics.add<AppPoint<Particle>>(cloth->particles[0]);
	auto clothConstraint1 = physics.add<DistConstraint>(staticAppPoint1, clothAppPoint1);

	auto staticAppPoint2 = physics.add<StaticAppPoint>(cloth->particles[90]->getPosition()); // 9
	auto clothAppPoint2 = physics.add<AppPoint<Particle>>(cloth->particles[90]); // 9
	auto clothConstraint2 = physics.add<DistConstraint>(staticAppPoint2, clothAppPoint2);

	auto wind = physics.add<Wind>(
		glm::vec3(5.f, 0.f, 0.f), 50.f,
		cloth->particles
	);

	auto gravity = physics.add<ConstGravity>(
		glm::vec3(0.f, -9.81f, 0.f),
		physics.getEvery<Object>()
	);

	auto rigidBody = physics.add<RigidBody>(
		5.f, 1.f, 1.f, 1.f,
		glm::vec3(5.f, 5.f, 0.f)
	);

	auto rigidBodyAppPoint1 = physics.add<AppPoint<RigidBody>>(rigidBody, glm::vec3(-1.f, -1.f, 0.f));
	auto rigidBodyAppPoint2 = physics.add<AppPoint<RigidBody>>(rigidBody, glm::vec3( 1.f,  1.f, 0.f));


	/*auto constForce1 = physics.add<ConstForce>(
		glm::vec3(-1.f, 0.f, 0.f),
		rigidBodyAppPoint1
	);*/

	auto constForce2 = physics.add<ConstForce>(
		glm::vec3(1.f, 0.f, 0.f),
		rigidBodyAppPoint2
	);

	auto staticAppPointRigid = physics.add<StaticAppPoint>(rigidBodyAppPoint1->getPosition());
	auto distConstraintRigid = physics.add<DistConstraint>(staticAppPointRigid, rigidBodyAppPoint1, 0.f);
	//distConstraintRigid->setCompliance(1e-8);

	/*auto part1 = physics.add<Particle>(10.f, glm::vec3(0.f, 0.f, 0.f));
	auto part2 = physics.add<Particle>(10.f, glm::vec3(0.f, 5.f, 0.f));

	auto appPart1 = physics.add<AppPoint<Particle>>(part1);
	auto appPart2 = physics.add<AppPoint<Particle>>(part2);

	auto gravity = physics.add<Gravity>(appPart1, appPart2, 10.f);

	part1->setVelocity(glm::vec3(2.5f, 0.f, 0.f));
	part2->setVelocity(glm::vec3(-2.5f, 0.f, 0.f));*/

	DrawableScreen screen(160, 50);
	auto draw = [&screen](glm::vec3 pos) { screen.drawPixel(static_cast<int>(2*pos.x) + 80, 25 - static_cast<int>(2*pos.y)); };
	auto drawRope = [&draw](const Rope& rope) { 
		for (const auto& particle : rope.particles) {
			glm::vec3 pos = particle->getPosition();
			draw(pos);
		}
	};

	auto drawCloth = [&draw](const Cloth& cloth) {
		for (const auto& particle : cloth.particles) {
			glm::vec3 pos = particle->getPosition();
			draw(pos);
		}
	};

	using Clock = std::chrono::high_resolution_clock;
	using Time_point = Clock::time_point;
	using Duration = std::chrono::duration<double>;

	Time_point current = Clock::now();

	float deltaTime = 0.016f; // ~60 FPS

	int i = 0;

	while(true) {
		++i;
		physics.update(deltaTime, 6, 6); // Simulate ~60 FPS
		while (Duration(Clock::now() - current).count() < deltaTime);
		current = Clock::now();
		
		glm::vec3 pos1 = dp->getPosition1();
		glm::vec3 pos2 = dp->getPosition2();

		draw(point);
		draw(pos1);
		draw(pos2);
		drawRope(*rope);
		drawCloth(*cloth);
		draw(particle1->getPosition());
		draw(particle2->getPosition());
		draw(pivot1->getPosition());
		draw(pivot2->getPosition());
		draw(staticAppPointRigid->getPosition());
		float size = 2.f;
		draw(rigidBodyAppPoint1->getPosition());
		draw(rigidBodyAppPoint2->getPosition());
		/*draw(rigidBody->localToWorld(0.5f * size * glm::vec3(-1.f, -1.f, -1.f)));
		draw(rigidBody->localToWorld(0.5f * size * glm::vec3( 1.f, -1.f, -1.f)));
		draw(rigidBody->localToWorld(0.5f * size * glm::vec3(-1.f,  1.f, -1.f)));
		draw(rigidBody->localToWorld(0.5f * size * glm::vec3( 1.f,  1.f, -1.f)));*/
		/*draw(rigidBody->localToWorld(0.5f * size * glm::vec3(-1.f, -1.f,  1.f)));
		draw(rigidBody->localToWorld(0.5f * size * glm::vec3( 1.f, -1.f,  1.f)));
		draw(rigidBody->localToWorld(0.5f * size * glm::vec3(-1.f,  1.f,  1.f)));
		draw(rigidBody->localToWorld(0.5f * size * glm::vec3( 1.f,  1.f,  1.f)));*/

		screen.renderAndClear();

		glm::vec3 angularVel = rigidBody->getWorldAngularVelocity();

		std::cout << "Angular velocity: " << angularVel; //angularVel.x, angularVel.y, angularVel.z;
		//float kinetic = getKineticEnergy(*part1) + getKineticEnergy(*part2);
		//float potential = (part1->getMass() * pos1.y + part2->getMass() * pos2.y) * 9.81;
		//potential += getPotentialEnergy(*spring1) + getPotentialEnergy(*spring2);
		//std::cout << "Tot energy: " << kinetic + potential << std::endl << "Kinetic: " << kinetic << std::endl << "Potential: " << potential << std::endl;
	}

	return 0;

	//for(int i = 0; i < 1000; ++i) {
	//	physics.update(0.016f); // Simulate ~60 FPS
	//	glm::vec3 pos1 = part1->getPosition();
	//	glm::vec3 pos2 = part2->getPosition();
	//	float dist = glm::length(pos2 - pos1);
	//	std::cout << "Particle 1 Position: (" << pos1.x << ", " << pos1.y << ", " << pos1.z << ")\n";
	//	std::cout << "Particle 2 Position: (" << pos2.x << ", " << pos2.y << ", " << pos2.z << ")\n";
	//	std::cout << "Distance between particles: " << dist << "\n\n";

	//	/*outputFile << pos1.x << " " << pos1.y << " "
	//			   << pos2.x << " " << pos2.y << "\n";*/
	//}

	//outputFile.close();

	return 0;
}
