#include "physics/Particle.h"

START_PHYSICS_NAMESPACE

Particle::Particle(float mass, glm::vec3 position, glm::vec3 velocity) :
	Object(ObjectType::PARTICLE), 
	mass(mass), position(position), velocity(velocity), 
	prevPosition(position), force(glm::vec3(0.f))
{}

void Particle::update(float deltaTime)
{
	velocity += (deltaTime / mass) * force; // 2nd Newton Law
	prevPosition = position;
	position += deltaTime * velocity;

	force = glm::vec3(0.f);
}

void Particle::setMass(float newMass)
{
	mass = newMass;
}

void Particle::setCharge(float newCharge)
{
	charge = newCharge;
}

void Particle::setPosition(const glm::vec3& newPosition)
{
	glm::vec3 diff = newPosition - position;
	position = newPosition;
	prevPosition += diff;
}

float _getDeltaTime(const glm::vec3& vel, const glm::vec3& pos, const glm::vec3& prevPos)
{
	return glm::dot(vel, pos - prevPos) / glm::dot(vel, vel);
}

void Particle::setVelocity(const glm::vec3& newVelocity)
{
	float deltaTime = _getDeltaTime(velocity, position, prevPosition);
	velocity = newVelocity;
	prevPosition = position - deltaTime * velocity;
}


float Particle::getMass() const
{
	return mass;
}

float Particle::getCharge() const
{
	return charge;
}

glm::vec3 Particle::getPosition() const
{
	return position;
}

glm::vec3 Particle::getVelocity() const
{
	return velocity;
}

glm::vec3 Particle::getPrevPosition() const
{
	return prevPosition;
}


void Particle::applyForce(glm::vec3 newForce)
{
	force += newForce;
}

void Particle::applyAcceleration(const glm::vec3& acceleration)
{
	force += mass * acceleration;
}

void Particle::correctVel(float deltaTime)
{
	velocity = (position - prevPosition) / deltaTime;
}

float getKineticEnergy(const Particle& particle)
{
	return 0.5f * particle.getMass() * glm::dot(particle.getVelocity(), particle.getVelocity());
}

END_PHYSICS_NAMESPACE