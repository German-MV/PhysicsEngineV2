#include "physics/RigidBody.h"

START_PHYSICS_NAMESPACE

RigidBody::RigidBody(
	float mass,
	float I1, float I2, float I3,
	const glm::vec3& position,
	const glm::quat& orientation,
	const glm::vec3& velocity,
	const glm::vec3& angularVelocity
) :
	mass(mass), I1(I1), I2(I2), I3(I3),
	position(position), orientation(orientation),
	velocity(velocity), angularVelocity(angularVelocity)
{
	resetForces();
}

void RigidBody::update(float deltaTime)
{
	// TODO: implement linear and angular damping
	/*float linearDamping = 0.f;
	float angularDamping = 0.01f;

	force -= linearDamping * velocity;
	torque -= angularDamping * angularVelocity;*/

	prevPosition = position;
	velocity += (force / mass) * deltaTime;
	position += velocity * deltaTime;

	prevOrientation = orientation;
	angularVelocity += (getWorldInvInertiaTensor() * torque) * deltaTime;

	orientation += (0.5f * deltaTime) * glm::quat(0.f, angularVelocity) * orientation;
	orientation = glm::normalize(orientation);

	resetForces();
}

void RigidBody::applyAcceleration(const glm::vec3& acceleration)
{
	force += mass * acceleration;
}

void RigidBody::applyForce(const glm::vec3& newForce, const glm::vec3& point)
{
	force += newForce;
	applyTorque(glm::cross(point - position, newForce));
}

void RigidBody::applyTorque(const glm::vec3& newTorque)
{
	torque += newTorque;
}

void RigidBody::resetForces()
{
	force = glm::vec3(0.f);
	torque = glm::vec3(0.f);
}

void RigidBody::setMass(float newMass)
{
	mass = newMass;
}

void RigidBody::setLocalInertiaTensor(float newI1, float newI2, float newI3)
{
	I1 = newI1;
	I2 = newI2;
	I3 = newI3;
}

void RigidBody::setWorldInertiaTensor(const glm::mat3& inertiaTensor)
{
	/* TODO: diagonalization */
}

void RigidBody::setPosition(const glm::vec3& newPosition)
{
	glm::vec3 diff = newPosition - position;
	position = newPosition;
	prevPosition += diff;
}

void RigidBody::setOrientation(const glm::quat& newOrientation)
{
	glm::quat normNewOrientation = glm::normalize(newOrientation);
	glm::quat diff = normNewOrientation * glm::inverse(orientation);
	orientation = normNewOrientation;
	prevOrientation = glm::normalize(diff * prevOrientation);
}

//float _getDeltaTime(const glm::vec3& vel, const glm::vec3& pos, const glm::vec3& prevPos)
//{
//	return glm::dot(vel, pos - prevPos) / glm::dot(vel, vel);
//}

void RigidBody::setVelocity(const glm::vec3& newVelocity)
{
	//float deltaTime = _getDeltaTime(velocity, position, prevPosition);
	velocity = newVelocity;
	//prevPosition = position - deltaTime * velocity;
}

void RigidBody::setLocalAngularVelocity(const glm::vec3& newLocalAngularVelocity)
{
	angularVelocity = orientation * newLocalAngularVelocity;
	//float deltaTime = _getDeltaTime(velocity, position, prevPosition);
	//prevOrientation = glm::normalize(orientation - (0.5f * deltaTime) * glm::quat(0.f, angularVelocity) * orientation);
	// orientation += (0.5f * deltaTime) * glm::quat(0.f, angularVelocity) * orientation;
}

void RigidBody::setWorldAngularVelocity(const glm::vec3& newWorldAngularVelocity)
{
	angularVelocity = newWorldAngularVelocity;
	//float deltaTime = _getDeltaTime(velocity, position, prevPosition);
	//prevOrientation = glm::normalize(orientation - (0.5f * deltaTime) * glm::quat(0.f, angularVelocity) * orientation);
}

float RigidBody::getMass() const { return mass; }

// float RigidBody::getCharge() const { return 0.f; }

float RigidBody::getI1() const { return I1; }
float RigidBody::getI2() const { return I2; }
float RigidBody::getI3() const { return I3; }

glm::vec3 RigidBody::getLocalInertiaDiag() const
{
	return glm::vec3(I1, I2, I3);
}

glm::mat3 RigidBody::getLocalInertiaTensor() const 
{ 
	return glm::mat3(
		I1, 0.f, 0.f,
		0.f, I2, 0.f,
		0.f, 0.f, I3
	);
}

glm::mat3 RigidBody::getWorldInertiaTensor() const
{
	glm::mat3 rotMatrix = glm::mat3_cast(orientation);
	return rotMatrix * getLocalInertiaTensor() * glm::transpose(rotMatrix);
}

glm::mat3 RigidBody::getLocalInvInertiaTensor() const
{
	return glm::mat3(
		1.f / I1, 0.f, 0.f,
		0.f, 1.f / I2, 0.f,
		0.f, 0.f, 1.f / I3
	);
}

glm::mat3 RigidBody::getWorldInvInertiaTensor() const
{
	glm::mat3 rotMatrix = glm::mat3_cast(orientation);
	return rotMatrix * getLocalInvInertiaTensor() * glm::transpose(rotMatrix);
}

glm::vec3 RigidBody::getPosition() const { return position; }

glm::quat RigidBody::getOrientation() const { return orientation; }

glm::vec3 RigidBody::getVelocity() const { return velocity; }

glm::vec3 RigidBody::getLocalAngularVelocity() const
{
	return glm::inverse(orientation) * angularVelocity;
}

glm::vec3 RigidBody::getWorldAngularVelocity() const
{
	return angularVelocity;
}

glm::vec3 RigidBody::localToWorld(const glm::vec3& localPoint) const
{
	return (orientation * localPoint) + position;
}

glm::vec3 RigidBody::worldToLocal(const glm::vec3& worldPoint) const
{
	return glm::inverse(orientation) * (worldPoint - position);
}

void RigidBody::correctVel(float deltaTime)
{
	velocity = (position - prevPosition) / deltaTime;
	glm::quat dq = orientation * glm::inverse(prevOrientation);
	if (dq.w < 0.f) dq = -dq;
	angularVelocity = (2.f / deltaTime) * glm::vec3(dq.x, dq.y, dq.z);
}

//#include <Eigen/Eigenvalues>
//
//void diagonalizeInertiaTensor(const glm::mat3& matrix, glm::vec3& eigenvalues, glm::mat3& eigenvectors)
//{
//	Eigen::Matrix3d mat;
//	mat << matrix[0][0], matrix[0][1], matrix[0][2],
//		matrix[1][0], matrix[1][1], matrix[1][2],
//		matrix[2][0], matrix[2][1], matrix[2][2];
//
//	Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> solver(mat);
//
//	eigenvalues = glm::vec3(solver.eigenvalues()[0], solver.eigenvalues()[1], solver.eigenvalues()[2]);
//	eigenvectors = glm::mat3(
//		glm::normalize(glm::vec3(solver.eigenvectors()(0, 0), solver.eigenvectors()(1, 0), solver.eigenvectors()(2, 0))),
//		glm::normalize(glm::vec3(solver.eigenvectors()(0, 1), solver.eigenvectors()(1, 1), solver.eigenvectors()(2, 1))),
//		glm::normalize(glm::vec3(solver.eigenvectors()(0, 2), solver.eigenvectors()(1, 2), solver.eigenvectors()(2, 2)))
//	);
//}

END_PHYSICS_NAMESPACE